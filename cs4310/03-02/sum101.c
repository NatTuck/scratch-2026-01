
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char* argv[])
{
    long* sum = mmap(0, 4096, PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *sum = 0;

    for (int pp = 0; pp < 10; ++pp) {
        long i0 = pp * 100 * 1000 * 1000;
        long i1 = i0 + 100 * 1000 * 1000;

        for (long ii = i0; ii < i1; ++ii) {
            if (ii % 101 == 0) {
                *sum += ii;
            }
        }
    }

    printf("sum = %ld\n", *sum);

    return 0;
}
