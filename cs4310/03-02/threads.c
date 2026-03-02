
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

long sum = 0;

typedef struct range {
    long i0;
    long i1;
} range;

void*
thread_main(void* arg)
{
    range rg = *((range*)arg);
    for (long ii = rg.i0; ii < rg.i1; ++ii) {
        if (ii % 101 == 0) {
            sum += ii;
        }
    }
    return 0;
}

int
main(int argc, char* argv[])
{
    pthread_t kids[10];
    range ranges[10];

    for (int pp = 0; pp < 10; ++pp) {
        long i0 = pp * 100 * 1000 * 1000;
        long i1 = i0 + 100 * 1000 * 1000;

        ranges[pp].i0 = i0;
        ranges[pp].i1 = i1;
        pthread_create(&(kids[pp]), 0, thread_main, &(ranges[pp]));
        printf("Spawned worker %d\n", pp);
    }

    for (int ii = 0; ii < 10; ++ii) {
        pthread_join(kids[ii], 0);
    }

    printf("sum = %ld\n", sum);

    return 0;
}
