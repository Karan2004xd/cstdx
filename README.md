## cstdx 

A lightweight, high-performance utility library extending the C programming language with modern data structures, memory management, and system utilities.

> ⚠️ **Project Status:** `cstdx` is currently a work-in-progress (WIP). Active development happens on the [`dev`](https://github.com/Karan2004xd/cstdx/tree/dev) branch.

---
## Overview

The standard C library leaves much of the heavy lifting, like dynamic arrays, hash tables, and smart memory management, to the developer. **cstdx** aims to bridge this gap by providing a rich, production-ready set of data structures and utilities without replacing standard C features.

Every module is designed to be rigorously tested, memory-safe, and benchmarked against standard approaches.

---
## Planned Features

### Data Structures
* **Array:** Dynamic, contiguous memory container supporting generic types, iterators, custom growth factors, and sorting (similar to C++ `std::vector`).
* **String:** Dynamic string container with built-in resizing, slice operations, and integrated **String Builder** support.
* **Hash Map:** Key-value store featuring pre-defined hash functions for primitive types, custom hashing support, and configurable collision resolution (similar to C++ `std::unordered_map`).

### Memory Management
* **Arena Allocator:** Fast region-based bump allocator for rapid allocation and $O(1)$ batch deallocation.
* **Auto Cleanup Pointers:** Smart pointer utilities where the caller will not need to deal with raw pointers and the can have clear ownership rules defined as well while not worrying about memory leaks or clean up. (Similar to smart pointers in C++).

### Tooling & System Utilities
* **CLI Argument Parser:** Robust option parsing with strong error reporting, auto-generated help menus, and positional argument support.
* **Tokenizer:** Fast lexing engine supporting direct file streaming, customizable rules, and zero-copy token views.
* **File System Explorer:** Cross-platform directory traversal, file metadata extraction, and path manipulation (similar to C++ `std::filesystem`).

---
## Getting Started

*(Build instructions, dependencies, and code examples will be added as core features land on the `dev` branch)*
