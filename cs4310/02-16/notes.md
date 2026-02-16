
# Virtual Memory and Page Tables

## Virtual Memory

- Each running process gets its own address space.
- Virtual memory is managed in pages.
  - On AMD64 (and a bunch of other common archetectures),
    pages are typically 4KB.
- That means that each process needs a lookup table that
  maps 4KB virtual pages to 4KB physical pages.

## The Lookup Table

Let's think about a 32-bit Intel system for a moment before
we get to AMD64.

Page table entries:

```C
struct pte {
  int20 physical_page_number;
  int12 flags_and_stuff;
};

pte page_table[1024 * 1024]; // 4 megabytes

sizeof(pte) = 4 bytes
```

That early 32-bit PC had 8 MBs of RAM.

We need to compress this map.

`Map<page_num> -> pte`

Options:

- Hash map
  - Selling point: Usually operations take O(1)
  - Worst case O(n), collisions
  - We really need a better guarantee for memory access times
- Tree map (Binary Search Tree)
  - O(log n) = N is a million = so this is 20
- Custom fixed-size tree structure
  - We can pick a large, fixed branching factor

How to implement this lookup:

- On Intel / AMD64, lookup is entirely in hardware.
- On SPARC this was implemented in software.

## Page Tables

On 32-bit Intel, each process has two levels of table:

- Root table:
  - Uses the first 10 bits of the page # to index
    a second level table.
  - So that's an array of 1024 entries, each 4 bytes.
  - Entries here can be marked invalid, in which case
    we don't allocate the corresponding second level
    table at all.
- Second level table.
  - Uses the second 10 bits to map to a real pte.
  - Again, the pte is 4 bytes.
