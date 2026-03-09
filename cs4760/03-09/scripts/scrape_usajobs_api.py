#!/usr/bin/env python3
"""
Fetch jobs from USAJobs API.
Uses the official API which doesn't require auth for basic searches.
Documentation: https://developer.usajobs.gov/
"""

import requests
from datetime import datetime, timedelta

API_BASE = "https://data.usajobs.gov/api/Search"

def search_jobs(keyword, location=None, max_results=50):
    """Search USAJobs API for jobs."""
    headers = {
        'User-Agent': 'arthur.pendelton.fake@email.com',
        'Accept': 'application/json'
    }
    
    params = {
        'Keyword': keyword,
        'WhoMayApply': 'all',
        'ResultsPerPage': min(max_results, 50),
        'PositionOffers': 1
    }
    
    if location:
        params['Location'] = location
    
    try:
        response = requests.get(API_BASE, headers=headers, params=params, timeout=30)
        if response.status_code != 200:
            print(f"  API error: {response.status_code}")
            return []
        
        data = response.json()
        return data.get('SearchResult', {}).get('SearchResultItems', [])
    
    except Exception as e:
        print(f"  Error: {e}")
        return []

def parse_job(item):
    """Parse a job from API response."""
    try:
        job = item.get('MatchedObjectDescriptor', {})
        
        title = job.get('PositionTitle', 'Unknown')
        agency = job.get('OrganizationName', 'Unknown')
        location = job.get('PositionLocationDisplay', 'Unknown')
        pub_date = job.get('PublicationStartDate', 'Unknown')
        job_url = job.get('PositionURI', '#')
        
        return {
            'title': title,
            'agency': agency,
            'location': location,
            'pub_date': pub_date[:10] if pub_date and pub_date != 'Unknown' else 'Unknown',
            'link': job_url
        }
    except Exception:
        return None

def filter_relevant(jobs):
    """Filter for national labs, HPC, Fortran, scientific computing."""
    keywords = [
        'computer scientist', 'software engineer', 'computational',
        'scientist', 'hpc', 'high performance', 'fortran',
        'numerical', 'simulation', 'modeling', 'research',
        'laboratory', 'scientific computing', 'data scientist'
    ]
    
    agencies = [
        'Department of Energy', 'NASA', 'NOAA', 'Department of Defense',
        'Air Force', 'Navy', 'Army', 'Lawrence', 'Los Alamos', 'Sandia',
        'Argonne', 'Oak Ridge', 'Brookhaven', 'Fermi', 'Jefferson',
        'National Laboratory', 'Naval Research', 'Army Research'
    ]
    
    relevant = []
    for job in jobs:
        text = f"{job['title']} {job['agency']} {job['location']}".lower()
        
        # Check if matches keywords
        has_keyword = any(kw in text for kw in keywords)
        
        # Check if at relevant agency
        has_agency = any(agg.lower() in text for agg in agencies)
        
        if has_keyword or has_agency:
            relevant.append(job)
    
    return relevant

def format_markdown(job):
    """Format as markdown table row."""
    return f"| USAJobs | {job['agency']} | {job['title']} | {job['location']} | [{job['pub_date']}]({job['link']}) | - | Not Applied | - |"

if __name__ == "__main__":
    print("Searching USAJobs API...")
    
    keywords = [
        "computer scientist",
        "software engineer",
        "computational scientist",
        "data scientist",
        "research scientist"
    ]
    
    all_jobs = []
    for kw in keywords:
        print(f"  Searching '{kw}'...")
        results = search_jobs(kw)
        print(f"    Found {len(results)} results")
        
        for item in results:
            job = parse_job(item)
            if job:
                all_jobs.append(job)
    
    # Deduplicate by title + agency
    seen = set()
    unique = []
    for job in all_jobs:
        key = (job['title'], job['agency'])
        if key not in seen:
            seen.add(key)
            unique.append(job)
    
    print(f"\nTotal unique: {len(unique)}")
    
    relevant = filter_relevant(unique)
    print(f"Relevant: {len(relevant)}")
    
    print("\n--- Relevant Jobs ---")
    for job in relevant[:30]:
        print(format_markdown(job))
