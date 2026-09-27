# Heaps (C++)

Array-based binary heap implementations including Max-Heap, Min-Heap, Priority Queue, and Heap Sort.

## Files

| File | Description |
|------|-------------|
| `heaps.cpp` | `MaxHeap<T>`, `MinHeap<T>`, `PriorityQueue<T>`, and `heapSort()` implementation |

## Features

- Array-backed binary tree representation using index math (`2i + 1`, `2i + 2`, `(i - 1) / 2`).
- Sift-up and sift-down algorithms for logarithmic maintenance on push and pop.
- Linear-time O(n) bottom-up heap construction (`heapify`).
- In-place Heap Sort using max-heap without allocating auxiliary buffers.
- Generic Priority Queue abstraction parameterized on element type.

## Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Peek (`top`) | O(1) | O(1) |
| Insert (`push`) | O(log n) | O(1) |
| Extract (`pop`) | O(log n) | O(1) |
| Build Heap | O(n) | O(1) auxiliary |
| Heap Sort | O(n log n) | O(1) auxiliary |

## Build and Run

```bash
g++ -std=c++17 -O2 -o heaps heaps.cpp
./heaps
```
