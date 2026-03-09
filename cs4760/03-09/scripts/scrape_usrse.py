#!/usr/bin/env python3
"""Scrape US-RSE Job Board listings."""

import requests
from bs4 import BeautifulSoup

BASE_URL = "https://us-rse.org"

def scrape_jobs():
    """Scrape US-RSE job listings."""
    jobs = []
    
    response = requests.get(f"{BASE_URL}/jobs/", timeout=30)
    if response.status_code != 200:
        return jobs
    
    soup = BeautifulSoup(response.text, 'html.parser')
    
    job_items = soup.find_all('article')
    
    for item in job_items:
        try:
            title_elem = item.find('a')
            title = title_elem.get_text(strip=True) if title_elem else None
            link = title_elem['href'] if title_elem and 'href' in title_elem.attrs else None
            
            meta_elem = item.find('div', class_='entry-meta')
            location = 'Unknown'
            date = 'Unknown'
            
            if meta_elem:
                spans = meta_elem.find_all('span')
                for span in spans:
                    text = span.get_text(strip=True)
                    if text:
                        if 'Remote' in text or 'USA' in text or ',' in text:
                            location = text
                        else:
                            date = text
            
            if title:
                jobs.append({
                    'title': title,
                    'agency': 'US-RSE',
                    'location': location,
                    'pub_date': date,
                    'link': f"{BASE_URL}{link}" if link and link.startswith('/') else (link or '#')
                })
        except Exception:
            continue
    
    return jobs

def filter_relevant_jobs(jobs):
    """Filter US-RSE jobs for relevant keywords."""
    keywords = ['fortran', 'legacy', 'hpc', 'scientific computing', 
                'simulation', 'numerical', 'research software', 'rse',
                'computational', 'modeling']
    
    relevant = []
    for job in jobs:
        text = f"{job['title']} {job['agency']} {job['location']}".lower()
        if any(kw in text for kw in keywords):
            relevant.append(job)
    
    return relevant

def format_markdown_listing(job):
    """Format a job as a markdown table row."""
    return f"| US-RSE | {job['agency']} | {job['title']} | {job['location']} | [{job['pub_date']}]({job['link']}) | - | Not Applied | - |"

if __name__ == "__main__":
    print("Scraping US-RSE...")
    jobs = scrape_jobs()
    print(f"Found {len(jobs)} jobs")
    
    relevant = filter_relevant_jobs(jobs)
    print(f"Relevant jobs: {len(relevant)}")
    
    for job in relevant[:20]:
        print(format_markdown_listing(job))
