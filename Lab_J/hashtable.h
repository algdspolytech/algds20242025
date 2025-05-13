#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

#define TABLE_SIZE 53
#define MAX_STRING_LENGTH 256

typedef struct {
    char* key;
    bool is_deleted;
} HashItem;

typedef struct {
    HashItem* items;
    int size;
    int count;
} HashTable;

HashTable* create_table();
void free_table(HashTable* table);

bool insert(HashTable* table, const char* key);
bool search(HashTable* table, const char* key);
bool delete(HashTable* table, const char* key);

void print_table(HashTable* table);

#endif