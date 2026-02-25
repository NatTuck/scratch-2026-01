# Free List Memory Allocator Demo

This is an interactive in-browser demonstration of a free list memory allocator, similar to the concepts in `mem.c`.

## Features

- Visual representation of memory pages and blocks
- Color-coded blocks (red for allocated, green for free)
- Interactive controls for malloc, free, and realloc operations
- Visualization of the free list with arrows showing the linked structure
- Memory statistics and fragmentation analysis

## How to Use

1. Open `demo.html` in a web browser
2. Use the controls to interact with the allocator:
   - **Malloc**: Enter a size and click "Malloc" to allocate memory
   - **Free**: Enter a block ID and click "Free" to release memory
   - **Realloc**: Enter a block ID and new size to resize an allocation
   - **Show Free List**: Display the current free list structure
   - **Reset Allocator**: Clear all allocations and start fresh

## Implementation Details

The demo simulates a simplified version of the free list allocator described in `mem.c`:

- 4KB memory pages
- Block headers storing size information
- Free list management with first-fit allocation
- Block splitting and coalescing
- Linked list structure for free blocks

Note: This is a educational demonstration and simplifies several aspects of real memory allocators for clarity.