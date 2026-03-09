.PHONY: all jobs track update help

help:
	@echo "Job Search Automation - Available Commands:"
	@echo ""
	@echo "  make all      - Run full aggregation (scrape all sources)"
	@echo "  make jobs     - View current job listings"
	@echo "  make track    - View application tracker"
	@echo "  make update   - Run aggregation and show summary"
	@echo "  make usajobs  - Search USAJobs API only (requires API key)"
	@echo "  make direct   - Scrape direct lab career pages only"
	@echo ""
	@echo "Setup:"
	@echo "  1. Get USAJobs API key: https://developer.usajobs.gov/"
	@echo "  2. Edit config.ini and add your API key"
	@echo "  3. Add manual jobs to jobs/manual_import.csv"

all:
	@python3 scripts/aggregate.py

jobs:
	@echo "=== Current Job Listings ==="
	@head -20 jobs/listings.md

track:
	@echo "=== Application Tracker ==="
	@cat tracker.md

update:
	@python3 scripts/aggregate.py
	@echo ""
	@echo "=== Quick Summary ==="
	@grep "^- \*\*Total" jobs/listings.md
	@grep "^- \*\*By Source" jobs/listings.md

usajobs:
	@python3 scripts/scrape_usajobs_api.py

direct:
	@python3 scripts/scrape_direct.py

manual:
	@python3 scripts/aggregate.py

# Install dependencies
install:
	@pip3 install -r scripts/requirements.txt

# Clean generated files
clean:
	@rm -f jobs/listings.md jobs/aggregator.log tracker.md
