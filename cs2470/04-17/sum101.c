#include <assert.h>
#include <stdio.h>

const long TOP = 1000 * 1000 * 1000;

int
main(int argc, char* argv[])
{
    long sum = 0;
    for (long ii = 0; ii < TOP; ++ii) {
        if (ii % 101 == 0) {
            sum += ii;
        }
    }

    printf("sum = %ld\n", sum);

    return 0;
}
