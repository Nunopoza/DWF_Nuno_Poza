# Part 1 – Fixed-Size Hash Table (C Project)

## Overview

This project implements a **fixed-size hash table** in C using **linear probing** to resolve collisions.  
The hash table stores **key–value pairs**, where the key is a word (string) and the value is an integer.

The dataset is created from the book  
[A Tale of Two Cities](https://www.gutenberg.org/files/98/98-0.txt)  
by Charles Dickens (Project Gutenberg).

The program demonstrates the following operations, all with *O(1)* average-case complexity:

- `insert(key, value)` — inserts or updates a key–value pair  
- `remove(key)` — deletes a key–value pair  
- `get(key)` — retrieves a value by key  
- `get_first()` — returns the first inserted key–value pair  
- `get_last()` — returns the most recently inserted or updated key–value pair  

---

## Folder Structure

```
part1_hash_table/
├── data/
│   └── 98-0.txt           # Dataset (book text)
├── src/
│   ├── main.c             # Program entry point
│   ├── hashtable.c        # Hash table implementation
│   └── hashtable.h        # Header file
├── Makefile               # Build automation
└── README.md              # Project documentation
```

---

## Requirements

- **C Compiler** — GCC or Clang (supports C11 standard)  
- **Make utility** — to build and run the project  
- **Operating system** — Linux, macOS, or WSL on Windows  

---

## Build and Run

### 1. Compile the project

```bash
make
```

This command compiles all source files inside `src/` and produces an executable called `hash_table`.

### 2. Run the program

Make sure the dataset file `98-0.txt` is located in the `data/` folder.

Then run:

```bash
./hash_table 100003 data/98-0.txt
```

Alternatively, you can build **and** run in one step:

```bash
make run
```

### 3. Clean build files

```bash
make clean
```

This removes the compiled binary (`hash_table`).

---

## Example Output

```
====================================
  Fixed-Size Hash Table Demo
====================================

Dataset file: data/98-0.txt
Table size:   100003

Dataset loaded successfully.
------------------------------------

Testing hash table operations:

  GET("casting")       -> 108899
  GET_FIRST()          -> "the" -> 141720
  GET_LAST()           -> "ebooks" -> 141745
  REMOVE("perplexed")  -> removed
  GET("perplexed")     -> not found

------------------------------------
Execution completed successfully.
```

---

## Notes

- The table size (here `100003`) should be a **large prime number** for optimal performance.  
- You can adjust it based on the expected number of unique words in the dataset.  
- The program reads the text line by line, tokenizes it into lowercase words, and inserts each into the hash table.

---

## Author

**Nuno Poza**  
Digital World Foundations — Software Development Module  
November 2025
