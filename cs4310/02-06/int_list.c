
#include <stdlib.h>

#include "int_list.h"

IntList*
ilist_alloc()
{
    IntList ys;
    ys.cap

        IntList* xs
        = malloc(sizeof(IntList));

    xs->cap = 1; // (*xs).cap = 1
    xs->size = 0;
    xs->data = malloc(sizeof(int) * xs->cap);
    return xs;
}

int ilist_get(long ii);
void ilist_put(long ii, long vv);
void ilist_push(long vv);
