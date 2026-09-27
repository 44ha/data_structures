# Graphs (C++)

Adjacency-list graph implementations supporting directed, undirected, and edge-weighted representations.

## Files

| File | Description |
|------|-------------|
| `graph.cpp` | `Graph` (unweighted graph operations) and `WeightedGraph` (Dijkstra shortest path) |

## Features

- Adjacency list storage using vectors of vectors.
- Graph traversals:
  - Breadth-First Search (BFS) using queue
  - Depth-First Search (DFS) recursive traversal
- Directed Acyclic Graph (DAG) tools:
  - Cycle detection using three-state recursion tracking
  - Topological sort using Kahn's in-degree BFS algorithm
- Weighted graph shortest path:
  - Dijkstra's algorithm with min-priority queue for non-negative weights

## Complexity

| Algorithm | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| BFS Traversal | O(V + E) | O(V) |
| DFS Traversal | O(V + E) | O(V) |
| Cycle Detection | O(V + E) | O(V) |
| Kahn Topological Sort | O(V + E) | O(V) |
| Dijkstra Shortest Path | O((V + E) log V) | O(V) |

`V` denotes number of vertices, and `E` denotes number of edges.

## Build and Run

```bash
g++ -std=c++17 -O2 -o graph graph.cpp
./graph
```
