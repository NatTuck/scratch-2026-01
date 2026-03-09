#!/usr/bin/env python3
"""Scrape USAJobs listings for national labs and HPC-related roles."""

import re
import requests
from bs4 import BeautifulSoup

BASE_URL = "https://www.usajobs.gov"

def search_jobs(keyword, max_pages=3):
    """Search USAJobs with keyword and return listings."""
    jobs = []
    
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
    }
    
    for page in range(1, max_pages + 1):
        params = {
            "k": keyword,
            "p": page
        }
        
        try:
            response = requests.get(f"{BASE_URL}/Search", params=params, headers=headers, timeout=30)
            if response.status_code != 200:
                continue
                
            soup = BeautifulSoup(response.text, 'html.parser')
            
            # Try multiple selectors for job cards
            job_cards = []
            for selector in ['article.usa-card__body', '.job-card', 'article', '.search-result']:
                job_cards = soup.find_all('article')
                if job_cards:
                    break
            
            if not job_cards:
                job_cards = soup.find_all(class_=re.compile(r'.*card.*body.*'))
            
            if not job_cards:
                break
                
            for card in job_cards:
                job = parse_job_card(card)
                if job:
                    jobs.append(job)
        
        except Exception as e:
            print(f"  Error on page {page}: {e}")
            continue
    
    return jobs

def parse_job_card(card):
    """Extract job data from a USAJobs card."""
    try:
        # Try to find title
        title_elem = None
        for selector in ['a.usa-card__heading-link', 'a.job-title-link', 'h2 a', 'h3 a', 'a']:
            title_elem = card.find('a', href=True)
            if title_elem:
                break
        
        if not title_elem:
            title_elem = card.find_all('a')[0] if card.find_all('a') else None
        
        title = title_elem.get_text(strip=True) if title_elem else None
        link = title_elem['href'] if title_elem and 'href' in title_elem.attrs else None
        
        # Skip if no title
        if not title:
            return None
        
        # Try to find agency
        agency = 'Unknown'
        agency_elem = card.find(class_=re.compile(r'.*agency.*', re.I))
        if not agency_elem:
            agency_elem = card.find(string=re.compile(r'(Department|Agency|Administration|Service|Laboratory)', re.I))
        if agency_elem:
            agency = agency_elem.get_text(strip=True) if hasattr(agency_elem, 'get_text') else str(agency_elem).strip()
        
        # Try to find location
        location = 'Unknown'
        location_elem = card.find(class_=re.compile(r'.*location.*', re.I))
        if location_elem:
            location = location_elem.get_text(strip=True)
        
        # Try to find publication date
        pub_date = 'Unknown'
        date_elem = card.find(class_=re.compile(r'.*date.*', re.I))
        if date_elem:
            pub_date = date_elem.get_text(strip=True)
        
        if title and link:
            return {
                'title': title,
                'agency': agency or 'Unknown',
                'location': location or 'Unknown',
                'pub_date': pub_date or 'Unknown',
                'link': f"{BASE_URL}{link}" if link.startswith('/') else link
            }
    except Exception:
        pass
    return None

def filter_relevant_jobs(jobs):
    """Filter jobs relevant to national labs and HPC."""
    keywords = ['national laboratory', 'doe', 'department of energy', 
                'lawrence livermore', 'los alamos', 'sandia', 'argonne',
                'brookhaven', 'oak ridge', 'jefferson lab', 'fermilab',
                'nasa', 'noaa', 'weather', 'meteorology', 'atmospheric',
                'hpc', 'high performance computing', 'fortran', 'legacy',
                'scientific computing', 'numerical simulation', 'computational']
    
    relevant = []
    for job in jobs:
        text = f"{job['title']} {job['agency']} {job['location']}".lower()
        if any(kw in text for kw in keywords):
            relevant.append(job)
    
    return relevant

def format_markdown_listing(job):
    """Format a job as a markdown table row."""
    return f"| USAJobs | {job['agency']} | {job['title']} | {job['location']} | [{job['pub_date']}]({job['link']}) | - | Not Applied | - |"

if __name__ == "__main__":
    print("Scraping USAJobs...")
    
    keywords = [
        "scientific software engineer",
        "computational scientist",
        "fortran",
        "high performance computing",
        "national laboratory"
    ]
    
    all_jobs = []
    for keyword in keywords:
        jobs = search_jobs(keyword)
        print(f"Found {len(jobs)} jobs for '{keyword}'")
        all_jobs.extend(jobs)
    
    # Deduplicate
    seen = set()
    unique_jobs = []
    for job in all_jobs:
        key = (job['title'], job['agency'])
        if key not in seen:
            seen.add(key)
            unique_jobs.append(job)
    
    relevant = filter_relevant_jobs(unique_jobs)
    print(f"\nTotal unique jobs: {len(unique_jobs)}")
    print(f"Relevant jobs: {len(relevant)}")
    
    # Output markdown
    for job in relevant[:20]:
        print(format_markdown_listing(job))
