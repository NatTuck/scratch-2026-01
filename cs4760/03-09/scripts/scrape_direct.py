#!/usr/bin/env python3
"""Scrape direct national lab career pages."""

import requests
from bs4 import BeautifulSoup

LABS = [
    {'name': 'LLNL', 'url': 'https://jobs.llnl.gov/', 'keywords': ['software', 'computational', 'scientist', 'fortran', 'hpc']},
    {'name': 'LANL', 'url': 'https://www.lanl.gov/jobs/', 'keywords': ['software', 'computational', 'scientist', 'fortran', 'hpc']},
    {'name': 'Sandia', 'url': 'https://www.sandia.gov/careers/', 'keywords': ['software', 'computational', 'scientist', 'fortran', 'hpc']},
    {'name': 'Argonne', 'url': 'https://www.anl.gov/careers', 'keywords': ['software', 'computational', 'scientist', 'fortran', 'hpc']},
    {'name': 'Oak Ridge', 'url': 'https://www.ornl.gov/careers', 'keywords': ['software', 'computational', 'scientist', 'fortran', 'hpc']},
    {'name': 'NASA', 'url': 'https://www.nasa.gov/careers/', 'keywords': ['software', 'computational', 'scientist', 'fortran', 'hpc', 'aerospace', 'simulation']},
]

def scrape_lab_jobs(lab):
    """Scrape jobs from a specific lab."""
    jobs = []
    
    try:
        response = requests.get(lab['url'], timeout=30)
        if response.status_code != 200:
            return jobs
        
        soup = BeautifulSoup(response.text, 'html.parser')
        
        job_links = soup.find_all('a')
        for link in job_links:
            text = link.get_text(strip=True)
            if any(kw.lower() in text.lower() for kw in lab['keywords']):
                href = link.get('href', '')
                if href and not href.startswith('#') and not href.startswith('javascript'):
                    jobs.append({
                        'title': text,
                        'agency': lab['name'],
                        'location': 'Unknown',
                        'pub_date': 'Unknown',
                        'link': href if href.startswith('http') else f"{lab['url']}{href}"
                    })
    except Exception:
        pass
    
    return jobs

def scrape_all():
    """Scrape all configured lab career pages."""
    all_jobs = []
    for lab in LABS:
        print(f"Scraping {lab['name']}...")
        jobs = scrape_lab_jobs(lab)
        all_jobs.extend(jobs)
        print(f"  Found {len(jobs)} jobs")
    
    return all_jobs

def format_markdown_listing(job):
    """Format a job as a markdown table row."""
    return f"| Direct | {job['agency']} | {job['title']} | {job['location']} | [{job['pub_date']}]({job['link']}) | - | Not Applied | - |"

if __name__ == "__main__":
    print("Scraping direct lab career pages...")
    jobs = scrape_all()
    
    print(f"\nTotal jobs found: {len(jobs)}")
    
    for job in jobs[:30]:
        print(format_markdown_listing(job))
