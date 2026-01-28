
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[])
{
    int sum = 0;

    for (int ii = 1; ii < argc; ++ii) {
        sum += atoi(argv[ii]);
    }

    int avg = sum / (argc - 1);

    printf("%d\n", avg);

    return 0;
}
