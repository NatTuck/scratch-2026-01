
# More Reductions, Because Reductions are Fun

## Review

- A problem is X-hard if we can reduce all problems in X to it.
- A problem is X-complete if we can reduce all problems in X both
from and to it.
- Example X's: P, NP, PSPACE, EXP, etc.
- And there are P-complete problems.

We know:

- 3SAT is NP-complete
- Regex Equivalence is PSPACE-complete

## What problems are P-complete?

For NP reductions (to show NP-hard or NP-complete), we want to transform any
concrete instance of one problem to a concrete instance of another problem in
polynomial time.

So we'd expect to be able to show that a problem is P hard by reducing a
P-complete problem to it in polynomial time. That's not good enough, because
then we could solve the problem during the reduction.

A problem is in P if we can solve it in polynomial time. So we need to do our
reductions in log *space*, which is less than P time.

## Given P-complete problem: The Circuit Value Problem (CVP)

- Given a boolean circuit with AND and OR gates, inputs at the bottom,
output at the top. (do we have NOT? Let's keep going.)
- The bottom layer (where the input are) has fixed inputs.
- What's the one output?

Strategy:

- Start at the bottom layer, evaluate all gates at the next layer up,
repeat for each layer.
- Linear time in the number of gates.

## Another candidate problem: Horn-SAT

This is CNF-SAT, but with a restriction: Every clause can have at most
one positive literal.

Valid clauses:

(a' + b' + c)
(d' + e' + f' + g)
(a' + b)
(a)
(b')

Invalid clauses:

(a + b)     # two positive literals

Algorithm:

- Assume all variables are false.
- That satisfies the expression unless there's a single positive literal.
- When we find a single positive literal, set it true then remove all
negations of that from other clauses and repeat.
- Contradiction = UNSAT
- Finish the process (no more single positive literals) = SAT
- (clauses)*(literals)

Horn SAT clauses encode if / then logical statements:

- a AND b -> c, by De-Morgan's law, is (a' + b' + c)

## Can we reduce CVP to Horn-SAT?

Structure things to be UNSAT if the CVP is true:

- AND gate: (a AND b) outputs c
  - (a1' + b1' + c1)
- OR gate: (a OR b) outputs c
  - a -> c AND b -> c
  - (a2' + c2)(b2' + c2)
- Negate the final output

We can do this in log space: We don't need any space except
for the loop counter: Each gate of input directly outputs
one or two clauses.

## Horn-SAT to CVP?

Build a circuit that does the solving algorithm for
Horn-SAT.

Go through every clause and assign remaining single variables
as true.

We need to do this N times.

So we'll build a circuit with N layers.

A clause that means (a AND b) implies c becomes:

- An AND gate, with a and b as inputs.
- Output into the next layer up.
- Any single input at each layer becomes a 1 input.
- At the final layer, check for contradictions, wired into
a big OR gate.
