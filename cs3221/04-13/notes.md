
# Why SAT exciting?

If P=NP and we had a polynomial time algorithm for SAT...

## We could break cryptographic algorithms

Cryptographic hash algorithms.

**SHA256**

- A function from an array of bytes to an array of 32 bytes.
- One key property: Given an output, you can't figure out the
  input.
- Critical for digital signatures and other stuff.
- It's a block algorithm, so it operates on the first X bytes
  of the input, then the next with the output of the previous block,
  etc.

Block ciphers.

**AES**

- A function from (plaintext, key) to cyphertext.
- A function from (cyphertext, key) to plaintext.

## 3SAT

Given a boolean formula in conjunctive normal form with exactly three literals
per clause:

- Decision problem: Can it be satisfied?
- Solution problem: Find an assignment of variables that satisfies it.
- (satisfies = output is true)

This is also NP-hard. We can reduce from CircuitSAT.

- Make sure every AND or OR has exactly two inputs.
- Every wire is a variable.
- That gives us one clause per gate (a = bc, a = b + c, or a = 'b)
  - a = ab    => (a+b'+c')(a' + b)(a' + c)
  - a = b + c => (a'+b+c)(a+b')(a+c')
  - a = 'b = (a+b)(a'+b')
- We can expand two variable clasues into three variable clauses like this:
  - (a+b) = (a+b+x)(a+b+x')

This transformatoin takes linear time and produces an ouptut that's biggre
than the input by a constant factor.

## Maximum Independent Set

Given a simple, unweighted, undirected graph G. An independent set in G is a
subset of the vertices of G with no edges between them.

Solution problem: What's the largest independent set in G?

Decision problem: Given an integer *k*, is there an independent set of
size >= *k*?

We'll reduce 3SAT to this.

- We've got to come up with a way to translate any instance of 3SAT to
some instance of MIS in poly time.
- Then we imagine solving our MIS instance, optimally with a shiny new
poly time algorithm.
- At this point, the decision problem is solved.
- Then we translate the solutoin back to 3SAT to get our actual solution.

Reduction:

- Each clause in the 3SAT instance becomes three new vertices with
edges connecting them into a triangle.
- Our MIS vertices will correspond to a set of variables that, if true,
satisfy the 3SAT instance.
- In order to prevent both a and a' from being true, add an edge from very
variable to every negating vertex for that variable.

If we solve the MIS instance, we've solved the 3SAT problem.

Therefore MIS is NP-hard

## Words

- Any problem is in NP if a proposed solution can be verified in polynomial
time.
  - 3 + 5?
- It's NP-hard if solving it would let us solve *all* problems in NP.
- It's NP-complete if it's in NP and it's NP-hard.

## Proving NP hard vs NP complete

To prove that X is NP hard:

- Reduce a known NP-hard problem to X.

To prove that X is NP-complete:

- Prove it's in NP.
- Prove that it's NP-Hard.
