#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 128 
#define MAX_STRING_LENGTH 256

typedef struct HashItem {
    char* key;      
    int is_deleted;  
    int is_occupied;
} HashItem;

typedef struct HashTable {
    HashItem* items;  
    int size;         
    int count;       
} HashTable;

unsigned int hash1(const char* key, int size);
unsigned int hash2(const char* key, int size);
HashTable* create_hash_table(int size);
void free_hash_table(HashTable* table);
void insert_with_brent(HashTable* table, const char* key);
int search(HashTable* table, const char* key);
void del(HashTable* table, const char* key);