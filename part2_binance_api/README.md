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
    "a": 2928726317,
    "p": "103885.70",
    "q": "0.809",
    "f": 6818745628,
    "l": 6818745640,
    "T": 1762263261130,
    "m": false
  },
  {
    "a": 2928726318,
    "p": "103885.60",
    "q": "0.050",
    "f": 6818745641,
    "l": 6818745654,
    "T": 1762263261181,
    "m": true
  },
  {
    "a": 2928726319,
    "p": "103885.70",
    "q": "0.038",
    "f": 6818745655,
    "l": 6818745657,
    "T": 1762263261205,
    "m": false
  },
  {
    "a": 2928726320,
    "p": "103885.70",
    "q": "0.010",
    "f": 6818745658,
    "l": 6818745659,
    "T": 1762263261337,
    "m": false
  },
  {
    "a": 2928726321,
    "p": "103885.60",
    "q": "0.001",
    "f": 6818745660,
    "l": 6818745660,
    "T": 1762263261504,
    "m": true
  },
  {
    "a": 2928726322,
    "p": "103885.70",
    "q": "0.077",
    "f": 6818745661,
    "l": 6818745663,
    "T": 1762263261508,
    "m": false
  },
  {
    "a": 2928726323,
    "p": "103885.60",
    "q": "0.001",
    "f": 6818745664,
    "l": 6818745664,
    "T": 1762263261612,
    "m": true
  },
  {
    "a": 2928726324,
    "p": "103885.70",
    "q": "0.132",
    "f": 6818745665,
    "l": 6818745666,
    "T": 1762263261642,
    "m": false
  },
  {
    "a": 2928726325,
    "p": "103885.60",
    "q": "0.001",
    "f": 6818745667,
    "l": 6818745667,
    "T": 1762263261718,
    "m": true
  },
  {
    "a": 2928726326,
    "p": "103885.70",
    "q": "0.079",
    "f": 6818745668,
    "l": 6818745668,
    "T": 1762263261823,
    "m": false
  },
]

--- Summary ---
Total trades: 10
Price range: 103885.60 → 103885.70
Average quantity: 0.119800
Maker ratio: 40.0%

Parsed 10 trades in 0.281 ms (28.100 µs per trade)
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
