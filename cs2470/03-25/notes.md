
# Creating Processes (running programs)

On Linux and other POSIX:

- We create processes with fork()
- We run a differnet program (in the current process) with exec.

On Windows: CreateProcess

- This creates a new process and loads a new program into it.

Why fork / exec?

- We can fork() for parallel / concurrent execution of one program.
