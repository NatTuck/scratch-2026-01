
## Semaphores

A semaphore is an integer. We initialize it
with an integer value.

Two operations:

- increment
  - If there's any other process blocked trying to decrement
    the semaphore, they immediately get another try.
- decrement
  - If this would reduce the value below zero, we block
    instead.

How do we build a lock (mutex) with a semaphore?

- Initialize semaphore to 1.
- lock operation is: decrement
- unlock operation: increment

- When does a lock cause a process (thread) to block?
  - If it's the second process trying to take the lock.
- When do blocked threads unblock?
  - When the first process is done.
- How many threads do we want to have unblocked in a critical
section at a time?
  - Just one.
