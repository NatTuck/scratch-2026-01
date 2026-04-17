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

    long local_sum = 0;

    for (long ii = i0; ii < i1; ++ii) {
        if (ii % 101 == 0) {
            local_sum += ii;
        }
    }

    pthread_mutex_lock(&sum_lock);
    sum += local_sum;
    pthread_mutex_unlock(&sum_lock);

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
