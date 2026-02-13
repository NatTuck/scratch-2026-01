
## Bad News

Backtracking / search problems tend to take O(2^n) time.

## Good News

Many of them are that slow because they repeat a bunch of work,
which is an opportunity to not do that.

## The Robber Problem

- There's a street with houses long one side.
- You have a list of the values of easily stolen stuff in each house,
  (in order).
- Problem: If you steal from two neighboring houses, you'll get caught.
- Question: Which set of houses can you steal from and maximize your expected
  fencing value wihtout getting caught?

## Recursive search solution

```
maximize_loot(xs):
  assume we take [0], recurse (next possible house is [2])
  assume we don't take [0], recurse (next possible house is [1])
  take the maximum
```

## Dynamic Programming

Probably should be called "Filling in a Table"

- We start with a backtracking / search / recursive problem.
- We notice that we're recalculating subproblems.
- Maybe just stick in a memoization map.
- Fancier: Figure out the order we need to compute subproblems.
- Once we figure that out, we fill in a map / table intentionally.
- "Table" means multi-dimensional array.
