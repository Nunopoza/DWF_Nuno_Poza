# Binance Futures Trade Parser (Part 2)

This project implements a **C program** that connects to the Binance USD(S)-M Futures REST API endpoint  
[`GET /fapi/v1/aggTrades`](https://binance-docs.github.io/apidocs/futures/en/#compressed-aggregate-trades-list),  
downloads a stream of aggregated trades, parses the JSON response, and prints each trade in a readable format.

In this enhanced version, a **minimal web interface** was added to run and visualize trade parsing directly from the browser (`localhost:8080`).

---

##  Features

 Connects to Binance Futures via `libcurl`  
Parses JSON trades with `cJSON`  
Measures parsing speed using a lightweight timing utility (`timer.h`)  
Displays formatted trade data and execution stats  
Provides a local web dashboard to change symbol and trade limit dynamically  

---

## Folder Structure

```
part2_binance_api/
│
├── src/
│   ├── api.c / api.h         # HTTP GET connection using libcurl
│   ├── parser.c / parser.h   # JSON parsing and trade formatting
│   ├── timer.h               # Simple timing utility
│   ├── main.c                # Main entry point
│   └── webserver.c / webserver.h  # Local web interface (localhost:8080)
│
├── Makefile                  # Build and run automation
└── README.md                 # Project documentation
```

---

## Build and Run

### Build the program
```bash
make clean
make
```

### Run in console mode
Fetch and parse aggregated trades directly:
```bash
./binance_api
```

Example output:
```
Fetching trades from Binance...
Data received. Parsing...

[
  { "a": 2928762982, "p": "103995.10", "q": "0.012", "m": false },
  ...
]

--- Summary ---
Total trades: 10
Price range: 103995.00 → 103995.10
Average quantity: 0.049300
Maker ratio: 40.0%
Parsed 10 trades in 0.434 ms (43.400 µs per trade)
```

---

## Run in Web Interface Mode

Launch the local server:
```bash
./binance_api --web
```

Then open [http://localhost:8080](http://localhost:8080) in your browser.

### Web Interface Features

- Simple dashboard with form fields:
  - `Symbol`: e.g. `BTCUSDT`, `ETHUSDT`, etc.
  - `Limit`: number of trades (1–1000)
- Results are displayed directly in the browser
- Clean, responsive HTML/CSS layout:
  - Rounded panels
  - Highlighted headers
  - Scrollable formatted JSON

Example view:

```
Binance Trade Parser
--------------------
Symbol: [ BTCUSDT ]  Limit: [ 10 ] [ Run Parser ]

--- Results ---
[
  { "a": 2928762982, "p": "103995.10", "q": "0.012", "m": false },
  ...
]

Parsed 10 trades in 0.43 ms (43.4 µs per trade)
```

---

## Performance Metrics

| Metric | Description |
|--------:|-------------|
| **Parsing Time** | Average time per trade: `~30–40 µs` |
| **Throughput** | ~25,000 trades per second on average |
| **Complexity** | `O(n)` — linear with the number of trades |
| **Timing Source** | High-resolution millisecond counter in `timer.h` |

---

## Implementation Details

###  Connectivity Layer (`api.c`)
- Uses `libcurl` for the HTTP GET request.
- Custom write callback stores API response in a memory buffer.

###  JSON Parsing (`parser.c`)
- Uses `cJSON` for efficient DOM parsing.
- Converts JSON objects into formatted text output.
- Supports 64-bit integer fields (`long long`) to avoid overflow.

###  Timing Utility (`timer.h`)
- Simple wrapper using `clock_gettime()` or `gettimeofday()`.
- Used to compute parsing duration per trade.

###  Web Interface (`webserver.c`)
- Minimal HTTP server (port 8080) built with POSIX sockets.
- Serves a small HTML page with inline CSS.
- Redirects standard output (`stdout`) temporarily to capture parser output.
- Displays results dynamically inside `<pre>` blocks with styled containers.

---

## Design Decisions

| Aspect | Rationale |
|--------|------------|
| **libcurl + cJSON** | Reliable, portable, and fast libraries for C |
| **Fixed buffer allocation** | Prevents heap fragmentation during repeated calls |
| **Web UI via sockets** | Lightweight, dependency-free way to visualize output |
| **64-bit IDs** | Prevents overflow for large Binance trade IDs and timestamps |
| **Inline styling** | Self-contained web server, no external CSS/JS needed |

---

## Example API Request

```
GET https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT&limit=10
```

Response sample:
```json
[
  {
    "a": 2928585634,
    "p": "103995.10",
    "q": "0.001",
    "f": 6818390300,
    "l": 6818390300,
    "T": 1762257482194,
    "m": false
  }
]
```

---

## Dependencies

Install required libraries (macOS / Linux):
```bash
brew install curl cjson
# or
sudo apt install libcurl4-openssl-dev libcjson-dev
```

---

## Future Improvements

- Real-time WebSocket trade streaming (`wss://fstream.binance.com/ws`)
- Export results as `.csv` or `.json`
- Add live charts using simple HTML canvas
- Implement WebAssembly-compatible build

---

## Author

**Nuno Poza**  
HESGE - Advanced C Systems Programming  
Part 2 — Binance Futures API Parser (2025)
