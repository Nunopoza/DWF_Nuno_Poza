#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

/**
* @brief Parse the Binance aggregated trades into JSON response.
* 
* @param json_text Pointer to the JSON string buffer.
* @return int The number of trades parsed successfully.
*/
int parse_trades(const char *json_text);

#endif