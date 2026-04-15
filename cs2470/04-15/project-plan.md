
To run a command:

- fork
  - child: exec
  - parent: wait

To change directory:

- Don't fork.
- Don't exec.
- Just change the directory.

To run a command with a redirect:

- fork
  - parent: wait
  - child:
    - Plan A:
      - open new (or input) file
      - close the original fd
      - dup
    - Plan B:
      - close the original fd
      - open new (or input) file
    - exec

To run a pipleline (e.g. "a | b"):

- fork B from shell
  - in parent (shell): wait on B
  - pipe
  - fork A from B:
    - in A (child):
      - close(pipe0)
      - stdout = pipe1
      - exec A
    - in B (parent):
      - close(pipe1)
      - stdin = pipe0
      - exec B
