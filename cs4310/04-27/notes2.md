
## Modern computers have multiple cores

Why? Physics

- Power = Frequency^2 (or ^3)
- So for a given power budget, we're looking at being
  able to get more cores easier than faster cores.

### Threads & Locks

- Multiple threads + shared data + any thread writing = data race
- Primary solution: locks
- But locks mean we need to be careful to avoid sequential execution
  and deadlock.

## Our two problems to solve

- Parallelism
  - Get programs to execute (finish) faster with mutltiple cores
- Concurrency
  - Model situations where things happen logically simultaneiously

Example for both: Web server

- Alice requests a 100GB file to download
- Bob requests a 1KB file to download.

## How do we write concurrent / parallel programs

The hardware gives us some tools to help, primarily atomic instructions.

- Example: atomic compare and swap

`int atomic_compare_and_swap(int* mem, int old, int new)`

Atomically do:

```
if *mem == old:
  *mem == new
  return True
else:
  return False
```

This is enough to build locks, but we also can build other stuff.

### Solutions

Multiple threads + shared data + any thread writing = data race

So we can eliminate data races by eliminating any one of those
three conditions.

### JS: Eliminate Multiple Threads

Event callbacks, each callback is atomic.

No actual parallel speedups.

### Eliminate Shared Data

Example: Go, with standard patterns

Thread (goroutines) are supposed to communicate by passing messages
and either transfer ownership or make copies.

### Eliminate Mutability

Example: Rust, by default

If shared data can't be mutated, then there's no problem.

### Ban shared data *and* mutability

Example: Elixir

### Neat idea: Software Transactional Memory

- Allow the data race
- Detect if it happened, and if it did fix it.
