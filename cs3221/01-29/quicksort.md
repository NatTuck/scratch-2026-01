
10 | 3, 92, 6, 41, 29, 8, 17, 31

3, 6, 8 | 10 |  92, 41, 29, 17, 31

3 | 6, 8  ...

3, 6, 8, 10 | ...

----

21

In every row, we have N items.
There will be log N rows (if we split in half each time).

If the input was random, we expect to get O(n log n) execution time.

(10) | (1) | (10)
(4) | (1) | (5) | (1) | (4) | (1) | (5)
(1) (1) (2) (1) (2) (1) (2) (1) (1) (1) (2) (1) (2) (1) (2)

Quicksort:

- Pick one element as the pivot.
- Reorder the list into stuff smaller than the pivot,
  the pivot, then stuff bigger than the list.
- Recurse to the left and right of the pivot.
