#!/usr/bin/env python3
"""Scrape HPCwire Job Board listings."""

import requests
from bs4 import BeautifulSoup

BASE_URL = "https://www.hpcwire.com"

def scrape_jobs():
    """Scrape HPCwire job listings."""
    jobs = []
    
    response = requests.get(f"{BASE_URL}/jobs/", timeout=30)
    if response.status_code != 200:
        return jobs
    
    soup = BeautifulSoup(response.text, 'html.parser')
    
    job_items = soup.find_all('div', class_='job-item')
    
    for item in job_items:
        try:
            title_elem = item.find('a', class_='job-title')
            title = title_elem.get_text(strip=True) if title_elem else None
            link = title_elem['href'] if title_elem and 'href' in title_elem.attrs else None
            
            company_elem = item.find('span', class_='company')
            company = company_elem.get_text(strip=True) if company_elem else None
            
            location_elem = item.find('span', class_='location')
            location = location_elem.get_text(strip=True) if location_elem else None
            
            date_elem = item.find('span', class_='date')
            date = date_elem.get_text(strip=True) if date_elem else None
            
            if title:
                jobs.append({
                    'title': title,
                    'agency': company or 'Unknown',
                    'location': location or 'Unknown',
                    'pub_date': date or 'Unknown',
                    'link': f"{BASE_URL}{link}" if link and link.startswith('/') else (link or '#')
                })
        except Exception:
            continue
    
    return jobs

def filter_relevant_jobs(jobs):
    """Filter HPCwire jobs for relevant keywords."""
    keywords = ['fortran', 'legacy', 'hpc', 'high performance computing',
                'scientific computing', 'simulation', 'numerical',
                'laboratory', 'research software', 'python', 'c++', 'c']
    
    relevant = []
    for job in jobs:
        text = f"{job['title']} {job['agency']} {job['location']}".lower()
        if any(kw in text for kw in keywords):
            relevant.append(job)
    
    return relevant

def format_markdown_listing(job):
    """Format a job as a markdown table row."""
    return f"| HPCwire | {job['agency']} | {job['title']} | {job['location']} | [{job['pub_date']}]({job['link']}) | - | Not Applied | - |"

if __name__ == "__main__":
    print("Scraping HPCwire...")
    jobs = scrape_jobs()
    print(f"Found {len(jobs)} jobs")
    
    relevant = filter_relevant_jobs(jobs)
    print(f"Relevant jobs: {len(relevant)}")
    
    for job in relevant[:20]:
        print(format_markdown_listing(job))
