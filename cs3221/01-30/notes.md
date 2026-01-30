
# Complexity Classes Quick Review

- We've written the number of operations for some algorithm (or
  memory usage, or whatever) as a numerical function of the input size.
  - Sorting the list takes n * (n - 3) + 35 operations.
- Take only the highest term and drop any coefficient: n^2

## Big-O and Friends

- f is O(g) means:
  - f(x) is at most as big as g(x), within some constant margin,
    once x is big enough
- f is \Omega(g) means:
  - f(x) is at most no bigger than as g(x), within some constant margin,
    once x is big enough
- f is \Theta(g) means: f is O(g) and f is \Omega(g)

## Figuring out complexity classes

Given an algorithm (e.g. a pseudocode function), how do we figure
out its complexity class?

- Simplest: Count loops

```
def foo(x):
  return x + 3
```

```
def bar(xs):
  for x in xs:
    if x > 7:
      return x
  return 3
```

Loops over the entire input.

- Zero loops is O(1).
- One loop so linear or O(n).
- Two nested loops O(n^2).
  - Two unrelated loops, probably just O(n).
- K nested loop O(n^k).

## More fun, recursive functions

```
def mergesort(xs):
  ys = mergesort(first half of xs)
  zs = mergesort(second half of xs)
  return merge(ys, zs)

def merge(xs, ys):
  zs = []
  until both xs and ys are empty:
    if either xs or ys is empty:
      append the other to zs (leaving it empty)
    else:
      compare xs[0] to ys[0]
      remove the smaller one and append it to zs
  return zs
```

```
def insertion_sort(xs):
  zs = []
  for x in xs:
    insert(zs, x) // insert into sorted list, maintaining sortedness
                  // this is O(n), so the whole thing is O(n^2)
  return zs

def insert(xs, x):
  for ii in range(xs):
    if x < xs[ii]:
      tmp = xs[ii]
      xs[ii] = x
      x = tmp
  stick x on the end
```

````
def aa(xs):
  // this function os O(n^3)

def bb(xs):
  z = 3
  for x in xs:
    for y in xs:
      z += x * y

  return z + aa(xs)

def cc(xs):
  z = 3
  for x in xs:
    z += aa(xs)

    for y in xs:
      z += x * y

  return z + aa(xs)

```




