
void* saved_brk;

void*
my_sbrk(long size)
{
    brk(old_brk + size);
    return old_brk;
}
