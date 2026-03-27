
## Last Time: Single Source Shortest Path

- One start vertex
- Find shortest path to each other vertex
- This gives us a tree of paths, rooted at the start

## This Time: All Source Shortest Path

Example:

- We're building a video game.
- There are a bunch of AI NPCS / enemies
- They need to constantly find paths on the map.
- Huge world, complex map.
- Step 1: Build a navigation graph, which is a graph of connectivity
between regions of the world.
- We have no negative distances in our navigation graph.

We want the distances / paths from every vertex *s* to every vertex *t*.

### Plan A: Just run a SSSP algorithm |V| times

- Djikstra's is `O(|E| log |V|)`, so total that's `(|V| * |E| log |V|)`
- In a dense graph, |E| is |V|^2, so we get |V|^3 log |V|.

### Can we beat that by remembering partial paths or something?

We're trying to build up a |V|x|V| table of each distance (u -> v). If we reuse
already computed values that might help.

Let's try a recurrence:

```
dist(u, v) =
  0 if u == v
  dist(u,x) + min weight(x, v) for each edge (u, v)
```

Need to start somewhere:

`dist[u, v] = +inf`

```
dist(u, v, l) =
  0 if u == v and l == 0
  dist(u,x,l-1) + min weight(x, v) for each edge (u, v)
```

```
for i in 1..(|V|-1):
  for each vertex u:
    for each vertex v:
      for each vertex x:
        if there's an edge (x, v):
          if dist[u, x] + weight(x, v) < dist[u, v]:
            dist[u, v] = dist[u, x] + weight(x, v)
```

That's O(|V|^4).

```
dist(u, v, l) = 
    0 if u == v
    weight(u, v) if l == 1 and that edge exits 
    dist(u, x, l/2) + min dist(x, v, l/2) for each known dist u, x and x, v
```

```
for i in 1..ceil(log(|V|)):
  for each vertex u:
    for each vertex v:
      for each vertex x:
        if there are known distances (u, x) and (x, v):
          if dist[u, x] + dist[x, v] < dist[u, v]:
            dist[u, v] = dist[u, x] + dist[x, v] 
```

That's O(|V|^3 log |V|).

## Floyd-Warshall

Instead of splitting on path length, let's arbitrarily number the vertices
1..|V| and add only paths through vertices 1, 2, ..., |V| at each step.

- P(u, v) is true min path length from u -> v
- P(u, v, i) is best path length from u -> v through only verices <= i.

We can see:

- P(u, v, 0) is 0, weight(u, v), or +inf
- P(u, v, 1) adds some correct shortest paths. All non-inf paths
  are length <= 2. For weighted edges, this gives best weight of one edge.
- P(u, v, 2) adds more correct shortest paths, All non-inf paths
  are length <= 3. For weighted edges, this gives best weights for two edges.
- By induction we can show:
  - We get paths for all connectd pairs.
  - These end up being shortest paths at the end.

```
for i in 1..|V|:
  for each vertex u:
    for each vertex v:
        if there are known distances (u, x) and (x, v):
          if dist[u, i] + dist[i, v] < dist[u, v]:
             dist[u, v] = dist[u, i] + dist[i, v] 
```

O(|V|^3) is better than simple Djikstra's if we assume dense graphs.

But, wait, our video game is a sparse graph (|E| is O(|V|)),
so repeated Djikstras would be O(|V|^2 log |V|).

## Funny Matrix Multiplication

ASSP:

```
  for each vertex u:
    for each vertex v:
      for each vertex x:
        dist[u, v] = min(dist[u, x] + weight(x, v))
```

Matrix Multiplication is

```
for k in 1..N:
  for j in 1..N:
    for i in 1..N:
      Y[i, j] += X[i, k] * X[k, j]
```

Matrix multiplication can be optimized down from O(n^3) to like O(n^2.3...)
