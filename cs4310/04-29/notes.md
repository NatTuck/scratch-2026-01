
# Semester Summary

## Operating System

Software that runs on a computer and enables:

- Communication between the user software, hardware, and other shared
resources.
- Core software to do things like run programs, manage running programs, etc.

## Kernel

- That component which is always running while the computer is turned
on and directly manages hardware / shared resources.
- The kernel exposes an API, a set of system calls, which allow user
programs to access shared resources.

## C to Assembly

- C and Assembly correspond pretty close to 1:1

## Two Assembly Languages: AMD64, RISC-V

- A set of machine instructions (e.g. add)
- A application binary interface
  - This lets us compile a library to a .so file and then
    call functions in it from a C program we compile later
    with a different compiler.
  - How do we call a function?
    - Arguments go in registers
    - On 32 bit x86, they went on the stack
    - Stack alignment rules
  - etc.
  - How do we call a syscall?

## What system calls did we use this semester?

- open - Open a file
- read, write - Reads / writes data from a file
- close - Close a file
- mmap - Manage the current processes memory map (page tables)
- exec, fork
- exit
- ...

## Memory Allocation

### Manual Memory Allocation

- malloc, free, realloc
- Various levels of complexity:
  - Simple free list
  - Complex free list
  - Bucket / bin allocator
  - Oh crap, threads are a thing

### Garbage Collector

- Way more complicated than manual allocators
- But conceptually can go even faster.
- If we're trying to enumerate the 7 wonders of the sofware engineering
world, the JVM and its garbage collectors are top contenders.

- Good final exam question: Why can't a garbage collector for C move allocated
objects? This would be great to work around, because without moving objects
we can't build a copying collector.

## Bring a device on Friday for course evals
