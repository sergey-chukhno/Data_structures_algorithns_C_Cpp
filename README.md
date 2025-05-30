# Data Structures and Algorithms in C/C++

This repository contains a collection of classic data structures and algorithms implemented in C and C++. Each file is self-contained and demonstrates a specific algorithm or data structure, with a short annotation at the top of each file explaining its purpose and approach.

## Directory Structure

```
DSA_C_Cpp/
├── binary_search_tree.cpp           # Binary Search Tree (BST) with insert, search, and traversal
├── bst_min_max.cpp                  # Find min and max in a BST
├── queue_array.cpp                  # Queue using a dynamic array (circular buffer)
├── queue_linked_list.cpp            # Queue using a singly linked list
├── stack_array.c                    # Stack using a fixed-size array
├── stack_linked_list.c              # Stack using a singly linked list
├── reverse_string_stack.cpp         # Reverse a string using a stack
├── linked_list_basic.c              # Basic singly linked list with head insertion
├── linked_list_insert_at_n.c        # Singly linked list with insertion at nth position
├── linked_list_delete_at_n.c        # Singly linked list with deletion at nth position
├── doubly_linked_list.c             # Doubly linked list with head/tail insertion
├── reverse_linked_list.c            # Iterative reversal of a singly linked list
├── reverse_linked_list_recursion.c  # Recursive reversal of a singly linked list
├── reverse_linked_list_recursion_alt.c # Alternative recursive reversal of a singly linked list
├── reverse_string_linked_list.cpp   # Reverse a string using a linked list
├── infix_to_postfix.cpp             # Infix to postfix (RPN) conversion using stack
├── infix_to_prefix.cpp              # Infix to prefix (Polish notation) conversion using stack
├── check_balanced_parentheses.cpp   # Check for balanced parentheses using stack
```

## How to Build and Run

Most files are standalone and can be compiled with `g++` (for C++) or `gcc` (for C). For example:

```
# For C++ files
$ g++ binary_search_tree.cpp -o bst && ./bst

# For C files
$ gcc stack_array.c -o stack_array && ./stack_array
```

## Features
- Classic data structures: Stack, Queue, Linked List, Doubly Linked List, Binary Search Tree
- Expression conversion: Infix to Postfix/Prefix
- Parentheses balancing checker
- String reversal using stack and linked list
- Each file is annotated with a brief description of the algorithm at the top

## Contributing
Contributions are welcome! Please open issues or submit pull requests for improvements, bug fixes, or new algorithms.

## License
This project is licensed under the MIT License. 