
## Exam Questions

### Asymptotic Complexity Basics

For each of the following functions, give big-Theta class:

- f(n) = 5n^3 + 2n^2 + 100  ; so f(n) is Theta(n^3)
- f(n) = log2(n) + sqrt(n)  ; so f(n) is Theta(sqrt(n))
  - so f(n) is O(sqrt(n))
  - so f(n) is Omega(sqrt(n))
- f(n) = 2^(n+1) ; so f(n) is Theta(2^n)
- f(n) = n! / 1000  ; so f(n) is Theta(n!)

## Asymptotic complexity proof

Prove that n^2 + 10n + 100 is Theta(n^2).

Definition of Theta(f) is O(f) AND Omega(f).

f(n) is O(g(n)) means:

O: There exists some c, n0 such that `f(n) <= c*g(n)` for all n > n0.

n0 = 10
c  = 3

f(11) = 121 + 110 + 100 = 331 <= 3 *(g(11) = 11^2 = 121) = 363
f(12) = 144 + 120 + 100 = 364 <= 3* 12^2 = 432

f breaks into three parts:

- n^2 (we can ignore this)
- 10n
- 100

`3*g` breaks into three parts:

- n^2 (we can ignore this)
- n^2
- n^2

Induction: Base case, prove for x = 11.

Inductive step:

- Prove that if it's true for x, it's true for x + 1.
- What we're're're are proving:  f(x) < 3 * g(x)

`f(x+1) - f(x) < 3 * g(x+1) - 3 * g(x)`

After deleting one x^2 term from each:

```
(10(x+1) + 100) - (10x + 100)

<

2 * (x+1)^2 - 2 * (x^2)
```

Just handle the 100's

```
(10(x+1)) - (10x) = 10

<

2 * (((x+1)(x+1)) - (x*x)) = 

 (x^2 + 2x + 1) - x^2 = 4x+2
```

For all x > 11

Omega: There exists some c, n0 such that `f(n) >= c*g(n)` for all n > n0.
