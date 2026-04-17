#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

const long TOP = 1000 * 1000 * 1000;

long sum = 0;
pthread_mutex_t sum_lock;

void*
thread_main(void* arg)
{
    pthread_mutex_init(&sum_lock, 0);

    int kk = *((int*)arg);

    printf("In worker %d\n", kk);

    int i0 = kk * (TOP / 10);
    int i1 = i0 + (TOP / 10);

    for (long ii = i0; ii < i1; ++ii) {
        if (ii % 101 == 0) {

            pthread_mutex_lock(&sum_lock);
            sum += ii;
            pthread_mutex_unlock(&sum_lock);

            // add %ii, (sum)
            //  - mov (sum), %tmp
            //  - add %tmp, %ii
            //  - mov %tmp, (sum)
            //
            //
            //  thread1: mov (sum), %tmp
            //  thread2: mov (sum), %tmp
            //  t1: add %tmp, %ii
            //  t1: mov %tmp, (sum)
            //  t1: add %tmp, %ii
            //  t2: mov %tmp, (sum)
        }
    }

    return 0;
}

int
main(int argc, char* argv[])
{
    pthread_t threads[10];
    int rv;

    for (int kk = 0; kk < 10; ++kk) {
        int* thread_id = malloc(sizeof(int));
        *thread_id = kk;
        pthread_create(&(threads[kk]), 0, thread_main, thread_id);
    }

    for (int kk = 0; kk < 10; ++kk) {
        pthread_join(threads[kk], 0);
    }

    printf("sum = %ld\n", sum);

    return 0;
}
