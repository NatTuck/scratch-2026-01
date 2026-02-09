
#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    struct cell* tail;
    int head;
    int refs;
} cell;

cell*
cons(int hh, cell* tt)
{
    cell* cc = malloc(sizeof(cell));
    cc->head = hh;
    cc->tail = tt;
    cc->refs = 1;
    return cc;
}

int
sum(cell* xs)
{
    if (xs == 0) {
        return 0;
    }

    return xs->head + sum(xs->tail);
}

void
deref_list(cell* xs)
{
    if (xs == 0) {
        return;
    }

    deref_list(xs->tail);
    free(xs);
}

int
main(int argc, char* argv[])
{
    cell* xs = cons(1, cons(2, cons(3, cons(4, 0))));
    printf("Sum = %d\n", sum(xs));

    cell* ys = cons(6, xs->tail);
    printf("Sum = %d\n", sum(ys));

    free_list(xs);
    free_list(ys);
    return 0;
}
