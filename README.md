# 📚 Data Structures in C++

![C++](https://img.shields.io/badge/language-C++-00599C.svg?style=flat-square)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat-square)

A curated collection of fundamental data structures implemented in C++. This repository is designed for educational purposes, offering clean implementations of classic data structures.

---

## 🧠 Implemented Data Structures

- ✅ **AVL Tree** – Self-balancing binary search tree
- ✅ **Binary Search Tree (BST)**
- ✅ **Heap** – Max-Heap
- ✅ **B-Tree**
- ✅ **Suffix Array**

Each data structure is written from scratch to demonstrate key concepts and algorithmic techniques.

---

## 📁 Project Structure

```
Data-Structures/
├── B_Tree.cpp         # B-Tree implementation
├── SuffixArray.cpp    # Suffix Array implementation
├── items.txt          # Sample input for main.cpp
├── main.cpp           # AVL, BST and Heap implementation
└── README.md          # Project documentation
```

---

## 🛠️ Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++`, `clang++`)
- Terminal or IDE like VS Code, CLion, or Code::Blocks

### Compilation

```bash
g++ main.cpp -o main
```

### Execution

```bash
./main
```

Ensure `items.txt` is located in the same directory as the executable.

---

## 🔍 Usage

The `main.cpp` file contains the implementation of **Binary Search Tree**, **AVL Tree**, and **Heap**, along with an `Item` class used to store structured input.

The file `items.txt` provides the input for the data structures in `main.cpp`. Each line in `items.txt` is parsed and inserted into the trees or heap for demonstration purposes.

The other structures — **B-Tree** and **Suffix Array** — are implemented independently in their respective `.cpp` files and can be compiled and tested separately.

---
