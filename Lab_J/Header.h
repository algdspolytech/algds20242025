#pragma once
#define TABLE_SIZE 101
#define MAX_STRING_LENGTH 256

typedef struct {
    char* str;
    int is_deleted;
} HashItem;

typedef struct {
    HashItem* items;
    int size;
    int count;
} HashTable;

HashTable* create_table();
void free_table(HashTable* table);
int insert(HashTable* table, const char* str);
int search(HashTable* table, const char* str);
int delete(HashTable* table, const char* str);

unsigned int hash1(const char* str);
unsigned int hash2(const char* str);