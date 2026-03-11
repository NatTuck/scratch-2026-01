
## Optimizing A Memory Allocator, Continued

We looked at two strategies for an optimized allocator:

- Buddy System
- Bins / Buckets

Both of these get us down to O(log n) / O(1) range complexity.

But both of them leave us with at least a 16 byte minimum allocation
size.

### Optimizing Further: Packed Buddy System

- Sizes are always a power of two, which means that we don't need
to store the size, we can just store which power of two.
- Using one byte for size gives us a range from 2^0 to 2^255
- If we use six bits for size, that's 2^0 through 2^63
- We need one bit for an "allocated" field.
- We also need prev/next pointers.
- We want to handle multiple arenas (heaps) anyway for multiple threads.
- Big allocations can go straight to mmap.
  - How big? 256k is ~64 4k pages.
- So we'll make our heaps 256k. That's 2^18
- Declare minimum allocation to be 8 bytes (2^3), then we can store
our size field as a 4-bit value (0-15 + 3 = 3-18).
- That means we can store our next and prev pointers in 16 bits each. How?
  - Max allocation is 2^18, min is 2^3, so we only need 18-3 = 15 bits.
- With a one byte heap id, we have 256k * 256 total small heap size,
so we can only do

Structures:

```C
struct packed_header { // on every allocation (4 bytes)
  unsigned uint32_t size : 4;
  unsigned uint32_t allocated : 1;
  unsigned uint32_t heap_id : 24;
};

struct packed_freelist_cell { // free blocks (12 bytes)
  unsigned uint32_t size : 4;
  unsigned uint32_t allocated : 1;
  unsigned uint32_t heap_id : 24;
  unsigned short prev;
  unsigned short next;
};

// global heaps array
void* heap_bases = // an array of heap starts.
packed_freelist_cell** = // for each heap, 16 free lists

```

## Optimizing Further

- Problem: The size field is part of each allocation.
- Get rid of that per-allocation size field.
- Let's build a bin allocator.
  - Fixed sizes: 1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, ...
- Here big allocations start after 2035 bytes.
- Big allocatons just have a size field at the beginning
and go straight to mmap.

```C
struct page_header {
  long size;
  page_header* prev;
  page_header* next;
  boolean allocated[4064]; // ~508 bytes at size 1
  // max header size is 532
}
```
