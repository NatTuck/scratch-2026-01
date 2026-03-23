
# Some Functions

```
def logstar(n):
  if n <= 1:
    return 0
  else:
    return 1 + logstar(log2(n))
```

## Single Source Shortest Path

The problems:

(1) We have:

- A weighted, directed graph.
- Some source vertex, *s*.
- Some target vertex, *t*.

Want to find the shortest path from s to t.

(2) We have:

- A weighted, directed graph.
- Some source vertex, *s*.

Want to find the shortest path from s to every vertex in the graph.

**Path Tree**

Problem (2) gets us a tree rooted at *s*. Why?

**Problem: Negative Edges**

When we talk about "shortest path", we typically wanted to say "shortest walk".

## The Algorithm

We'll solve both variant (1) and (2) the same way. If we're only looking for a
path to one target, we stop when we get it.

Setup:

- An array `dist[]` gives the shortest distance found so far from *s* to each
vertex. Init each to +inf.
- An array `pred[]` gives the predecessor note in that candidate shortest path.
  Init each to null.

Tense edges:

- An edge (u, v) is tense if `dist[u] + weight(u, v) < dist[v]`. In that case,
s -> u then (u, v) is better than the previous best path to get to v.
- We can relax a tense edge by updating our best path to v to use that edge (set
  both `dist[v]` and `pred[v]`.

The generic algorithm:

- While there are tense edges, relax some (at least 1) of them.

Notes:

- An edge (u, v) can only be tense if we already have a distance (and path) to
  u.
- Initially, only edges from s are tense.
- We should be able to prove that this process (repeated relaxation) leads to
  shortest paths by contradiction. Can we?
- We might need to assume positive edge weights. Most require no negative
  cycles.

Assume we have no tense edges and our best path is length x. There is some
shortest path of length < x. Why contradiction?

## Specific Case: Unweighted Directed Graph

Breadth-first search.

Start with:

- An array `dist[]` gives the shortest distance found so far from *s* to each
vertex. Init each to +inf.
- An array `pred[]` gives the predecessor note in that candidate shortest path.
  Init each to null.

We hit vertices in distance order, so `dist[v] != inf` is the same as our
visited map for simple BFS. Pred is write-once.

## Specific case: DAG (weighted)

Because no cycles, we can write down a formal recurrence:

- We have `dist[v] = 0` if v = s.
- Otherwise, `dist[v] = min((for each u) dist[u] + weight(u, v))`

This lets us do dynamic programming.

## More generally: Dijkstra's Algorithm

This is just best-first search. We swap out the breadth first queue with a
priority queue on `dist[u] + weight(u, v)`.

## Most simply: Bellman-Ford

```
until we run out of tense edges:
  for each edge (u, v):
    if tense, relax(u, v)
```
