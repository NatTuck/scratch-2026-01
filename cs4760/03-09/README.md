# Job Search Automation

Automated job aggregation and tracking system for national labs, HPC, and scientific computing roles.

## Quick Start

```bash
# Run full aggregation
python3 scripts/aggregate.py

# Run individual scrapers
python3 scripts/scrape_usajobs.py
python3 scripts/scrape_hpcwire.py
python3 scripts/scrape_usrse.py
python3 scripts/scrape_clearancejobs.py
python3 scripts/scrape_direct.py
```

## Output Files

- `jobs/listings.md` - All current job listings aggregated from all sources
- `tracker.md` - Application tracking spreadsheet (update manually as you apply)

## Sources

| Source | Description |
|--------|-------------|
| USAJobs | Federal jobs (national labs, NASA, NOAA, DOE) |
| HPCwire | High-performance computing industry jobs |
| US-RSE | Research Software Engineer positions |
| ClearanceJobs | Security clearance required positions |
| Direct | Lab career pages (LLNL, LANL, Sandia, ORNL, Argonne, NASA) |

## Filtering

Jobs are filtered for keywords relevant to your profile:
- Fortran, legacy code, HPC
- Scientific computing, numerical simulation
- National labs, DOE, NASA, NOAA
- Computational scientist, research software engineer

## Scheduled Updates

Add to crontab for daily updates:
```bash
0 8 * * * cd /home/nat/scratch/cs4760/03-09 && python3 scripts/aggregate.py >> jobs/aggregator.log 2>&1
```

## Manual Tracking

Update `tracker.md` as you apply:
1. Change "Date Applied" column to the date you submitted
2. Update "Status" column: Not Applied → Applied → Interview → Offer/Rejected
3. Add notes about each application (contact info, follow-up dates, etc.)

## Requirements

- Python 3.8+
- requests
- beautifulsoup4
