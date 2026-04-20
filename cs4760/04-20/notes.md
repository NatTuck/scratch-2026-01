
# Evidence Day

- Evidence due today
- Will be reviewed on Wednesday to confirm you're ready
to present.
- Final presentations are next week, figure 4-7pm on
Thursday and Friday (I think it's in 442)
- If you can't make both days, let me know by email ASAP.

## Agentic Job Search

### Tools and Skills

Tool calls:

- In the system message that the harness sends to the LLM, it lists
the available tools.
- In any reply, the LLM can request to use a tool.

Example tool:
`execute_shell_command(background=False, cmd="ls ~/Documents")`

Skills:

- Notes on how to do stuff.

Example: A job search directory

Skill markdown:

```md
# Skill: Job Search Management Action

Jobs are in ~/Documents/jobs directory:

- JOBS.md - Active jobs.
- DONE.md - Finished considering.

To add a job.

`echo "- Job Info" >> ~/Documents/jobs/JOBS.md`

```

Hermes has a built in skill that reminds it how
to use cron jobs.
