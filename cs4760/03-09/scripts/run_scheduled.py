#!/usr/bin/env python3
"""
Run all scrapers and save results with timestamp.
Designed to be run via cron for scheduled updates.
"""

import os
import sys
from datetime import datetime

def run_with_logging():
    """Run aggregator with logging."""
    os.makedirs('jobs', exist_ok=True)
    
    log_file = 'jobs/aggregator.log'
    
    with open(log_file, 'a') as log:
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        log.write(f"\n{'='*60}\n")
        log.write(f"Run: {timestamp}\n")
        log.write(f"{'='*60}\n")
        
        try:
            from aggregate import main, generate_markdown
            listings = main()
            generate_markdown(listings)
            log.write(f"\nSuccess: {len(listings)} listings found\n")
        except Exception as e:
            log.write(f"Error: {e}\n")
            raise

if __name__ == "__main__":
    run_with_logging()
