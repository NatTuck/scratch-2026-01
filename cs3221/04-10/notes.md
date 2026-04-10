
# Today: P vs NP

Complexity classes:

- O(5), O(log n), O(n), O(n^2), O(n^30), O(2^n)

## Decision Problems

A decision problem is a problem with a yes/no answer.

Examples:

1. Given a list of integers, are there any duplicates?
2. Given a graph and two vertices, s and t, is there a path from s to t?
3. Given a boolean logic circuit with N inputs and one output, is there
an assignment of values to the inputs that will make the output true?
4. Given a graph is there a cycle that visits each vertex exactly once?

# Class P, or Polynomial Time

## Duplicate integers?

seen = new HashSet()
for x in xs:
  if x in seen:
    return true
  seen.append(x)
return false

This is O(n^2), or maybe O(n)

## Is there a path?

- Run bread first search.
- O(|E|) = O(|V|^2)

# Class NP, Deterministic Polynomial Time

## Satisfying assignment to boolean circuit? CircuitSAT

1. Given a boolean logic circuit with N inputs and one output, is there
an assignment of values to the inputs that will make the output true?

Plan A: Brute Force / Search / Backtracking

- Pick an assignment
- Try it
- If true, done
- If false, maybe another input will work, keep going

O(2^n)

Can we do better?

Imagine we had a magical computer that could:

- Copy the entire universe every time it needs to do
multiple recursions in a search, recursively.
- Once we have a yes answer, return that.
- Delete all the universe copies that weren't the first "yes" answer.

That computer can solve this problem in O(n) time.

Alternate formulation:

- At each step in the recursion the computer can consult a magical
oracle that gives it the correct guess for the next step.

A problem that can be solved in polynomial time with a non-deterministic
computer is in a class called NP. Equivalently, the class of problems where we
can *verify* a solution in polynomial time is NP.

Recall, P is the class of problems that we can solve in polynomial time.

The big question of computer science: Does P = NP?

## NP-Hard

A problem that is NP hard has an interesting property:

- If this problem can be solved in polynomial time then
- Any other problem in NP also can be solved in polynomial time.

CircuitSAT is NP-Hard, as are a bunch of other problems.

CircuitSAT is NP-Complete.

## Another NP-Hard Problem: SAT

If we have an arbitrary boolean formula in CNF-form (e.g. (A+B)(A+'B)(A+C))
is there a satisfying assignment (variable assignments that make the formula
true)?

To prove that SAT is NP hard, we must reduce a known NP-Hard problem to
this new problem.

So we need to:

- Describe an algorithm to convert any instance of CircuitSAT to SAT
in polynomial time.
- Describe an algorithm to translate the solution back in polynomial time.

Translating from circuit sat:

Each gate becomes an equality.

Then, each equality:

- a = bc
  - (a+b'+c')(a'+b)(a'+c)
- a = b + c
  - (a'+b+c)(a+b')(a+c')
- a = b'
  - (a+b)(a'+b')

# For the fun

## Hamiltonian Path

1. Given a graph is there a cycle that visits each vertex?

If somone proposed a cycle, could we check their proposal in polynomial time?

See if you can figure this out over the weekend.
