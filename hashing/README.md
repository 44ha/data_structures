# Hash Tables (C++)

Implementations of hash tables using separate chaining and open addressing (linear probing) collision resolution strategies.

## Files

| File | Description |
|------|-------------|
| `hash_table.cpp` | `HashTableChaining<K, V>` and `HashTableLinearProbe<K, V>` template classes |

## Implementations

### Separate Chaining
- Buckets are represented as singly linked lists of key-value pairs.
- Automatic table growth and rehashing when load factor exceeds 0.75.
- Handles high load factors gracefully without running out of slots.

### Linear Probing (Open Addressing)
- Flat contiguous array storage for improved CPU cache locality.
- State-tracking per bucket (Empty, Occupied, Tombstone/Deleted) to preserve probe chains after deletion.
- Probes sequentially on collision and rehashes when load factor exceeds 0.65.

## Complexity

| Operation | Separate Chaining (Avg) | Separate Chaining (Worst) | Linear Probing (Avg) | Linear Probing (Worst) |
|-----------|-------------------------|---------------------------|----------------------|------------------------|
| Insert    | O(1)                    | O(n)                      | O(1)                 | O(n)                   |
| Lookup    | O(1)                    | O(n)                      | O(1)                 | O(n)                   |
| Delete    | O(1)                    | O(n)                      | O(1)                 | O(n)                   |
| Rehash    | O(n)                    | O(n)                      | O(n)                 | O(n)                   |

## Build and Run

```bash
g++ -std=c++17 -O2 -o hash_table hash_table.cpp
./hash_table
```
