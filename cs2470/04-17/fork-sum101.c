#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

const long TOP = 1000 * 1000 * 1000;

int
main(int argc, char* argv[])
{
    int kids[10];

    long* sum = mmap(0, sizeof(long), PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(sum != (long*)-1);
    *sum = 0;

    for (int kk = 0; kk < 10; ++kk) {
        kids[kk] = fork();
        if (kids[kk] == 0) {
            // in child worker

            int i0 = kk * (TOP / 10);
            int i1 = i0 + (TOP / 10);

            for (long ii = i0; ii < i1; ++ii) {
                if (ii % 101 == 0) {
                    *sum += ii;
                }
            }
            exit(0);
        }
    }

    for (int kk = 0; kk < 10; ++kk) {
        wait(0);
    }

    printf("sum = %ld\n", *sum);

    return 0;
}
