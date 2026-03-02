
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

#include <semaphore.h>

void*
malloc_shared(size_t size)
{
    return mmap(0, size, PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

int
main(int argc, char* argv[])
{
    long* sum = malloc_shared(sizeof(long));
    *sum = 0;

    sem_t* lock = malloc_shared(sizeof(sem_t));
    sem_init(lock, 1, 1);

    for (int pp = 0; pp < 10; ++pp) {
        long i0 = pp * 100 * 1000 * 1000;
        long i1 = i0 + 100 * 1000 * 1000;

        int cpid;
        if ((cpid = fork())) {
            printf("Spawned worker %d\n", cpid);
        }
        else {
            for (long ii = i0; ii < i1; ++ii) {
                if (ii % 101 == 0) {
                    sem_wait(lock);
                    *sum += ii;
                    sem_post(lock);
                }
            }
            exit(0);
        }
    }

    for (int ii = 0; ii < 10; ++ii) {
        wait(0);
    }

    printf("sum = %ld\n", *sum);

    return 0;
}
