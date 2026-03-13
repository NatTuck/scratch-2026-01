
## Minimum Spanning Trees

Every connected undirected graph has a spanning tree. For example, we
can generate one by doing DFS and keeping the tree edges.

Let's consider:

- A connected, undirected graph with weighted edges.

### How to find MST

- We'd like unique MST.
- We have a unique MST if we have unique edge weights.
- Given N integer weighted edges, we can make them unique by
replacing the weight of each edge i with `weights[i] + i/(10^n)`.

## Generic MST algorithm

- Maintain an acyclic subgraph F of the input graph G, the "intermediate
forest". This is also a subgraph of the result MST.
- Initally, F contains all vertices and no edges of G.
- We connect trees by adding edges.
  - Which edges? Safe edges.
- When the algorithm halts, we've added enough edges to F that it's the MST.
- We don't want to add any edges not in the MST.

Pay attention to two kinds of edges:

- An edge that connects two vertices that are already in a connected compoent
of F is *useless*.
- An edge with exactly one endpoint in a component of F is *safe* if it's the
minimum weight edge like that for that component.

**Lemma (Prim)**: The minimum spanning tree of G contains every safe edge.

- We're dealing with a undirected connected graph with unique weights.
- Let S be an arbitrary subset of the vertices of G.
- Let e be the lightest edge with exactly one endpoint in S.
- Let T be an arbitrary spanning tree that does not contain e.
- To prove: T is not the MST of G.
- Because T is connected, it contains a path from one end of e to the other.
- Becasue the path starts at a vertex of S and ends at a vertex not in S (by def
of e), it must contain at least one edge with exactly one endpoint in S. Call
that edge e'.
- We can swap e in for e'.

**Lemma**: The minimum spanning tree contains no useless edges.

That'd be a cycle. By definition, a MST (which is a tree) has no cycles.

### Generic algorithm summary

- Identify a safe edge
- Add it to F.
- Repeat until F is connected.

### Boruvka's Algorithm

- Count the components in the graph F, label each vertex with its component
  (e.g. the first one we found is `#0`, the second `#1`, etc).
- For each component, start with a null safe edge.
- For each edge (u, v), if the edges are in different components:
  - If this is lighter than `safe_edges[u.component]`, it's our new safe
  edge for that component.
  - Same for `safe_edges[v.component]`
- We've got a safe edge for each component. Add all of them to the graph.
- Repeat.

Running time:

- We can count and label components in O(|V|) time.
- Our loop loops through all the edges (thats O(|E|) iterations).
- The graph is connected, so we know |V| in O(|E|)
- Each iteration, at worst, cuts the number of components in half, so
  number of iterations is O(log |V|).
- Total is O(|E| log |V|).

### Jarnik's (Prim's) Algorithm

- Initalize an empty priority queue Q.
- Intialize an empty subtree T.
- Take an arbitrary vertex and add it to T.
  - Add its edges to Q.
- Repeatedly take lowest-weight edge from Q and, if it has one end in T:
  - Add the edge to T
  - Add the edges of the next vertex to Q.

Priority queue ops are probably O(log n), so total ends p being O(|V| log |E|).

### Kurskal's Algorithm

- Sort E by increasing weight  (this takes O(|E| log |E|)).
- Add each vertex to a separate set.
- For each edge (u, v) in (sorted) E:
  - If u and v are in different sets, merge (union) the two sets together.
  - Add (u, v) to F.
- Because we're looking at edges in increasing weight order, we'll add
all safe edges (unsafe edges get considered after they're useless).

This set stuff needs a custom data structure that:

- Can initalize our sets with single items.
- Can quickly determine if u and v are in the same set.
- Can quickly merge (union) two sets together.

This class of structure is called a disjoint set structure or a union-find
structure.

How can this work:

- Store a forest (each tree is one set).
- The trees in the forest are trees with pointers going leaf -> root direction,
 so parent pointers. Each node also has a node ID.
- To get fast lookup, we store a hash table of node ID to the associated
tree node.
- New set: Check if in hashtable, else allocate new node.
- Find is hash table lookup and then follow parent pointers to root. Component /
  set ID is the ID of the root of that tree.
- Union is setting the parent of one root to the other root.
- To speed up traversals, we reparent every node to the current root of that
  tree during each traversal.

```
struct node {
  struct node* parent;
  int node_id;
}
```
