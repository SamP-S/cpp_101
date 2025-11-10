# C++ 101
## Summary
A set of implementations of fundamental computer science data structures and algorithms implemented in C++11.

## Requirements
- Compile for g++
- Header only
- Use minimal std libs
- No external libs
- Malloc memory management
- Always `int` data
- Testing at scientific orders of magnitude until timeout

## Data Structures
Todo:
- Linked List
- Double Linked List
- Binary Search Tree
- Min Heap
- Max Heap
- Priority Queue

## Algorithms
Todo:
- Bubble sort
- Merge sort
- Quick sort


### Sequence Data Structures
Requirements:
- Ordered packed collection of elments
- Access by index
- Support insert/remove at arbritrary index

#### Dynamic Array
Time Complexities:
| Operation            | Best Case       | Average Case    | Worst Case      |
|----------------------|-----------------|-----------------|-----------------|
| Access               | O(1)            | O(1)            | O(1)            |
| Push            	   | O(1)            | O(1) Amortized  | O(n)			 |
| Pop	               | O(1)            | O(1) Amortized  | O(n)            |
| Push Front           | O(1)            | O(n)            | O(n)            |
| Pop Front            | O(1)            | O(n)            | O(n)            |
| Insert Arbitrary     | O(1)            | O(n)            | O(n)            |
| Remove Arbitrary     | O(1)            | O(n)            | O(n)            |

### Queue Data Structures

#### Queue
Time Complexities:
| Operation            | Best Case       | Average Case    | Worst Case      |
|----------------------|-----------------|-----------------|-----------------|
| Access               | O(1)            | O(1)            | O(1)            |
| Enqueue (Push)       | O(1)            | O(1) Amortized  | O(n)            |
| Dequeue (Pop)        | O(1)            | O(1)            | O(1)            |
| Peek Front           | O(1)            | O(1)            | O(1)            |
| Peek Rear            | O(1)            | O(1)            | O(1)            |

