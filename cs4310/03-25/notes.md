
# How do we build a Garbage Collector?

## Review: Mark and Sweep

- Users allocate memory by calling a custom `gc_alloc` function instead
of malloc.
- Users never explicitly call free.
- Everything magically works as long as more memory isn't used at once
than is available.
- Specifically, if `gc_alloc` would fail due to being out of heap space,
we do a garbage collection and free any unused allocations.

### GC Sequence

- To start, no objects are marked.

Mark phase:

- Starting at the roots (stack, globals) we scan for pointers to allocated
  objects.
- When we find a pointer to an object, we mark it, then recursivley scan
  for more object pointers.

Sweep:

- For each object, if not marked, we free it.
- For each object, if it is marked, we unmark it to prepare for next GC.

## Problems

**Identifying Roots**

We always have the stack.

But globals are trickier. We could scan all of .data, but it might have a bunch
of stuff in it that definitely isn't pointers.

Easiest method is probably to have user explicitly register global roots with
a function call.

**Scanning the Stack**

That means we need to identify the top and bottom of the stack.

To identify the bottom of the stack, we can just run some asssembly code
that returns the stack pointer during GC.

How to identify top of stack?

- Segfault handler, scan from bottom.
- Have `gc_init` macro (or function) that must be called from main.

**Scanning for Pointers**

When we're just looking at memory in a C program, there are no labels for which
things are pointers.

Some assumptions (that aren't guaranteed in C programs):

- All pointers are 8 byte values aligned to 8 bytes.
- Any aligned 8-byte value that contains an address within our
heap is a pointer. This may give false positives, which is fine.

## Simplest Design

- Free List
- Used List

This means that object headers include:

```
struct mem_obj {
  long size;
  struct mem_obj* next; 
  bool mark;
}
```
