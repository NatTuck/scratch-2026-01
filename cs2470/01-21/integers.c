#include <stdio.h>

int
main(int argc, char* argv[])
{
    int aa = 12;

    printf("aa = %d\n", aa);
    printf("sizeof(aa) = %ld\n", sizeof(aa));

    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("sizeof(short) = %ld\n", sizeof(short));
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(long) = %ld\n", sizeof(long));
    printf("sizeof(long long) = %ld\n", sizeof(long long));

    printf("sizeof(int*) = %ld\n", sizeof(int*));
    printf("sizeof(short*) = %ld\n", sizeof(short*));

    return 0;
}
