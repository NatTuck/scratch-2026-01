
#include <stdio.h>

void* raw_brk(void* brk);

void* current_brk = 0;

void*
my_sbrk(size_t size)
{
    if (!current_brk) {
        current_brk = raw_brk(0);
    }

    current_brk = raw_brk(current_brk + size);

    return current_brk - size;
}

int
main(int argc, char* argv[])
{
    void* yy = raw_brk(0);
    printf("brk = %p\n", yy);
    return 0;
}
