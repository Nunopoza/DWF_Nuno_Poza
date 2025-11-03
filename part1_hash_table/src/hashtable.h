#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

/**
* @file hashtable.h
* @brief Fixed-size hash table with linear probing and O(1) complexity in operations.
*/

/**
* @struct HashEntry
* @brief Represents the key-value pair inside the hash table.
*/
typedef struct {
    char *key;
    int value;
    unsigned long long timestamp;//// Record time of instertion/modification
    int state;                   //// 0 = empty slot, 1 = used slot, 2 = deleted (used before)  
} HashEntry;

/**
* @struct HashTable 
* @brief Hash table container/bucket.
*/
typedef struct {
    HashEntry *entries;
    int size;
    unsigned long long tick;
    HashEntry* first_entry; //// Pointer to first entry
    HashEntry* last_entry; //// Pointer to last entry
} HashTable;

/**
* @brief Creates a new hash table with a fixed size.
*
* @param size Number of slots to create.
* @return Pointer to the newly created HashTable 
*/
HashTable *create_table(int size);

/**
* @brief Frees all the memory associated with the hash table.
*
* @param table Pointer to the hash table.
*/
void free_table(HashTable *table);

/**
* @brief Inserts / Update a key-value pair in a HashTable
*
* @param table Pointer to the hash table.
* @param key Pointer String key.
* @param value Integer value. 
*/
void insert(HashTable *table, const char *key, int value);

/**
* @brief Removes a key-value pair form the hash table
* 
* @param table Pointer to the hash table.
* @param key Pointer String key.
*/
void remove_key(HashTable *table, const char *key);

/**
* @brief Retreives the int-value associated to a given key
*
* @param table Pointer to the hash table.
* @param key Pointer String key.
* @param found Output flag; set to true if found, false otherwise. Use to differentiate between nothing and value 0.
* @return Integer value if found, 0 otherwise.
*/
int get(HashTable *table, const char *key, bool *found);

/**
* @brief Returns the most recently insterted/modified key-value pair.
* 
* @param table Pointer to the hash table.
* @return Pointer to the last HashEntry (NULL if empty) 
*/
HashEntry *get_last(HashTable *table);

/**
* @brief Returns the first inserted/modified key-value pair.
*
* @param table Pointer to the hash table.
* @return Pointer to the oldest HashEntry (NULL if empty)
*/
HashEntry *get_first(HashTable *table);
#endif

