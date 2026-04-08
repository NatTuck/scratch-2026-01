
## Exam 2 is in a couple of days

Question 1a:

- Prove that if you have a tree and add an edge, the resulting graph isn't a
  tree.

- Plan A: A tree has |V|-1 edges. Adding an edge is a different number.

- Plan B: A tree is a connected, acyclic graph.
  - Because it's connected, there's a path from the root to every node.
  - Adding an extra edge, now we've got an extra path.
  - If there's two distinct paths to a node from the root there must be a cycle,
    because we can go down one path and up the other.

Question 1b:

- Prove that if you have a tree and remove an edge, the resulting graph isn't a
  tree.

- Plan A: A tree has |V|-1 edges. Removing an edge is a different number.
  - Tree is a minimally connected graph,

- Because it's connected, it must have at least |V|-1 edges or it wouldn't be
  connected.
- Why didn't it start with more than |V|-1? Because it's acyclic, see 1a.

Question 2:

The diagram is the result of a DFS tree that could have been gotten from a DFS
started at vertex s.

For another possible traversal starting at s, could the back edge instead have
been a forward edge?

- Is the origional graph directed?
  - If we assume it was a directed graph, then no, because it's going the
     wrong way and ends at the start vertex.
  - If we assume it was not directed. If it were a tree edge, it's not forward.
     Because we went s to t and there's no other path to get to u, it's still
     a back edge. (We know it is directed.)

Can the same edge be a back edge in one DFS traversal and a forward edge
in another traversal?

- A back edge can be a tree edge.
- A back edge can be a forward edge.

## MST

Consider the following MST algorithm for an undirected graph with integer
weighted edges:

- Replace each edge with weight w in the graph with a string of w edges
with intermediate vertices.
- Do a breadth-first search.
- The first path connecting original vertices is an edge in the MST.

Prove correct. Or wrong. If wrong, fix.
