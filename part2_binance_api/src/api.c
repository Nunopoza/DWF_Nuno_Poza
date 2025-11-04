#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> //// https://curl.se/libcurl/

/**
* @struct MemoryBlock
* @brief Structure used to store temporarily the downloaded data
*/
typedef struct {
    char *data; //// Pointer to buffer
    size_t size;
    size_t capacity;
} MemoryBlock;

/**
* @brief Handles the new data that enters from libcurl
*/
static size_t write_callback (void *contents, size_t size, size_t nmemb, void *userp ){

    size_t total = size * nmemb; //// multiply size by number of bytes arrived 
    MemoryBlock *mem = (MemoryBlock *)userp;

    if (mem->size + total + 1 > mem->capacity){ //// Check if we have space left
        fprintf(stderr, "Error: response exceeds buffer capacity.\n");
        return 0;
    }

    //// If everything is okay, copy data in buffer
    memcpy(&(mem->data[mem->size]), contents, total);
    mem->size += total;
    mem->data[mem->size] = '\0';

    return total; //// Return total of bytes
}

/**
* @brief Performs GET request to Binance API and store answer in JSON format.
*/
int get_agg_trades(const char *symbol, int limit, char *buffer, size_t bufsize){
    if (!symbol || !buffer || bufsize == 0) return -1; //// Any error, end.

    CURL *curl = curl_easy_init(); //// Init CURL, symbolize one HTTP transaction
    if (!curl) { 
        fprintf(stderr, "Error: failed to initialize CURL.\n");
        return -1;
    }

    char url[256]; //// Build and print URL request
    snprintf(url, sizeof(url), "https://fapi.binance.com/fapi/v1/aggTrades?symbol=%s&limit=%d", symbol, limit);

    MemoryBlock chunk ={ //// Prepare the memory block structure
        .data = buffer,
        .size = 0,
        .capacity = bufsize
    };

    curl_easy_setopt(curl, CURLOPT_URL, url); //// Tell libcurl which URL to connect to

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); //// Register callback to handle

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk); //// Pass our MemoryBlock for the callback

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0"); //// Set an HTTP user-agent header

    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); //// Set timeout of 10 sec

    CURLcode res = curl_easy_perform(curl); //// Perform HTTP request synchronously, blocks until finished

    if (res != CURLE_OK){ //// Check if request is finished well
        fprintf(stderr, "CURL error: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_cleanup(curl);
    return 0;
}