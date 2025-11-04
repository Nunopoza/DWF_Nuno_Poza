#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "hashtable.h"

#define PORT 8080

/**
 * @brief Starts a simple HTTP server for interacting with the hash table.
 */
void start_web_server(HashTable *table) {
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

        char key[128] = "";
        int value = 0;
        char action[32] = "";

        // Parse GET parameters: action, key, value
        if (strstr(buffer, "GET /?")) {
            sscanf(buffer, "GET /?action=%31[^&]&key=%127[^&]&value=%d", action, key, &value);
        }

        char html[8192];
        char result[4096] = "";

        // Process actions
        if (strcmp(action, "insert") == 0 && strlen(key) > 0) {
            insert(table, key, value);
            snprintf(result, sizeof(result), "<p>Inserted key '%s' with value %d.</p>", key, value);
        } else if (strcmp(action, "get") == 0 && strlen(key) > 0) {
            bool found = false;
            int val = get(table, key, &found);
            if (found)
                snprintf(result, sizeof(result), "<p>Key '%s' → Value %d</p>", key, val);
            else
                snprintf(result, sizeof(result), "<p>Key '%s' not found.</p>", key);
        } else if (strcmp(action, "remove") == 0 && strlen(key) > 0) {
            remove_key(table, key);
            snprintf(result, sizeof(result), "<p>Removed key '%s'.</p>", key);
        } else if (strcmp(action, "first") == 0) {
            HashEntry *first = get_first(table);
            if (first)
                snprintf(result, sizeof(result), "<p>First key: '%s' → %d</p>", first->key, first->value);
            else
                snprintf(result, sizeof(result), "<p>Table is empty.</p>");
        } else if (strcmp(action, "last") == 0) {
            HashEntry *last = get_last(table);
            if (last)
                snprintf(result, sizeof(result), "<p>Last key: '%s' → %d</p>", last->key, last->value);
            else
                snprintf(result, sizeof(result), "<p>Table is empty.</p>");
        }

        // HTML interface
        snprintf(html, sizeof(html),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><head><meta charset='UTF-8'><title>Hash Table Interface</title>"
            "<style>"
            "body{font-family:Arial;background:#f8fafc;color:#222;max-width:800px;margin:auto;padding:40px;}"
            "h2{color:#0d9488;border-bottom:2px solid #0d9488;padding-bottom:6px;}"
            "form{margin-bottom:20px;}"
            "input,select{padding:6px;margin:4px;border:1px solid #ccc;border-radius:6px;}"
            "input[type=submit]{background:#0d9488;color:white;border:none;padding:8px 16px;border-radius:6px;cursor:pointer;}"
            "input[type=submit]:hover{background:#0f766e;}"
            ".result{background:#fff;border-radius:8px;padding:20px;box-shadow:0 2px 8px rgba(0,0,0,0.1);}"
            "</style></head><body>"
            "<h2>Hash Table Interactive Console</h2>"
            "<form>"
            "Action: <select name='action'>"
            "<option value='insert'>Insert</option>"
            "<option value='get'>Get</option>"
            "<option value='remove'>Remove</option>"
            "<option value='first'>Get First</option>"
            "<option value='last'>Get Last</option>"
            "</select>"
            "&nbsp;Key: <input name='key' type='text'>"
            "&nbsp;Value: <input name='value' type='number'>"
            "&nbsp;<input type='submit' value='Run'>"
            "</form>"
            "<div class='result'>%s</div>"
            "</body></html>",
            result
        );

        send(new_socket, html, strlen(html), 0);
        close(new_socket);
    }
}
