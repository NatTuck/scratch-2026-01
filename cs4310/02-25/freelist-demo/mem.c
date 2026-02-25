// THIS IS JUST PSEUDOCODE TO DESCRIBE A MEMORY ALLOCATOR
// DON'T TRY TO MAKE IT WORK OR CHANGE IT AT ALL

typedef struct free_list_cell {
    long size; // we're on AMD64, sizeof(long) = 8
    struct free_list_cell* next;
} free_list_cell;

static free_list_cell* free_list = 0; // NULL is empty list

void*
malloc(long size)
{
    size += 8; // for size field
    size = min(size, sizeof(free_list_cell)); // guarantee we can free

    // 1. If size > 4k, directly call mmap to get our allocation, return whole block

    // 2. Search free list for cell with cell.size >= size.

    // 3. If no such cell, allocate a new 4k page to use.

    // 4. Take the first size bytes for our allocation, return rest to free list.

    // 5. Fill in the first sizeof(long) bytes with the actual block size (including the long).
    return ptr + sizeof(long);
}

void
free(void* ptr)
{
    long* size_ptr = ((long*)ptr) - 1;
    long size = *size_ptr;

    // 1. If size > 4k, munmap this block and return.

    // 2. Stick this block on the free list, sorted by memory address.

    // 3. Traverse the free list and coalesce adjacent blocks.

    // 4. If that gave us a full free 4k page, unmap it.
}

void*
realloc(void* ptr, long size)
{
    // Correctly realloc
}
