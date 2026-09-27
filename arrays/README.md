# Arrays (C++)

Dynamic array implementations demonstrating manual heap allocation, capacity doubling, element shifting, and custom iterators.

## Files

| File | Description |
|------|-------------|
| `dynamic_array.cpp` | Template `DynamicArray<T>` with copy semantics, insert/erase, resize/reserve, and iterators |
| `vector.cpp` | Lightweight vector template with custom forward iterator |

## Features

- Dynamic capacity doubling when full (amortized O(1) push_back)
- Element insertion and removal with contiguous shifting
- Boundary validation on indexed access
- Range-based for loop support via `begin()` and `end()`
- Binary search for sorted arrays and linear search fallback

## Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Random access (`[]`) | O(1) | O(1) |
| Append (`push_back`) | O(1) amortized | O(1) |
| Insert / Erase | O(n) | O(1) |
| Linear Search | O(n) | O(1) |
| Binary Search | O(log n) | O(1) |

## Build and Run

```bash
g++ -std=c++17 -O2 -o dynamic_array dynamic_array.cpp
./dynamic_array
```
