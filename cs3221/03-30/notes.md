
# Max Flow, Min Cut

Working with a weighted, directed graph.

Source vertex *s* and a target vertex *t*.

## Max Flow

This is the maximum flow from *s* to *t* in the graph, if the flow
is limited by edge weights.

- If we use one path, the limit is the minimum weight on that path.
- A flow *f* is an assignment of a real number x (0 <= x) to every
edge in the graph. A flow is feasible if x <= weight.
- The value of a flow |f| the total net flow out of the source (or,
  equivalently, into t).
- Each intermediate vertex has the same flow in and out.
- We say a flow avoids an edge if it uses 0 capacity.
- A flow saturates an edge if it uses all the capacity.

A max flow is a flow that maximizes |f|.

## Min Cut

A cut is a disjoint partition of the graph into S (including s) and T (including
t).

The capacity of a cut is the sum of the weights of the edges from S -> T.

## Prove: Max Flow = Min Cut

- First, we want to work with reduced graphs, where there is at most one edge
between any two vertices.

Let f be a feasible flow in G. We can define a residual capacity graph as:

- The same vertices.
- An edge for any remaining capacity of an edge.
- A reverse edge for any used capacity.

Now we can look for augmenting paths in the residual graph. An augmenting
path is a path from s to t in the residual graph with positive weight.

If there is an augmenting path, we can add it to the initial flow to
increase the flow.

If there is no augmenting path, the vertices that are reachable from s in
the graph can be the S set in an S / T cut of our graph. The capacity of
that cut must be equal to the max flow we've found so far (or there would
be an augmenting path).

This algorithm is called Ford-Fulkerson.

## Integers

- If all the edge weights are integers, then there's a max flow (min cut)
where all the capacities used of edges are integers. Why?
- For irrational weights, this algorithm may not terminate or even give
useful outputs.

With integer weights, FF runs in O(|E||f\*|) time, where f\* is the actual
max flow.

## How to chose augmenting paths?

Edmonds and Karp suggested two methods:

- Take the path with the largest bottlneck edge.
  - This still has \f* in it.
- Take the path with the fewest edges.
  - This runs in O(|V||E|^2).

## Can we go faster?

Yes. The fastest general purpose algorithm is O(|V||E|).
