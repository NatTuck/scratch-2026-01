
# Exam 1 is Thursday

## Q

Solve the recurrance `T(n) = 2T(n-1) + 1` with T(0) = 0 using recursion trees.

```
L0 = T(n):      1
L1 = 2T(n-1):   1 + 1
L2 = 4T(n-2):   1 + 1 + 1 + 1
...
Lx = (2^x)T(n-x): 2^x
...
Ln = (2^n)T(0): 2^n

Exponential case:
L(n) is 2^n
L(n-1) is (2^n)/2

So total is O(2^n)
...

```

Three cases to look for summing up our levels:

- At each level, we have more work to do (leaves will dominate).
- Every level matters.
- At each level, we have less to do (extra work / root will dominate).

##

Prove that for all n >= 1, the sum 1 + 2 + 3 + ... + n = n(n+1)/2

Conceptual proof:

pair the first item with the last item

1 + n        (each row is n+1)
2 + (n-1)    (there are n rows)
3 + (n-2)
...
n + 1        (this over-counts by a factor of 2)

Now let's do it inductively.

Base case: Sum from 1 to 1 is 1.

To prove:

- Assuming sum to (x-1) adds up to (n(n+1) / 2), plug in (x-1), ((x-1)x / 2)
- Show that sum to x adds up to (x(x+1) / 2).

Sum to x:

- Have sum to x-1 is ((x-1)x / 2)
- y = (((x-1)x) / 2) + x

- y - x = (((x-1)x) / 2)
- 2(y-x) = (x-1)(x)
-        = x^2 - x
- 2y - 2x = x^2 - x
- 2y = x^2 + x
- y = (x^2 + x) / 2
- y = ((x+1)x) / 2

(x-1)x / 2

##

Prove that the following algorithm correctly determines whether
a string is a palindrome:

```
def is_palindrome(s):
  if len(s) <= 1:
    return True
  return s[0] == s[-1] and is_palindrome(s[1:-1])
```

Base case: Length <= 1, it's a palindrome.

Inductive case:

- Must show: For a string of length two or longer,
it's sufficient to show that the ends match and the
middle (excluding first and last chars) is a palindrome.

- Length 2 case: First and last are the same letter,
middle is empty.
- Length 3 case: First and last are the same letter,
middle is length 1.

Length > 3.

- The middle is length n-2, recursion shows it's a palidrome.
- It must be a palindrome, because reversing by definiton:
  - Swaps the first and last characters, which are the same.
  - Reverses the middle, which is a palindrome.

#

For the game of Tic-Tac-Toe on a 3x3 board, estimate
the size of the complete game tree (upper bound).

n = 9

L0 = At the root: 9
L1 = Next level: 8

9 *8* 7 *6* ... * 1

Answer: N! (9!) is a valid upper bound.

Ways this overestimates:

- Wins don't have children

###

The grocery store has apples priced at 5 for a dollar.

You want the most weight of apple for X dollars.

Does the greedy algorithm work? Prove it.

Apples vary in weight by +/- 50%.

--

The greedy algorithm works.

Assume there is an optimal solution that produces a different
result than the greedy solution.

Two solutions:

- Optimal
- Greedy

Assume heaviest apple from Greedy not in Optimal. We can swap that apple into
the optimal solution and it won't make it worse. Repeat inductively.

Confusing:

We can swap out any apple (from the optimal solution) not in the greedy solution
for the heaviest apple we didn't include (which would have been in the greedy
solution). This will either give us more apple, or stay the same.

We want to swap an apple that was in optimal but not in greedy for one that was
in greedy but not in optimal.
