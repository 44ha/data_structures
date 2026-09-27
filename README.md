# Data Structures in C++

Clean implementations of fundamental data structures in modern C++ (C++17), written without relying on container libraries. Each directory contains self-contained code with runnable examples and tests in `main()`.

## Directory Overview

| Directory | Data Structures / Algorithms |
|-----------|------------------------------|
| [arrays/](arrays/) | Dynamic array (vector equivalent) with capacity doubling and bounds checking |
| [linked_lists/](linked_lists/) | Singly linked list and doubly linked list with full node management |
| [stacks_queues/](stacks_queues/) | Stack (LIFO), Queue (FIFO), and double-ended queue (Deque) |
| [trees/](trees/) | Binary Search Tree (BST) and self-balancing AVL Tree with rotations |
| [heaps/](heaps/) | Min-heap, max-heap, priority queue, and in-place heapsort |
| [graphs/](graphs/) | Adjacency-list graph with BFS, DFS, Dijkstra, cycle detection, and topological sort |
| [hashing/](hashing/) | Hash table with separate chaining and open addressing (linear probing) |

## Building and Running

Compile any source file directly with a C++17 compiler:

```bash
g++ -std=c++17 -O2 -Wall dynamic_array.cpp -o dynamic_array
./dynamic_array
```

On Windows:
```cmd
g++ -std=c++17 -O2 -Wall dynamic_array.cpp -o dynamic_array.exe
dynamic_array.exe
```

## Complexity Reference

### Arrays & Linked Lists
| Operation | Dynamic Array | Singly Linked List | Doubly Linked List |
|-----------|---------------|--------------------|--------------------|
| Indexing  | O(1)          | O(n)               | O(n)               |
| Search    | O(n)          | O(n)               | O(n)               |
| Insert Front | O(n)       | O(1)               | O(1)               |
| Insert Back  | O(1) amortized | O(n) (or O(1) with tail) | O(1)     |
| Delete Front | O(n)       | O(1)               | O(1)               |
| Delete Back  | O(1)       | O(n)               | O(1)               |

### Trees & Heaps
| Structure | Search | Insert | Delete | Space |
|-----------|--------|--------|--------|-------|
| BST (average) | O(log n) | O(log n) | O(log n) | O(n) |
| BST (worst)   | O(n)     | O(n)     | O(n)     | O(n) |
| AVL Tree      | O(log n) | O(log n) | O(log n) | O(n) |
| Binary Heap   | O(n)     | O(log n) | O(log n) | O(n) |

### Hash Tables
| Variant | Average Lookup | Worst Lookup | Load Factor Rehash |
|---------|----------------|--------------|--------------------|
| Separate Chaining | O(1) | O(n) | > 0.75 |
| Linear Probing    | O(1) | O(n) | > 0.70 |
