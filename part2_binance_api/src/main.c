#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "parser.h"
#include "timer.h"
#include "webserver.h" 

/**
 * @brief Program entry point.
 * @param argc number of command-line arguments
 * @param argv argument vector
 */
int main(int argc, char *argv[]) {

    //// WEB MODE
    if (argc > 1 && strcmp(argv[1], "--web") == 0) {
        start_web_server(); //// Launch local web interface
        return 0;
    }

    //// CLI MODE
    char buffer[2000000]; //// 2MB of buffer for HTTP response
    printf("Fetching trades from Binance...\n");

    //// Default parameters
    const char *symbol = argc > 1 ? argv[1] : "BTCUSDT";
    int limit = argc > 2 ? atoi(argv[2]) : 10;

    if (get_agg_trades(symbol, limit, buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error fetching trades.\n");
        return 1;
    }

    printf("Data received. Parsing...\n");

    double start = get_time_ms(); //// Measure parsing time
    int count = parse_trades(buffer);
    double end = get_time_ms();

    printf("\nParsed %d trades in %.3f ms (%.3f µs per trade)\n",
           count, end - start, (end - start) * 1000.0 / count);

    return 0;
}
