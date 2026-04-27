
# Exam Topics

## Why are we having an exam?

- The university forces us to do something during the final
exam period.
- This is a math class.
- We want to see if the students learned stuff.
- This material shows up in the future:
  - If you're writing computer programs.
  - You'll take comp theory next semester, this is a legit prereq.
  - If you find yourself in grad school for CS, you are prepared
    for the algo class there.
  - If you're self-studying stuff, this is material you should
    recognize.

## What does the exam need to do?

- Some cumulative material from the previous exams.
- New material: NP reductions

## What to study for reductions

- Be comfortable with the 3-SAT to 3-color reduction.
- Be comfortable with the 3-SAT to Maximum Independent Set reduction.
- Be comfortable with the MIS to MaxClique and MinVertexCover reductions.

## Exam 2 Topics

Q1. For what sort of graph would an adjacency matrix be more space-efficient
than an adjacency list? Why?

A. A densely connected graph.

- Adjacency Matrix is `V*V`, Adjacency list is `V*E`. In a dense graph,
E > V, etc.

Q2. If you do a DFS search and classify edges on a graph with 12 vertices
and 15 edges, how many edges will be tree edges? Prove it.

There will be 11 tree edges. A tree always has V-1 edges in it, and
DFS will build a spanning tree.

Q3. Prove that every tree with directed edges (directed root -> leaves)
has a topological ordering.

We're building a specific ordering for the tree. All edges in the graph
point forward in the ordering. A graph with a cycle has no topological
ordering. This is a tree, so there are no cycles, and that's the only
thing that would prevent a topological ordering.

Q4. Given a connected, weighted, undirected graph G, prove that
for any cycle in G the minimum spanning tree of G excludes the maximum
weighted edge in that cycle.

If we have a cycle, we can turn it in to a minimum spanning tree
by removing one edge.

- Assume you have a spanning tree that includes the maximum weighted
  edge in the cycle.
- Swap that for the missing edge from the cycle.
- The maxium weight edge has a weight >= the new one.
- Therefore the new cycle is no worse.
- If there are multiple maximum edges, all we can show is that one
of them is excluded.

Q5. You are given a connected, undirected graph G with weighted
edges and a minimum spanning tree T of G. The weight of a single
edge e is decreased. Describe an algorithm to update the minimum
spanning tree efficiently.

- If e is in the spanning tree, we're done.
- Otherwise:
  - Add it to the tree.
  - That added a cycle.
    - Search all edges with breadth-first search to find the cycle.
    - Thats O(E)
  - Find the max edge in the cycle and remove it.
  - That's as efficient as we can get, consider a big loop graph.

Q6: Describe and analyze and alorithm to compute the maximum weight
spanning tree of a given edge-weight graph G.

- Inverse Dijkstra's (Dijkstras, just with negated edge weights)
- As long as there's no cycles, this is fine.
  - Just don't repeat vertexes.

Q7: You are given a directed graph with edge weights that may be
negative. Describe an algorihtm to determine whether there exists a path
from s to t with total weight exactly equal to k, assuming you only
need to answer yes/no.

- Plan A: Breadth first search starting at s for a path of length k to t.
- Program won't terminate if there's no answer.
