#ifndef API_H
#define API_H

#include <stddef.h>

/**
* @brief Fetches aggregated trades from Binance Futures API.
*
* @param symbol Trading pair symbol.
* @param limit Number of trades to fetch.
* @param buffer Pointer to a memory buffer to store the JSON response.
* @param bufsize Size of the provided buffer in bytes.
* @return int 0 on success, -1 on failure.
*/
int get_agg_trades(const char *symbol, int limit, char *buffer, size_t bufsize);

#endif
