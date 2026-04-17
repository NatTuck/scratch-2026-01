
# What problem is NP-hard but not NP-complete?

## Regular Expressions

A way to search / compare text by matching patterns.

Rules:

- A literal character (e.g. "a") matches itself.
- A sequence of regular expressions connected directly
matches those patterns in that order. (e.g. "ab" matches "ab").
- A sequence of regular expressions connected with pipes can
match either the first or second thing. (e.g. "a|b" matches "a" or "b").
- We can use parens for grouping. (e.g. "(a|b)(cd)" matches the strings
in the set {"acd", "bcd"}.
- A regex followed by a star matches 0 or more of the previous item. This
lets us match infinite sets.

Examples:

- "(ab|cd)*z":   "abcdz"?

Our problem now: Regex equivalence (or non-equalence)

Do these two regexes describe the same set:

- "a(aa)*a"
- "(aa*)*"

Counter-example: "" (matches second, not first), "a", "aaa"

"((aa)*(bb*)(c|(def*)))*"

## Decision Problems

Our regex equivalence decision problem is:

- Given two regexes A and B, are they equivalent?

- If we say yes or no, that's great, but we'd usually like to be able to prove
it.
- For problems in NP, we can do that by showing evidence of our claim (called a
"certificate"), which is polynomial size and can be checked in polynomial time.
- For 3SAT, a certificate is a proposed variable assignment that satisfies the
expression.
- To check if a string matches a regex, that takes polynomial time.

- But proving that two regexes are the same is harder. A simple certificate
might be infinite size - just listing both sets exhaustively.

This ends up being in a class called PSPACE.

- We can solve the problem in polynomial *space*.
- Our classes are O(1) = O(1) space <= LOG <= LOGSPACE <= P <= NP <= PSPACE <= EXP <= EXPSPACE <= ...

Let's try to do some reductions:

We're going to reduce 3SAT to polynomial non-equivalence.

- Given a 3SAT formula we want to construct two regular expressions.
- If the regexes are *not* equivalent, then the formula is satisfiable.

Our 3SAT instance has N variables.

A assignment is represented as a string of N 0's and 1's, with the first
digit being the first value, etc. (0 = false)

Our first regular expression (RX1) matches all possible variable assignments of
length N: "(0|1)(0|1)...(0|1)" (N sets of parens).

Our second regular expression is the regex that matches all assignments that
falsify our 3SAT expression.

A 3SAT expression is false if at least one clause is false.

Consider: (V1 ^ V2' ^ V4)

We can match an assignment that falsifies it with:

(0(0|1)(0|1)(0|1) | (0|1)1(0|1)(0|1) | (0|1)(0|1)0)

Or one of these together for each clause, thats RX2.

If the 3SAT formula is satisfiable:

- Then it doesn't match RX2.
- And RX2 != RX1
  
If it's not satisfiable:

- It does match RX2.
- And RX1 == RX2 because there's no solution.
