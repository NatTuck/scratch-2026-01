#include <stdio.h>
#include <stdlib.h>

// An empty list is a 0 (NULL) pointer.

typedef struct cell {
    int head;
    struct cell* tail;
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
sum_acc(cell* xs, int yy)
{
    if (xs == 0) {
        return yy;
    }
    return sum_acc(xs->tail, yy + xs->head);
}

int
sum(cell* xs)
{
    return sum_acc(xs, 0);
}

int
sum2(cell* xs)
{
    int yy = 0;
    for (cell* it = xs; it != 0; it = it->tail) {
        yy += it->head;
    }
    return yy;
}

int
sum1(cell* xs)
{
    if (xs == 0) {
        return 0;
    }
    return xs->head + sum1(xs->tail);
}

int
main(int argc, char* argv[])
{
    // xs = [1, 2, 3, 4]
    cell* xs = cons(1, cons(2, cons(3, cons(4, 0))));

    printf("sum = %d\n", sum(xs));

    return 0;
}
