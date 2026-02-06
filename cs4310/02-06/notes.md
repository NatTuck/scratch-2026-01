
# Data Structures in C

Normal programming languages provide data structures:

- Some List type.
- Some Map / Dictionary type.

C thinks that's too extravagant. Instead, it gives is only three things:

- Primitive integer types (including pointers)
- Arrays: A sequence of things of the same type next to each other in memory.
  - Arrays decay to pointers (to the first element) if we give them half a
    chance.
  - Any specific array has a fixed length, but we can reference any array
    with a pointer (or array[] var = a pointer).
- Structs: A collection of potentially different things, fixed length, next
  to each other in memory.

## Two main ways to do a list

### ArrayList (C++ Vector, Python List, etc)

```C
typedef struct IntList {
  int* data;  // the allocated array for data
  long size;  // number of items in list
  long cap;   // size of allocated data array
} IntList;
```

C doesn't have methods, but we can still build this
in an OO-ish style with functions like:

```
ilist_malloc
ilist_free
ilist_put
ilist_get
ilist_push_back
...
```

### Linked List (LISP List, Elixir List)

```C
typedef struct icell {
  int head;
  struct icell *tail;
} icell;

icell* icell_empty = 0;
```

```
icell_cons
icell_free
```
