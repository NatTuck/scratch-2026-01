
# Context Switching

Two cases:

- Switching from running user code to kernel code
- Switching to running user code from another process

Every process has a set of page tables, pointed to by CR3.

So when we switch processes (on a CPU core), CR3 changes, which invalidates all
TLB entries. That slows memory reads way down (5 reads instead of 1) until the
TLB refills.

Imagine two processes running on one core. One process is compute heavy,
so it needs to be pre-empted to give the other process a turn.

To switch:

- A hardware interrupt occurs (probably the scheduling timer).
- That bumps us into kernel code in the interrupt handler.
- That saves registers to current process stack.
- The kernel picks a new process to run.
- Saves stack pointer to kernel data structure.
- Swaps CR3.
- Now we've got a new memory space.
- Restore stack pointer from data struture.
- Restore registers from stack.
- sysret

## Simple Memory Allocator

New process:

```
+------------------------+
| Main thread stack      |
|                        |
+------------------------+
|                        |
|                        |
| (No heap yet)          |
|                        |
+------------------------+
| Stuff from binary      |
+------------------------+
+------------------------+
```

The fork(2) syscall:

- Copies the current process,
now we have two.
- That means copying page tables.
- For non-shared, writable mappings,
it does Copy-on-Write:
  - Page is marked read only.
  - When write happens and
  we get exeption, it copies
  that page.

To get heap space, we need to allocate
it with a syscall. Traditionally, sbrk,
but now, mmap.

```C
// How to get a heap chunk.
int flags = MAP_PRIVATE | MAP_ANONYMOUS;
void* heap_ptr = mmap(0, length, PROT_READ|PROT_WRITE, flags, -1, 0);

// How to free a heap chunk.
long munmap(void* ptr, long length);
```

We want to build 3 functions:

```C
void* malloc(long size);
void free(void* ptr); // problem: can't call munmap, no size
void* realloc(void* ptr, long); // problem: still no size
```

Another problem: mmap only allocates pages. What about alloctions
less than 4kB?

Two problems:

- Small allocations
  - Need to be able to store more than one thing in a page.
  - Need to be able to keep track of them as they're allocated
    and freed.
- Need to know size to free.
  - Need to remember the allocation sizes.

Idea: Free list

- When we allocate a chunk of memory, we need to store its
  size.
  - Where?
  - We're allocating memory right now, so we can store the size
    in the memory we're allocating.
  - We can make the allocation a little bigger so we can have
    a size field.
- We need a way to track leftover space in a heap block, and to
  track chunks that have been freed.
  - We'll use a linked list.
  - Where?
  - We've allocating memory, each free block can store its own
    linked list cell.

When malloc(12), we instead allocate 12+sizeof(size) bytes:

We store our size field before the user data so we can find it.

```
+------+
| size |
+------+   <- return this ptr
|  12  |   
+------+
```

```
struct free_list_cell {
  long size;
  free_list_cell* next;
}
```
