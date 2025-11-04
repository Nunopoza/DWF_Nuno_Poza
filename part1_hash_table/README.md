# Part 1 — Fixed-Size Hash Table with Linear Probing

## Overview
This project implements a **fixed-size hash table** using **linear probing** to handle collisions.
Each key corresponds to a word extracted from *A Tale of Two Cities* by Charles Dickens, sourced from Project Gutenberg.

You can run the program in **two modes**:
1. **CLI Mode** — loads the dataset and tests core hash table functions.
2. **Web Mode** — starts a local web server (http://localhost:8080) to interact with the hash table visually.

---

## Features Implemented
- **`insert(key, value)`** — inserts or updates a key-value pair.  
- **`remove(key)`** — removes a key from the table.  
- **`get(key)`** — retrieves the value for a given key.  
- **`get_first()`** — returns the least recently inserted or modified key.  
- **`get_last()`** — returns the most recently inserted or modified key.  
- **Web interface** for interactive testing.

---

## Build Instructions

### Clone the repository
```bash
git clone https://github.com/Nunopoza/DWF_Nuno_Poza.git
cd part1_hash_table
```

### Build the project
```bash
make
```

This will compile `src/main.c`, `src/hashtable.c`, and `src/webserver.c` into the executable `hash_table`.

---

## Running the Program

### **Mode 1: Command-Line Mode**
```bash
./hash_table 100003 data/98-0.txt
```

This mode loads the entire dataset and performs automated tests for all hash table operations.

### CLI Output Example
```
Loading words from data/98-0.txt...
Dataset loaded successfully.
------------------------------------

Testing hash table operations:

  GET("casting")       -> 108899
  GET_FIRST()          -> "the" -> 0
  GET_LAST()           -> "ebooks" -> 141745
  REMOVE("perplexed")  -> removed
  GET("perplexed")     -> not found

------------------------------------
Execution completed successfully.
```

**Insert your screenshot below:**
> *(Screenshot: Terminal output after running CLI mode)*

---

### **Mode 2: Web Interface**
```bash
./hash_table --web
```
Then open [http://localhost:8080](http://localhost:8080) in your browser.

In this mode, the program automatically loads the dataset (`data/98-0.txt`) and allows you to:

- Search for specific words using `get(key)`  
- Insert new entries manually (`insert(key, value)`)  
- Remove words (`remove(key)`)  
- View the first and last keys (`get_first()`, `get_last()`)  

**Insert your screenshot below:**
> *(Screenshot: Web interface running on localhost)*

---

## Design Highlights

- **Linear probing** for collision resolution, ensuring simplicity and speed.  
- **Constant-time (O(1)) operations** in the average case for `get`, `insert`, and `remove`.  
- **HTML-based web interface** using a lightweight HTTP server (no external dependencies).  
- Automatic dataset loading on `--web` mode from `data/98-0.txt`.

---

## Performance Note

Performance depends on table size and load factor.  
The hash table achieves near O(1) performance under moderate load but may degrade toward O(n) when many collisions occur.

**Insert your screenshot below:**
> *(Screenshot: Performance results or summary if applicable)*

---

## File Structure

```
part1_hash_table/
├── Makefile
├── README.md
├── data/
│   └── 98-0.txt
├── src/
│   ├── main.c
│   ├── hashtable.c
│   ├── hashtable.h
│   ├── webserver.c
│   └── webserver.h
└── tests/
```

---

## Author
**Nuno Poza**  
Advanced Software Testing — May 2024  
