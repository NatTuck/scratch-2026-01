
# Today: Introducing C++

## Differences from C

- Generics, in the form of templates
- Classes, with all the OOPsies that entails.
- Has a standard library with anything in it.

Some syntax extensions:

- lambdas

## Generics / Templates

```C
typedef struct int_cell {
  int head;
  struct int_cell* tail;
} int_cell;
```

```C++
template <typename T>
struct cell {
  T head;
  cell<T>* tail;
}

template <typename T>
cell<T>* cons(T hd, cell<T>* tl)
{
  ...
}

cell<int> xs = cons(3, cons(4, 0));
auto ys = cons("foo", cons("bar", 0));
```

## Classes

```C++
template <typename T>
class Cell {
  public:
    T head;
    Cell<T> tail;

    Cell(T hd, Cell<T>* tl)
    {
      this.head = hd;
      this.tail = tl;
    }
}
```

## Standard Library

### Data Structures

Better Strings

- std::string

Normal collection types

- std::vector (like ArrayList)
- std::map (like TreeMap)
- std::unordered_map (like HashMap)
- std::deque
- std::list (a doubly-linked list)
- ...

### Algorithms

- std::sort
- std::stable_sort
- std::binary_search
- std::next_permutation
- ...
