typedef struct IntList {
    int* data; // the allocated array for data
    long size; // number of items in list
    long cap; // size of allocated data array
} IntList;

IntList* ilist_alloc();
int ilist_get(long ii);
void ilist_put(long ii, long vv);
void ilist_push(long vv);
