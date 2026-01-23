#include <stdio.h>

int
main(int argc, char* argv[])
{
    int aa = 12;
    int* aap = &aa;

    printf("aa = %d\n", aa);
    printf("aap = %p\n", aap);
    printf("*aap = %d\n", *aap);

    *aap += 2;

    printf("aa = %d\n", aa);
    printf("aap = %p\n", aap);

    return 0;
}
