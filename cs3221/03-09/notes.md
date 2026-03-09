
## More Graphs

Already defined:

- Graphs
- Vertices and Edges (vertices are sometimes "nodes")
- Directed and undirected
- Adjacency Matrices, Adjacency Lists
- Graph Traversals (DFS, BFS, Best-First Search, etc)

## More Words

- Simple graphs: No self loops or duplicate edges.
- Multigraphs allow that stuff
- If there's an edge u -> v, then v is adjacent to and is a neighbor of u.
- The dgree of a node is its number of neighbors (out-edges).
- A walk is a sequence of vertices where each adjacent pair of vertices in the
  walk are adjacent edges in the graph.
- A path is a walk with no repeat vertices.
- A closed walk starts and ends at the same vertex.
- A cycle is a closed path.
- An acyclic graph contains no cycles.
- A tree is a connected acyclic graph.
- A graph is connected if:
  - It's an undirected graph, you can get there from here.
  - If it's a directed graph, pretend it's undirected, and then
    you can get there from here. (weakly connected)
  - Strongly connected directed: Any node is reachable from any other.
- A subgraph of a graph G has a subset of the edges and a subset
of the vertices.
- A spanning tree of an undirected graph G is a tree that contains
every vertex in G.
- Forest: (A graph consisting of) multiple trees

## Traversals

- We're going to do a depth-first search.
- For a pre-order traversal, visit (e.g. print) each node before
recursing.
- For a post-order traversal, visit (e.g. print) each node after
recursing.

## Depth-First Search

```
DFS(v):
  mark v
  PreVisit(v)
  for each edge (v, w):
    if w is unmarked:
      w.parent = v
      DFS(w)
  PostVisit(v)
```
