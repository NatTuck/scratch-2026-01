
# Today: Greedy Algorithms

## Grouping Kinds of Problems

**General Search Problems (Backtracking)**

- Series of choices
- We can't be sure we got the first choice right
  until we have the whole sequence.
- If 2+ recursive call, tends to be exponential time.

**Optimal Substructure (Dynamic Programming / Memoization)**

- Series of choices
- We have overlapping subproblems. We can't just split it
in half and independently solve the halves.
- We can make an optimal choice for one more step based entirely on the series
of choices so far / previous subproblem answers.
- Typically this takes polynomial time (e.g. O(n), O(n^2), etc), and possibly
also polynomial space.

**Local Optimal Substructure (Greedy Algorithms)**

- Series of choices
- We can structure the problem so that at each step the immediate
optimal choice is also globally optimal.
- This lets us solve the problem in polynomial time without extra space.
- Many problems have tempting greedy heuristics (that may give a decent
approximation) that aren't optimal. We can't be sure a greedy algo is
optimal without a correct proof.
