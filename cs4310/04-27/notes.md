
# Dealing with Concurrency and Parallelism

The problem (parallelism):

- Single-core computers don't exist.
- Threads => Shared Memory => Data Races => Locks => Deadlocks
- By default, all parallel programs are wrong.

The problem (parallelism):

- Some programs are logically concurrent, even if there's not
  a performance issue.
- Example: Alice and Bob join a chat server.
- We'd like logical threads, which pulls us back into the same
  problem as with parallelism.

## Primitives and Abstractions

- Threads + Shared Memory
- CPU gives us atomic instructions, which are sufficient
  to build mutexes or hand-rolled lock free data structures.
- But that probably makes our programs wrong and slow.

Some modern programming languages provide mechanisms to allow
for concurrency and/or parallelism without these problems.

What are the conditions for data races?

- Shared Data
- Multiple threads access that data
- At least one thread must write to that data


## Plan A: Concurrency without parallelism

- Basic plan: An event system, where code runs when events happen.
- If all event handlers are fast, this works great.

## Plan B: Eliminate shared data, still have multiple threads

- Idea: Message passing
- Example language: Go
- Example language: Elixir / Erlang

## Plan C: Require that shared data is immutable

 - Example: Rust
 - Next time: Rust demo







