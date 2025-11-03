#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
* Internal functions
*/

/**
* @brief djb2 hash function for strings. (http://www.cse.yorku.ca/~oz/hash.html)
*/
static unsigned long hash(const char *str){
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

/**
* @brief Duplicates a string safely, safe the key while the table exists
*/
static char *strdup_safe(const char *src){
    size_t len = strlen(src);
    char *copy = malloc(len + 1);
    if (copy) strcpy(copy, src);
    return copy;
}

/*
* Public functions implementation
*/

HashTable *create_table(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    if(!table) return NULL;

    table->entries = calloc(size, sizeof(HashEntry));
    if(!table->entries){
        free(table); //// Belongs to <stdlib.h>
        return NULL;
    }

    table->size = size;
    table->tick = 0;
    table->first_entry = NULL;
    table->last_entry  = NULL;
    return table;
}

void free_table(HashTable *table){
    if(!table) return;
    for (int i = 0; i < table->size; i++){ ////Impossible to secure free the table with lower complexity of O(N)
        if(table->entries[i].state == 1 && table->entries[i].key) {
            free(table->entries[i].key);
        }
    }
    free(table->entries);
    free(table);
}

void insert(HashTable *table, const char *key, int value){
    if (!table || !key) return;

    unsigned long index = hash(key) % table->size;
    unsigned long start_index = index;

    while(true){
        HashEntry *entry = &table->entries[index];

        if (entry->state == 0 || entry->state == 2){ //// Empty or deleted slot
            entry->key = strdup_safe(key);
            entry->value = value;
            entry->state = 1;
            entry->timestamp = ++table->tick;
            if (table->first_entry == NULL){
                table->first_entry = entry;
            }
            table->last_entry = entry;
            return;
        }

        if(strcmp(entry->key, key) == 0){ //// If key does exist in the table, update
            entry->value = value;
            entry->timestamp = ++table->tick;

            table->last_entry = entry;
            return;
        }

        index = (index + 1) % table->size; //// Check next index
        if (index == start_index){ //// If next index is the init index -> FULL TABLE
            fprintf(stderr, "Error: Hash table is full.\n");
            return;
        }
    }
}

void remove_key(HashTable *table, const char *key){
    if(!table || !key) return; 

    unsigned long index = hash(key) % table->size;
    unsigned long start_index = index;

    while(true){
        HashEntry *entry = &table->entries[index];

        if (entry->state == 0) return;
        if (entry->state == 1 && strcmp(entry->key, key) == 0){
            free(entry->key);
            entry->key = NULL;
            entry->state = 2; //// Marked as deleted
            return;
        }

        index = (index + 1) % table->size;
        if (index == start_index) return; //// Not found
    }
}

int get(HashTable *table, const char *key, bool *found){
    if(!table || !key){ //// Not existing table/key, found = false, return 0
        if(found) *found = false;
        return 0;
    }

    unsigned long index = hash(key) % table->size;
    unsigned long start_index = index;

    while(true){ //// Similar to insert()
        HashEntry *entry = &table->entries[index];

        if(entry->state == 0) break; //// Empty slot-> NOT FOUND
        if(entry->state == 1 && strcmp(entry->key, key) == 0){
            if(found) *found=true; //// If valid pointer then *found=true
            return entry->value;
        }

        index = (index + 1) % table->size;
        if (index == start_index) break; /// Same as instert()
    }

    if (found) *found = false;
    return 0;
}

HashEntry *get_last(HashTable *table){
    return table->last_entry;
}
HashEntry *get_first(HashTable *table){
    return table->first_entry;
}