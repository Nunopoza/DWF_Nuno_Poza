#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

#define BUFFER_SIZE 8192

/*
* Normalize al characters
*/
static void normalize(char *s){
    for(; *s; ++s){
        *s = (char)tolower((unsigned char)*s);
    }
}

/*
* Extract words and load them in a hash table with incremental value
*/
static void load_words(FILE *file, HashTable *table){
    char buffer[BUFFER_SIZE];
    unsigned long counter = 0;

    while (fgets(buffer, BUFFER_SIZE, file)){ //// Reads the file, line by line

        char *p = buffer; 

        while(*p){ //// While we have characters to be read

           while(*p && !isalnum((unsigned char)*p)) p++; //// Ignore non numbers/caracters
           if(!*p) break;
           
           char *start = p; //// Store firts letter/number of the word

           while (*p && isalnum((unsigned char)*p)) p++; //// Advance through word

           size_t len = (size_t)(p-start);
           char *word = malloc(len+1);
           if(!word){
            fprintf(stderr, "Error allocating memory.\n");
            exit(EXIT_FAILURE);
           }

           strncpy(word, start, len);
           word[len] = '\0';

           normalize(word);

           insert(table, word, (int)counter++); //// Insert word in the hash table

           free(word); //// Free temporal save
        }

    }
}

int main(int argc, char *argv[]){

    if(argc < 3){ //// Check if there are enough arguments
        fprintf(stderr, "Usage: %s <table_size> <book_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int table_size = atoi(argv[1]); 
    if(table_size <= 0){ //// Check size of the table
        fprintf(stderr, "Invalid table size.\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[2], "r"); //// Open the text file
    if(!file){
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    HashTable *table = create_table(table_size);
    if(!table){
        fprintf(stderr, "Failed to create hash table.\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("Loading words from %s...\n", argv[2]);
    load_words(file, table);
    fclose(file);

    //// TESTS!!!!!!
    printf("Dataset file: %s\n", argv[2]);
    printf("Table size:   %d\n\n", table_size);
    printf("Dataset loaded successfully.\n");
    printf("------------------------------------\n\n");

    printf("Testing hash table operations:\n\n");

    //// Test 1: get(key)
    bool found = false;
    int val = get(table, "casting", &found);
    if (found)
        printf("  GET(\"casting\")       -> %d\n", val);
    else
        printf("  GET(\"casting\")       -> not found\n");

    //// Test 2: get_first() and get_last()
    HashEntry *first = get_first(table);
    HashEntry *last  = get_last(table);

    if (first)
        printf("  GET_FIRST()           -> \"%s\" -> %d\n", first->key, first->value);
    else
        printf("  GET_FIRST()           -> none\n");

    if (last)
        printf("  GET_LAST()            -> \"%s\" -> %d\n", last->key, last->value);
    else
        printf("  GET_LAST()            -> none\n");

    //// Test 3: remove(key)
    remove_key(table, "perplexed");
    found = false;
    val = get(table, "perplexed", &found);
    printf("  REMOVE(\"perplexed\")  -> %s\n", found ? "failed" : "removed");
    printf("  GET(\"perplexed\")     -> %s\n", found ? "still exists" : "not found");

    printf("\n------------------------------------\n");
    printf("Execution completed successfully.\n");

    free_table(table);
    return EXIT_SUCCESS;
}