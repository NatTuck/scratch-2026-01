#!/usr/bin/env python3
"""
Helper script to add jobs to the manual import file.
Usage: python3 scripts/add_job.py
"""

import os
from datetime import datetime

def add_job():
    """Interactive job addition."""
    print("Add a new job to manual imports")
    print("-" * 40)
    
    source = input("Source (e.g., LinkedIn, Indeed, Company website): ").strip()
    if not source:
        print("Source required.")
        return
    
    agency = input("Agency/Company: ").strip()
    if not agency:
        print("Agency required.")
        return
    
    title = input("Job Title: ").strip()
    if not title:
        print("Title required.")
        return
    
    location = input("Location: ").strip() or "Remote/Unknown"
    link = input("Job Link (URL): ").strip()
    if not link:
        print("Link required.")
        return
    
    date_found = input("Date Found (YYYY-MM-DD, or Enter for today): ").strip()
    if not date_found:
        date_found = datetime.now().strftime('%Y-%m-%d')
    
    # Add to manual import file
    csv_path = os.path.join(os.path.dirname(__file__), '..', 'jobs', 'manual_import.csv')
    
    with open(csv_path, 'a') as f:
        f.write(f"{source}|{agency}|{title}|{location}|{link}|{date_found}\n")
    
    print(f"\n✓ Added: {title} at {agency}")
    print("Run 'make all' to regenerate listings.")

if __name__ == "__main__":
    add_job()
