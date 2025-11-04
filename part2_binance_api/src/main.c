#include <stdio.h>
#include "api.h"
#include "parser.h"
#include "timer.h"

int main(void){
    char buffer[2000000]; //// 2MB of Buffer
    printf("Fetching trades from Binance...\n");

    if(get_agg_trades("BTCUSDT", 3, buffer, sizeof(buffer)) !=0){
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