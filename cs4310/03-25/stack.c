#include <stdio.h>

void* getbp();
void* getsp();

void*
page_base(void* addr_ptr)
{
    const unsigned long page_mask = ~4095;
    unsigned long addr = (unsigned long)addr_ptr;
    unsigned long base = addr & page_mask;
    return (void*)base;
}

void* gc_stack_top = 0;

void
gc_init_real(void* lp)
{
    gc_stack_top = page_base(lp) + 4096;
}

int
count(int nn)
{
    int local;

    if (nn == 0) {
        printf("Top of stack: %p\n", gc_stack_top);
        printf("Bot of stack: %p\n", page_base(&local));
        printf("bp: %p, sp: %p\n", getbp(), getsp());
        return 0;
    }
    else {
        return 1 + count(nn - 1);
    }
}

#define gc_init()                      \
    {                                  \
        int _gc_init_local;            \
        gc_init_real(&_gc_init_local); \
    }

int
main(int argc, char* argv[])
{
    gc_init();

    printf("bp: %p, sp: %p\n", getbp(), getsp());

    count(50);

    return 0;
}
