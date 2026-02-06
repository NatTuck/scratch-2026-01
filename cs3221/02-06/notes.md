
# Proof By Induction

```python
@doc """
Sum a list of integers.
"""
def sum1(xs):
  if len(xs) == 0:
    return 0
  else:
    return xs[0] + sum1(xs[1:])
```

To prove: This sums a list of integers. (Returning
the sum of the numbers in the list.)

Base case: An empty list. The sum of zero things is zero.

General case (inductive step):

- Assume that the recursive call will do the right thing.
- To prove: Given that correct answer from the recursive
  call, show that the function does the right thing (returns
  the correct value).

So:

- sum1(xs[1:]) correctly calculates the sum of the list,
  excluding the first item, by assumption.
- Adding in the first item gives us the whole sum because
  that's how addition works.

The inductive proof thing:

- Think about the length 0 case: It's correct because it's the
  base case which is correct.
- Think about the lenght 1 case:
  - The recursive call is correct (it's the base case).
  - This is correct, because X + 0 is in fact the sum of (X).
- Think about the length i case:
  - If the recursive call gives the right answer, then this
    is correct becasue X + the rest is correct.

## Another one

```
@doc """
Reverse a list of integers.
"""

def rev1(xs):
  if len(xs) == 0:
    return xs
  else:
    return rev1(xs[1:]) + [xs[0]]
```

Proof:

Base case: By definition, rev1([]) = [].

General case:

- We assume that reversing the rest of the list works.
- By definition of reversing, the first item becomes the last
  item, so that's the right place to put it. And reversing all
  the other items is the right thing.

Induciton:

- It works for length = zero.
- Assuming it works for length = 0, it works for length = 1.
- Assuming it works for length = i, it works for length = i + 1.

## Example Problem

We've got an integer `x` and a list of positive integers `ys`.

Can we pick some of the numbers from `ys` such that they add up
exactly to `x`? If so, show them.

Example:

- 100, (10, 20, 27, 30, 50, 18) = 20, 30, 50
- 100, (24, 34, 45, 78)

We want a function `subsum(x, ys)` that solves this problem (either
returns an answer or null for no answer).

Inductive design:

Base case:

- We can always sum an empty list to zero.
- subsum(0, []) = []

Base case:

- We can never sum an empty list to a number other than zero.
- subsum(x, []) = null if x != 0

General case:

Try both of:

- subsum(x, [y] + ys) = [y] + subsum(x - y, ys) if y is in the result.

- subsum(x, [y] + ys) = subsum(x, ys)

Induction on the lenght of the list:

- 0
  - Works for empty list (by definitoin, sum([]) = 0).
  - Works for non-empty, (by defiition, sum([... non-negatives]) != 0.
- 1
  - If first item in result, reduces easily to base case.
  - First item not in result, it won't be included in sum, so simply
    dropping it and recursing is correct.
