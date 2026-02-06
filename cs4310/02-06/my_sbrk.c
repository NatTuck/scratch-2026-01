void* raw_brk(void* brk);

void* current_brk = 0;

void*
my_sbrk(long size)
{
    if (!current_brk) {
        current_brk = raw_brk(0);
    }

    current_brk = raw_brk(current_brk + size);

    return current_brk - size;
}
