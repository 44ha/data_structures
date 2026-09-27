# Linked Lists (C++)

Implementations of singly linked and doubly linked lists with explicit heap management, pointer manipulation, and edge-case handling.

## Files

| File | Description |
|------|-------------|
| `linked_list.cpp` | `LinkedList<T>` (singly linked) and `DoublyLinkedList<T>` (bidirectional with head/tail pointers) |

## Features

- Singly linked list: front/back insertions, indexed insertion and removal, in-place reversal, and element search
- Doubly linked list: O(1) insertions and removals at both ends via head and tail pointers
- Forward and backward traversals
- Destructors ensuring complete memory deallocation without leaks

## Complexity

| Operation | Singly Linked List | Doubly Linked List |
|-----------|--------------------|--------------------|
| Prepend (`push_front`) | O(1) | O(1) |
| Append (`push_back`)   | O(n) | O(1) |
| Pop Front              | O(1) | O(1) |
| Pop Back               | O(n) | O(1) |
| Insert / Remove at `k` | O(k) | O(k) |
| Search                 | O(n) | O(n) |
| Reverse (in-place)     | O(n) | O(n) |

## Build and Run

```bash
g++ -std=c++17 -O2 -o linked_list linked_list.cpp
./linked_list
```
