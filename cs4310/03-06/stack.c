#include <stdio.h>

// crashes at 1016 (+ 0) = 4068 bytes
int stack[5];
int stptr = 0; // where next item is pushed

void
stack_push(int xx)
{
    stack[stptr++] = xx;
}

int
stack_pop()
{
    return stack[--stptr];
}

int
main(int argc, char* argv[])
{
    for (int ii = 0; ii < 20; ++ii) {
        stack_push(ii);
        printf("pushed %d\n", ii);
    }

    for (int ii = 0; ii < 20; ++ii) {
        printf("%d\n", stack_pop());
    }

    return 0;
}
