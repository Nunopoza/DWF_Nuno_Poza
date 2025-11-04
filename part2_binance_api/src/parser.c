#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

/**
* @brief Parses and prints each trade form the Binance JSON array.
*/
int parse_trades(const char *json_text){
    double min_price = 1e12;
    double max_price = 0.0;
    double total_qty = 0.0;
    int maker_count = 0;
    int total_count = 0;

    if(!json_text){
        fprintf(stderr, "Error: Null JSON input.\n");
        return 0;
    }

    cJSON *root = cJSON_Parse(json_text); //// Parse JSON string into a cJSON object
    if(!root){
        fprintf(stderr, "Error: Failed to parse JSON.\n");
        return 0;
    }

    if (!cJSON_IsArray(root)){
        fprintf(stderr, "Error: Expexted JSON array.\n");
        cJSON_Delete(root);
        return 0;
    }

    int trade_count = 0;
    cJSON *trade = NULL;

    printf("[\n");
    cJSON_ArrayForEach(trade, root){ //// Loops through every element in the array 'root'
        if (!cJSON_IsObject(trade)) continue; //// If not object, skip it to prevent errors

        long long a = cJSON_GetObjectItem(trade, "a")->valuedouble;
        const char *p = cJSON_GetObjectItem(trade, "p")->valuestring;
        const char *q = cJSON_GetObjectItem(trade, "q")->valuestring;
        long long f = cJSON_GetObjectItem(trade, "f")->valuedouble;
        long long l = cJSON_GetObjectItem(trade, "l")->valuedouble;
        long long T = cJSON_GetObjectItem(trade, "T")->valuedouble;
        int m = cJSON_GetObjectItem(trade, "m")->valueint;

        double price = atof(p); //// Convert String into numeric stats
        double quant = atof(q);

        if (price < min_price) min_price = price; //// Update price if ...
        if (price > max_price) max_price = price;

        total_qty += quant;
        if(m) maker_count++;
        total_count++;

        //// Print parsed data in JSON format
        printf("  {\n");
        printf("    \"a\": %lld,\n", a);
        printf("    \"p\": \"%s\",\n", p);
        printf("    \"q\": \"%s\",\n", q);
        printf("    \"f\": %lld,\n", f);
        printf("    \"l\": %lld,\n", l);
        printf("    \"T\": %lld,\n", T);
        printf("    \"m\": %s\n", m ? "true" : "false");
        printf("  },\n");

        trade_count++; //// Increment de number of parsed trades
    }
    printf("]\n");
    printf("\n--- Summary ---\n");
    printf("Total trades: %d\n", total_count);
    printf("Price range: %.2f → %.2f\n", min_price, max_price);
    printf("Average quantity: %.6f\n", total_qty / total_count);
    printf("Maker ratio: %.1f%%\n", 100.0 * maker_count / total_count);

    cJSON_Delete(root);
    return trade_count;
}