#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "api.h"
#include "parser.h"
#include "timer.h"

#define PORT 8080

/**
 * @brief Starts the local HTTP server on http://localhost:8080
 */
void start_web_server(void) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[2048] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    listen(server_fd, 3);
    printf("Server running at http://localhost:%d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) continue;

        read(new_socket, buffer, sizeof(buffer));

        // Extract parameters from GET request
        char symbol[32] = "BTCUSDT";
        int limit = 10;
        char *get = strstr(buffer, "GET /?");
        int has_params = 0;

        if (get) {
            has_params = sscanf(get, "GET /?symbol=%31[^&]&limit=%d", symbol, &limit);
        }

        // Prepare HTML response content
        char html[65536]; // 64 KB buffer for output
        char result[60000] = {0}; // parsed data buffer

        if (has_params == 2) {
            printf("Received request: %s (limit=%d)\n", symbol, limit);

            char trade_buffer[2000000];
            if (get_agg_trades(symbol, limit, trade_buffer, sizeof(trade_buffer)) != 0) {
                snprintf(result, sizeof(result),
                         "<pre style='color:red;'>Error fetching trades for %s.</pre>", symbol);
            } else {
                // Redirect stdout temporarily to capture parser output
                FILE *tmp = tmpfile();
                if (!tmp) {
                    snprintf(result, sizeof(result), "<p>Internal error creating temp file.</p>");
                } else {
                    // Redirect stdout to tmp
                    int saved_stdout = dup(STDOUT_FILENO);
                    dup2(fileno(tmp), STDOUT_FILENO);

                    //// Measure parsing time
                    double start = get_time_ms();
                    int count = parse_trades(trade_buffer);
                    double end = get_time_ms();

                    fflush(stdout);
                    fseek(tmp, 0, SEEK_SET);
                    fread(result, 1, sizeof(result) - 1, tmp);

                    //// Format result text
                    char stats[256];
                    snprintf(stats, sizeof(stats),
                            "\nParsed %d trades in %.3f ms (%.3f µs per trade)\n",
                            count, end - start, (end - start) * 1000.0 / (count > 0 ? count : 1));

                    //// Append stats to the captured output
                    strncat(result, stats, sizeof(result) - strlen(result) - 1);

                    // Restore stdout
                    dup2(saved_stdout, STDOUT_FILENO);
                    close(saved_stdout);
                    fclose(tmp);
                }
            }
        }

        char formatted_result[65536];
if (has_params == 2) {
    if (strlen(result) > 0)
        snprintf(formatted_result, sizeof(formatted_result),
                 "<div class='result'><pre>%s</pre></div>", result);
    else
        snprintf(formatted_result, sizeof(formatted_result),
                 "<p>No output received.</p>");
} else {
    snprintf(formatted_result, sizeof(formatted_result),
             "<p>Enter a symbol and limit, then click <b>Run Parser</b>.</p>");
}
        snprintf(html, sizeof(html),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><head><title>Binance Trade Parser</title>"
            "<meta charset='UTF-8'>"
            "<style>"
            "body{font-family:Arial,Helvetica,sans-serif;background:#f8fafc;color:#222;"
            "max-width:800px;margin:auto;padding:40px;}"
            "h2{color:#0d9488;border-bottom:2px solid #0d9488;padding-bottom:6px;}"
            "form{margin-bottom:20px;}"
            "input[type=text],input[type=number]{padding:6px;margin:4px;border:1px solid #ccc;"
            "border-radius:6px;width:150px;}"
            "input[type=submit]{background:#0d9488;color:white;border:none;padding:8px 16px;"
            "border-radius:6px;cursor:pointer;}"
            "input[type=submit]:hover{background:#0f766e;}"
            ".result{background:#fff;border-radius:8px;padding:20px;box-shadow:0 2px 8px rgba(0,0,0,0.1);}"
            "pre{white-space:pre-wrap;word-wrap:break-word;}"
            "</style></head><body>"
            "<h2>Binance Trade Parser</h2>"
            "<form>"
            "Symbol: <input name='symbol' type='text' value='%s'>"
            "&nbsp;&nbsp;Limit: <input name='limit' type='number' value='%d'>"
            "&nbsp;<input type='submit' value='Run Parser'>"
            "</form>%s</body></html>",
            symbol, limit, formatted_result
        );

        send(new_socket, html, strlen(html), 0);
        close(new_socket);
    }
}
