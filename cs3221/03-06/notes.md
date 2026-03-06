
# We Survived Exam 1

- No awful scores.
- Everyone had a really hard time with the two
recursion tree problems.

## Today: Graphs

A collection of nodes and edges.

We can define a graph as a set of vertices V and a set of pairs of elements in V
(our edges, E). The things that go in the pairs are called vertices.

- If the pairs are ordered, we have a directed graph.
- If the pairs are unordered, we have an undirected graph.

Frequently we draw graphs as circles with lines / arrows between
them.

## Data Structures for Graphs

Three data structures:

- Adjacency matrix: A 2D array (|V|x|V|) of booleans, where a cell in the
grid is set if the edge exists. Size: |V|x|V|
- Adjacency list: An array of |V| lists (typically linked lists) listing
the out-edges from each vertex. Size: |E|
- Direct object representation: Every vertex is an object, and the
edges are object references. Looks a lot like an adjacency list for
performance.

Adjacency list example:

```
A: []
B: []
C: [A, B]
```

## Graph Traversal

"Whatever-first search"

```
print_reachable(graph, seen, v0):
  todo = Set([v0])
  while not empty(todo):
    v = take one from todo
    if not seen.contains(v):
      print(v)
      seen.put(v)
      for each out_edge in graph.edges(v):
        todo.put(out_edge)
```

Specific cases of whatever-first search:

- What if todo is a stack? Depth-first search.
- What if todo is a queue? Breadth-first search.
- What if it's a priority queue? Best-first search.
  - Closest to destination on a map? A*

Everything is a graph.

- Trees, Grids, Anything we can think of as a set of pairs, etc.
