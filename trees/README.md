# Trees (C++)

Implementations of tree structures including unbalance-tolerant Binary Search Trees (BST) and self-balancing AVL Trees.

## Files

| File | Description |
|------|-------------|
| `trees.cpp` | `BST<T>` and `AVLTree<T>` template classes |

## Features

### Binary Search Tree (BST)
- Insertion, search, and node deletion supporting 0, 1, and 2 child node cases.
- Tree statistics: height, minimum element, and maximum element.
- Traversal strategies:
  - In-order (sorted order)
  - Pre-order (hierarchical serialization)
  - Post-order (bottom-up deletion)
  - Level-order (breadth-first search using queue)

### AVL Tree
- Self-balancing binary search tree with node balance factors.
- Implements single rotations (Left, Right) and double rotations (Left-Right, Right-Left).
- Strict O(log n) worst-case time complexity for search, insertion, and deletion.

## Complexity

| Operation | BST (Average) | BST (Worst) | AVL Tree (Worst) |
|-----------|---------------|-------------|------------------|
| Insertion | O(log n)      | O(n)        | O(log n)         |
| Deletion  | O(log n)      | O(n)        | O(log n)         |
| Search    | O(log n)      | O(n)        | O(log n)         |
| Height    | O(log n)      | O(n)        | O(log n)         |

## Build and Run

```bash
g++ -std=c++17 -O2 -o trees trees.cpp
./trees
```
