
## How hard is the problem?

1. Very Efficient: e.g. O(1), O(log n)
2. Regular Efficient: e.g. O(n), O(n log n)
3. Technically Efficient: e.g. O(n^2), O(n^4)
4. Technically Possible, with imaginary computers: O(2^n)
5. Nope.

## Post Correspondence Problem

We've got a set of string pairs {(a, b), ...}, pick a sequence of items from the
set such that the concatenatoin of first strings equals the concatenation of
second strings.

## Turing Machines

An abstract machine.

We need:

- An alphabet. That's any finite set of symbols. (e.g. {0, 1}, {A .. Z},
{0..10^37}, etc).
- We have a tape, which is an unbounded series of cells. Each tape cell
contains one symbol from the alphabet.
- The machine points to one cell on the tape, and which cell it points
to can be changed by moving the tape on cell at a time.
- We've got a control table, which maps {state, current tape cell symbol}
to {new state, value to write to tape, direction to move}. Direction to
move can be Left, Right, or Halt.

- Input: Intial state of the tape.
- Output: State of tape when we halt.

## The Halting Problem

Turing machines are as powerful as any computer for doing computations.

So we can talk about computer programs instead of Turing machines. This
could be machine code or Python code or whatever.

Can we write a program A that takes a program B as input and outputs
True if B will halt if we run it and False if it doesn't halt?

Example 1:

```
print("Hello, World")
```

Example 2:

```
while True:
  print("Ha, Ha")
```

Example 3:

```
def halts(fun1):
  return True if fun1 halts, else False

def foo(x):
  if x % 2 == 0:
    return x / 2 
  else:
    return 3 * x + 1

def bar(x):
  while x != 1:
    x = foo(x)

i = 2

while True:
  i += 1

  if not halts(lambda: bar(i)):
    break

print(i)
```

Example 4:

- Assume that `halts` exists.
- Then we could write this program, where `troll` has consistent
  behavior and `halts` works.

```
def halts(fun1):
  return True if fun1 halts, else False

def troll():
  if halts(troll):
    loop_forever()
```
