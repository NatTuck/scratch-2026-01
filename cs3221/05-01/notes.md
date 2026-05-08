# Algo: Semester Review

## Analysis of Scaling for Song Lyrics

On the first day of Christmas, my true love gave to me,
a partridge in a pair tree.

.... two french hens, and a partridge in a pear tree.

...

Twenty five thousands gladiators gladiating, ..., and a partridge in
a pear tree.

Question: How many total items does the songwriter get after
N verses?

= O(n^3)

## General Thing: Growth of Functions

- Come up with a formula
- For operations in code: Count loops
- More complex cases: Analyse a recursion

## Asymptotic Notation

- big O - Upper bound
- big Omega - Lower bound
- big Theta - Both sides bound

## Complexity Heirarchy

O(1) < O(log n) < O(n) < O(n log n) < O(n^2) < O(n^3) <  O(2^n)
  < O(n!) < O(worse stuff)

## Recursion Trees

Merge sort:

- 0 (Root): O(n)
- 1: 2 * O(n/2)
- 2: 4 * O(n/4)
- ...
- k: 2^k * O(n / 2^k)
- ...
- log n: n * O(1)

Total = O(n log n)

Binary search:

- 0: O(1)
- 1: 1 * O(1)
- ...
- (log n - 1: 1 * O(1)
- log n: 0

Total = O(log n)

---

Given a list of coins (e.g. 1, 3, 22, 84 cents) and a target value,
calculate how many ways you can combine coins to add up to that
value.

```
def count_ways(xs, k):
  if empty(xs) || k < 0:
    return 0

  if kk == 0:
    return 1
  
  first = xs[0]
  rest = xs[1:]

  # guess that we use the first coin
  c1 = count_ways(xs, k - first)
  c2 = count_ways(rest, k)

  return c1 + c2
```

T(n, k) = T(n - 1, k) + T(n, k - 1)

Leaves dominate = O(2^n + 2^k)

Two strategies to find structure:

- Greedy algorithm - Local best is global best
- Dynamic programming - Are there repeated subproblems?

2D table: Rows are sets of coints, cols are target value k,
and now work is bounded by O(n * k)

## Greedy

You really should prove that greedy is correct. How?

- Assume greedy is bad.
- Show that we can swap in the greedy solution, and it's
at least as good as the assumed optimal solution.

## Graph Algorithms

- Depth First, Breadth First, Best First (usually Djikstra's)
- Max Flow / Min Cut as concepts and Ford-Fulkerson

## NP-Hardness / Completness

## Solving instances of PCP by hand
