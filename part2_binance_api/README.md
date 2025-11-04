# Part 2 – Binance API Trade Parser

## Overview
This project implements a **C program** that connects to the Binance USD-M Futures REST API endpoint  
[`GET /fapi/v1/aggTrades`](https://binance-docs.github.io/apidocs/futures/en/#compressed-aggregate-trades-list), downloads a stream of aggregated trades, parses the JSON response, and prints each trade in a readable format.

The parser also measures the execution time per trade using a lightweight timing utility (`timer.h`).

---

## Folder Structure
```
part2_binance_api/
│
├── src/
│   ├── api.h        # Connectivity layer using libcurl
│   ├── api.c
│   ├── parser.h     # JSON parsing with cJSON
│   ├── parser.c
│   ├── timer.h      # Timing utility
│   └── main.c       # Program entry point
│
├── Makefile         # Build and run automation
└── README.md        # Project documentation
```

---

## Build and Run

### Prerequisites
- **gcc** compiler  
- **libcurl** (for HTTP requests)  
- **libcjson** (for JSON parsing)

#### macOS
```bash
brew install curl cjson
```

#### Linux (Debian/Ubuntu)
```bash
sudo apt install libcurl4-openssl-dev libcjson-dev
```

---

### Build
```bash
make
```

### Run
```bash
make run
```

### Clean
```bash
make clean
```

---

## Example Output
```
Running Binance API parser...
Fetching trades from Binance...
Data received. Parsing...

[
  {
    "a": 2928585632,
    "p": "104468.20",
    "q": "0.010",
    "f": 6818390298,
    "l": 6818390298,
    "T": 1762257481769,
    "m": true
  },
  {
    "a": 2928585633,
    "p": "104468.30",
    "q": "0.001",
    "f": 6818390299,
    "l": 6818390299,
    "T": 1762257482076,
    "m": false
  },
  {
    "a": 2928585634,
    "p": "104468.30",
    "q": "0.001",
    "f": 6818390300,
    "l": 6818390300,
    "T": 1762257482194,
    "m": false
  },
  {
    "a": 2928585635,
    "p": "104468.20",
    "q": "0.002",
    "f": 6818390301,
    "l": 6818390301,
    "T": 1762257482248,
    "m": true
  },
  {
    "a": 2928585636,
    "p": "104468.30",
    "q": "0.011",
    "f": 6818390302,
    "l": 6818390309,
    "T": 1762257482368,
    "m": false
  },
  {
    "a": 2928585637,
    "p": "104468.30",
    "q": "0.001",
    "f": 6818390310,
    "l": 6818390310,
    "T": 1762257482522,
    "m": false
  },
  {
    "a": 2928585638,
    "p": "104468.20",
    "q": "0.001",
    "f": 6818390311,
    "l": 6818390311,
    "T": 1762257482562,
    "m": true
  },
  {
    "a": 2928585639,
    "p": "104468.20",
    "q": "0.010",
    "f": 6818390312,
    "l": 6818390318,
    "T": 1762257483191,
    "m": true
  },
  {
    "a": 2928585640,
    "p": "104468.30",
    "q": "0.004",
    "f": 6818390319,
    "l": 6818390319,
    "T": 1762257483681,
    "m": false
  },
  {
    "a": 2928585641,
    "p": "104468.20",
    "q": "0.001",
    "f": 6818390320,
    "l": 6818390320,
    "T": 1762257484083,
    "m": true
  },
]

Parsed 10 trades in 0.253 ms (25.300 µs per trade)
 Execution finished.
```

---

## Implementation Details

### 1. Connectivity Layer (`api.c`)
- Uses **libcurl** to perform an HTTP GET request.
- Implements a custom **write callback** to store the response in a buffer.
- Handles timeouts and user-agent headers for reliability.

### 2. Parsing Layer (`parser.c`)
- Uses **cJSON** to parse the Binance JSON array.
- Iterates through all trade objects and extracts fields:
  - `"a"`: Aggregate trade ID  
  - `"p"`: Price  
  - `"q"`: Quantity  
  - `"f"`: First trade ID  
  - `"l"`: Last trade ID  
  - `"T"`: Timestamp (ms)  
  - `"m"`: Buyer was maker (boolean)

Each trade is printed in JSON format for readability.

### 3. Timer Utility (`timer.h`)
- Uses `clock_gettime(CLOCK_MONOTONIC)` for high-resolution timing.  
- Calculates parsing speed in milliseconds and microseconds per trade.

---

## Integer Overflow Fix

During early testing, the parser printed the same aggregate trade ID (`2147483647`) for all trades —  
the maximum value of a 32-bit signed integer (`2³¹ − 1`).

### Cause
Binance trade IDs and timestamps (`"a"`, `"f"`, `"l"`, `"T"`) exceed the 32-bit integer range.  
Storing them as `int` caused silent overflow and data clipping.

### Solution
All numeric identifiers were changed from `int` to `long long`  
and printed using the `%lld` format specifier.  
This enables 64-bit storage and correct unique ID representation.

**Before**
```json
{
  "a": 2147483647,
  "p": "0.0163",
  "m": true
}
```

**After**
```json
{
  "a": 500239815,
  "p": "68235.10",
  "m": false
}
```

---

## Performance and Complexity

The parsing algorithm runs in **O(n)** time complexity,  
where *n* = number of trade objects in the JSON array.

Each object is parsed once, with constant field extraction cost per trade.  
Memory usage is also **O(n)**, since cJSON loads the full array in memory.

Measured parsing performance on macOS M-series:  
≈ 0.11 ms total for 3 trades (~38 µs per trade).

---

## Conclusion
This project demonstrates how to:
- Connect to a live REST API in C using libcurl  
- Parse structured JSON efficiently using cJSON  
- Measure and reason about algorithmic performance  
- Handle integer overflow and ensure data integrity

All code follows a modular structure and Doxygen-style comments for clarity.

---

## Author

**Nuno Poza**  
Digital World Foundations — Software Development Module  
November 2025
