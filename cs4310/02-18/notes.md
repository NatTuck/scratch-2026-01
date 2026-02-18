
## 32-bit Page Tables

Purpose: Map a 32-bit virtual address to a 32-bit physical address.

How we split up the 32-bit address:

- Byte offset within a page: 12 bits
  - The last 12 bits of the address are the same for both
    the physical and virtual address.
- That leaves 20 bits for page number.
- Top 10 bits of page number indexes into our root page table.
- Middle 10 bits (bottom bits of page number) index into our
  second level table.

## Problem: Memory accesses are kind of slow

```C
  int xs[2048]; // 2048 * 4 = 8192 bytes = 2 pages
  for (int ii = 0; ii < 2048; ++ii) {
    xs[ii] = ii;
  }
 
  int ys[2048];
  // consider just this loop
  for (int ii = 0; ii < 2048; ++ii) {
    ys[ii] = xs[ii];
    // assuming xs starts at the start of a page
    // xs[0] takes 5 memory reads
    // xs[1] takes 1, because the translation is cached
    // how many memory accesses to read all of xs? 
    // 2048 array reads + 2*4 = 8 individual table reads
  }
```

CPU speed:

- 3.3 GHz means we can do 3 billion clock cycles per second
- Each clock cycle is how many seconds? 0.33 nanoseconds

Problem:

- Address translations with page table take 4 extra memory accesses.
- So we want to cache recently used translations.
- In the CPU, that cache is called the Translation Lookaside Buffer
  (Page Number Translation Cache), which almost always has 1536 entries.

Cache heirarchy:

- L1, split into speparate data / code caches, maybe 16k each.
  - Maybe L1 cache accesses take 5 ns.
- L2, typically per core, maybe 1MB.
- L3, for gaming they want to sell you 100MB. More typically, 16MB.
- Main memory, maybe 32GB
