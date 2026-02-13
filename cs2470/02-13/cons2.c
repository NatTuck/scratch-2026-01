#include <stdio.h>
#include <stdlib.h>

// An empty list is a 0 (NULL) pointer.

typedef struct cell {
    struct cell* tail;
    int head;
    int refs;
} cell;

cell*
cons(int hd, cell* tl)
{
    cell* ys = malloc(sizeof(cell));
    ys->head = hd;
    ys->tail = tl;
    return ys;
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
free_list(cell* xs)
{
    if (xs != 0) {
        free_list(xs->tail);
        free(xs);
    }
}

int
main(int argc, char* argv[])
{
    // xs = [1, 2, 3, 4]
    cell* xs = cons(1, cons(2, cons(3, cons(4, 0))));
    cell* ys = cons(10, cons(7, xs));

    printf("sum xs = %d\n", sum(xs));
    printf("sum ys = %d\n", sum(ys));

    free_list(xs);
    free_list(ys);

    return 0;
}
