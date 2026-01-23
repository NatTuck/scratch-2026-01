#include <stdio.h>

int
add1(int xx)
{
    return xx + 1;
}

int
main(int argc, char* argv[])
{
    int x = 5;
    int y = add1(x);
    printf("5 + 1 = %d\n", y);
    return 0;
}
