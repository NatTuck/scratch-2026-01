#!/usr/bin/env python3
"""Main aggregator - combines all job sources into unified listings."""

import os
import csv
from datetime import datetime

from scrape_usajobs_api import search_jobs as usajobs_api_search, parse_job, filter_relevant as filter_usajobs
from scrape_direct import scrape_all as scrape_direct_labs

def load_config():
    """Load configuration from config.ini."""
    config = {
        'usajobs_key': '',
        'user_agent': 'arthur.pendelton.fake@email.com',
        'keywords': ['computer scientist', 'software engineer', 'computational scientist'],
        'max_results': 50
    }
    
    config_path = os.path.join(os.path.dirname(__file__), '..', 'config.ini')
    if os.path.exists(config_path):
        with open(config_path) as f:
            for line in f:
                line = line.strip()
                if line.startswith('USAJOBS_API_KEY='):
                    config['usajobs_key'] = line.split('=', 1)[1].strip().strip('"')
                elif line.startswith('KEYWORDS='):
                    config['keywords'] = [k.strip() for k in line.split('=', 1)[1].split(',')]
    
    return config

def scrape_usajobs(config):
    """Scrape USAJobs using API if key available, otherwise skip."""
    jobs = []
    
    if not config['usajobs_key']:
        print("  [Skipping USAJobs API - no API key configured]")
        print("  Get a free key at: https://developer.usajobs.gov/")
        return jobs
    
    headers = {
        'User-Agent': config['user_agent'],
        'Accept': 'application/json',
        'Authorization-Key': config['usajobs_key']
    }
    
    from scrape_usajobs_api import API_BASE
    import requests
    
    for keyword in config['keywords'][:5]:
        params = {
            'Keyword': keyword,
            'ResultsPerPage': min(config['max_results'], 50)
        }
        
        try:
            response = requests.get(API_BASE, headers=headers, params=params, timeout=30)
            if response.status_code != 200:
                continue
            
            data = response.json()
            items = data.get('SearchResult', {}).get('SearchResultItems', [])
            
            for item in items:
                job = parse_job(item)
                if job:
                    job['source'] = 'USAJobs'
                    jobs.append(job)
            
            print(f"  '{keyword}': {len(items)} results")
        
        except Exception as e:
            print(f"  Error searching '{keyword}': {e}")
    
    return jobs

def load_manual_imports():
    """Load manually imported jobs from CSV."""
    jobs = []
    csv_path = os.path.join(os.path.dirname(__file__), '..', 'jobs', 'manual_import.csv')
    
    if not os.path.exists(csv_path):
        return jobs
    
    with open(csv_path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#') or line.startswith('---'):
                continue
            
            parts = line.split('|')
            if len(parts) >= 5:
                jobs.append({
                    'source': parts[0],
                    'agency': parts[1],
                    'title': parts[2],
                    'location': parts[3],
                    'link': parts[4],
                    'pub_date': parts[5] if len(parts) > 5 else 'Unknown'
                })
    
    return jobs

def deduplicate(jobs):
    """Remove duplicate jobs by title + agency."""
    seen = set()
    unique = []
    for job in jobs:
        key = (job['title'], job['agency'])
        if key not in seen:
            seen.add(key)
            unique.append(job)
    return unique

def generate_markdown(listings):
    """Generate markdown files for listings and tracker."""
    os.makedirs('jobs', exist_ok=True)
    
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    # Count by source
    source_counts = {}
    for job in listings:
        src = job.get('source', 'Unknown')
        source_counts[src] = source_counts.get(src, 0) + 1
    
    listings_md = f"""# Job Listings

Last updated: {timestamp}

## Summary
- **Total Listings:** {len(listings)}
- **By Source:** {', '.join(f'{k}: {v}' for k, v in source_counts.items())}

## Active Listings

| Source | Agency | Title | Location | Posted | Link | Applied | Status | Notes |
|--------|--------|-------|----------|--------|------|---------|--------|-------|
"""
    
    for job in listings:
        link_text = job.get('pub_date', 'Unknown')
        listings_md += f"| {job.get('source', 'Unknown')} | {job.get('agency', 'Unknown')} | {job.get('title', 'Unknown')} | {job.get('location', 'Unknown')} | [{link_text}]({job.get('link', '#')}) | - | Not Applied | - |\n"
    
    with open('jobs/listings.md', 'w') as f:
        f.write(listings_md)
    
    # Generate tracker
    tracker_md = f"""# Application Tracker

Last updated: {timestamp}

## Summary
| Status | Count |
|--------|-------|
| Not Applied | {len(listings)} |
| Applied | 0 |
| Interview | 0 |
| Offer | 0 |
| Rejected | 0 |

## Applications

| Source | Agency | Title | Location | Link | Date Applied | Status | Notes |
|--------|--------|-------|----------|------|--------------|--------|-------|
"""
    
    with open('tracker.md', 'w') as f:
        f.write(tracker_md)
    
    print(f"\nGenerated:")
    print(f"  - jobs/listings.md ({len(listings)} jobs)")
    print(f"  - tracker.md")

def main():
    print("=" * 60)
    print("Job Search Aggregator")
    print(f"Date: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("=" * 60)
    
    config = load_config()
    all_jobs = []
    
    # USAJobs API
    print("\n[USAJobs API]")
    jobs = scrape_usajobs(config)
    all_jobs.extend(jobs)
    
    # Direct lab pages
    print("\n[Direct Lab Pages]")
    jobs = scrape_direct_labs()
    all_jobs.extend(jobs)
    
    # Manual imports
    print("\n[Manual Imports]")
    jobs = load_manual_imports()
    all_jobs.extend(jobs)
    print(f"  Loaded {len(jobs)} manual imports")
    
    # Deduplicate
    unique = deduplicate(all_jobs)
    
    print(f"\n{'=' * 60}")
    print(f"Total listings: {len(unique)}")
    print(f"{'=' * 60}")
    
    generate_markdown(unique)
    return unique

if __name__ == "__main__":
    main()
