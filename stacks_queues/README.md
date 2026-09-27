# Stacks and Queues (C++)

Implementations of LIFO, FIFO, and double-ended queue abstractions using node-based allocation.

## Files

| File | Description |
|------|-------------|
| `stacks_queues.cpp` | `Stack<T>`, `Queue<T>`, and `Deque<T>` template classes |

## Implementations

### Stack (LIFO)
- Operations: `push(val)`, `pop()`, `top()`, `empty()`, `size()`
- Singly linked list backing with top-pointer for O(1) push and pop.

### Queue (FIFO)
- Operations: `enqueue(val)`, `dequeue()`, `front()`, `back()`, `empty()`, `size()`
- Singly linked list with `front` and `rear` pointers for O(1) insertions and removals.

### Deque (Double-Ended Queue)
- Operations: `push_front()`, `push_back()`, `pop_front()`, `pop_back()`, `front()`, `back()`
- Doubly-linked node architecture with constant-time operations on both extremities.

## Complexity

| Operation | Stack | Queue | Deque |
|-----------|-------|-------|-------|
| Insert | O(1) | O(1) | O(1) |
| Remove | O(1) | O(1) | O(1) |
| Peek   | O(1) | O(1) | O(1) |
| Space  | O(n) | O(n) | O(n) |

## Build and Run

```bash
g++ -std=c++17 -O2 -o stacks_queues stacks_queues.cpp
./stacks_queues
```
