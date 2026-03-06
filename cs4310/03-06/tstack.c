#include <assert.h>
#include <pthread.h>
#include <stdio.h>

// crashes at 1016 (+ 0) = 4068 bytes
int stack[5];
int stptr = 0; // where next item is pushed
pthread_mutex_t lock;

// just a lock isn't enough, we need a condition variable

void
stack_push(int xx)
{
    pthread_mutex_lock(&lock);
    stack[stptr++] = xx;
    pthread_mutex_unlock(&lock);
}

int
stack_pop()
{
    pthread_mutex_lock(&lock);
    int rv = stack[--stptr];
    pthread_mutex_unlock(&lock);
    return rv;
}

void*
producer_thread(void* _arg)
{
    for (int ii = 0; ii < 20; ++ii) {
        stack_push(ii);
    }

    return 0;
}

int
main(int argc, char* argv[])
{
    pthread_mutex_init(&lock, 0);
    pthread_t tid;

    pthread_create(&tid, 0, producer_thread, 0);

    for (int ii = 0; ii < 20; ++ii) {
        printf("%d\n", stack_pop());
    }

    pthread_join(tid, 0);

    return 0;
}
