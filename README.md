# DWF_Nuno_Poza — Software Testing Project (May 2024)

## Overview
This repository contains two C-based software testing projects completed as part of the **Advanced Software Testing** module.  
Each part focuses on a specific aspect of algorithmic and system-level development.

---

## Part 1 — Fixed-Size Hash Table
A C implementation of a **hash table** using **linear probing** to resolve collisions.  
The dataset is built from *A Tale of Two Cities* (Project Gutenberg).  

### Highlights
- O(1) average complexity for `insert`, `get`, and `remove`  
- Functions: `get_first()` and `get_last()` track insertion order  
- Optional local **web interface** to explore table operations interactively

Folder: `part1_hash_table/`

---

## Part 2 — Binance Trading Parser
A C application that connects to **Binance Futures API** (`/fapi/v1/aggTrades`) to retrieve and parse aggregated trades.  
It measures parsing performance and can display results in a local web dashboard.

### Highlights
- Uses `libcurl` for API requests and `cJSON` for JSON parsing  
- Calculates performance timing in microseconds per trade  
- Simple **web interface** for symbol and limit configuration

Folder: `part2_binance_api/`

---

## Build Instructions
Each part includes its own `Makefile`.  
To build and run:
```bash
cd part1_hash_table && make
./hash_table 100003 data/98-0.txt
```
or
```bash
cd part2_binance_api && make
./binance_api
```

---
## Author

**Nuno Poza**  
DWF - November 2025


