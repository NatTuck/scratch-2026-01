
## More Advanced Allocator Stuff

```
// simple free list
struct free_list_cell { // size = 16
  long size;
  struct free_list_cell* next;
}

// malloc(8) + 8 bytes for size header = 16 byte minimum allocation
```

```
// doubly-linked free list
struct free_list_cell { // size = 32
  long size;
  bool allocated; // round up to 8
  struct free_list_cell* prev;
  struct free_list_cell* next;
}

// malloc(24) + 8 bytes for size header = 32 byte minimum allocation
```

## Rounding up to powers of 2

- We still need a size header.
- malloc(20) + size header(8) = 28, round up to 32
- malloc(30) + size header(8) = 38, round up to 64

## Buddy System

- Need to round up to powers of two, with internal size fields (
the size is part of the power of 2 size)
- We have an array of free lists, one for each power of two size
block.
- Every block at each level has a buddy, which we can find with
bit math in O(1) time.
- ...
- malloc and free are either O(log n) or O(1) depending on how
you look at it.

## Buckets / Bins

- Have an array of fixed-size free lists.
