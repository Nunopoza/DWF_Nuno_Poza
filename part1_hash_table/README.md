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
---

### **Mode 2: Web Interface**
```bash
./hash_table --web
```
Then open [http://localhost:8080](http://localhost:8080) in your browser.

In this mode, the program automatically loads the dataset (`data/98-0.txt`) and allows you to:

## Search for specific words using `get(key)`
<img width="887" height="254" alt="Captura de pantalla 2025-11-04 a las 16 32 13" src="https://github.com/user-attachments/assets/f4448c92-d606-4e38-b69f-1f7f1f93a0d0" />

## Insert new entries manually (`insert(key, value)`)  
<img width="884" height="276" alt="Captura de pantalla 2025-11-04 a las 16 31 43" src="https://github.com/user-attachments/assets/c790eaab-1738-4dd3-96a6-373a9d330ebf" />

## Remove words (`remove(key)`)  
<img width="888" height="266" alt="Captura de pantalla 2025-11-04 a las 16 31 59" src="https://github.com/user-attachments/assets/58b96efe-7415-47b5-8bef-dbc58b50eccf" />


## View the first and last keys (`get_first()`, `get_last()`)  
<img width="897" height="253" alt="Captura de pantalla 2025-11-04 a las 16 26 35" src="https://github.com/user-attachments/assets/8a9f4bdb-97dc-4a18-8b0a-a36ca64fc4ea" />
<img width="880" height="252" alt="Captura de pantalla 2025-11-04 a las 16 31 23" src="https://github.com/user-attachments/assets/54946f71-2bc7-4bfa-9364-3d73ae55aec7" />

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

## File Structure

```
part1_hash_table/
├── Makefile
├── README.md
├── data/
│   └── 98-0.txt
├── src/
    ├── main.c
    ├── hashtable.c
    ├── hashtable.h
    ├── webserver.c
    └── webserver.h
```

---

## Author

**Nuno Poza**  
DWF
Part 1 — Fixed-Size Hash Table with Linear Probing (2025)
