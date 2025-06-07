#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define ENTRY_FREE 0
#define ENTRY_USED 1
#define ENTRY_DELETED -1

#define INSERT_SUCCESS 1
#define INSERT_FAIL 0
#define INSERT_OVERFLOW -1

#include <stddef.h>

typedef struct {
    int status;
    char* value;
} HashEntry;

typedef struct {
    HashEntry* entries;
    size_t capacity;
} HashTable;

HashTable createTable(size_t capacity);

int insert(HashTable* table, const char* str);

int search(HashTable* table, const char* str);

int deleteEntry(HashTable* table, const char* str);

void freeTable(HashTable* table);

void rehash(HashTable* table, size_t new_capacity);

#endif // HASH_TABLE_H