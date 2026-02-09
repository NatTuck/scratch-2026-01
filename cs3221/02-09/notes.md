
# Algorithms: Backtracking

Last time: Subset sum

Common problem structure: Search

## Search Problems

- We have a set of choices we need to make.
  - It's possible to make those choices one at a time.
  - We can't figure out how well we did until we made
    the full sequence of choices.
- Examples of choices:
  - Whether or not to include a number in our subset.
  - Which road to take when finding a path on a map.
  - What move to make in a turn-based game.
- Once we have a proposed sequence, we can validate it.
  - correct / incorrect
  - A score for the answer (e.g. number of bins)

Basic plan:

- Make the first choice in the series.
  - Recurse to find the rest of the choices.
  - Once the recursive call returns, we can determine if the
    initial choice worked.
- Try all the other possible choices too, compare.

How efficient is this?

### Subset Sum

Given:

- A targt sum x
- A list of number ys

We want:

- A subsequence of ys that sums to x.

Algorithm:

```
def subseq(x, ys):
  if x == 0:
    return []

  if !empty?(ys):
    return None

  s0 = subseq(x, ys[1:])
  tmp = subseq(x - ys[0], ys[1:])
  if tmp != None:
    s1 = [ys[0]] + tmp
  return the better of s0, s1
```
