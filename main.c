#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000003

typedef struct {
    char* key;
    int is_deleted;
    int is_occupied;
} HashItem;

typedef struct {
    HashItem* items;
    int size;
} HashTable;

unsigned int hash1(const char* key);
unsigned int hash2(const char* key);
void initHashTable(HashTable* table);
void insert(HashTable* table, const char* key);
void removeKey(HashTable* table, const char* key);
int search(HashTable* table, const char* key);
void freeHashTable(HashTable* table);

unsigned int hash1(const char* key) {
    unsigned int h = 2166136261u;
    while (*key) {
        h ^= *key++;
        h *= 16777619u;
    }
    return h % TABLE_SIZE;
}

unsigned int hash2(const char* key) {
    unsigned int h = 5381;
    while (*key) {
        h = ((h << 5) + h) ^ *key++;
    }
    return (h % (TABLE_SIZE - 2)) + 1;
}

void initHashTable(HashTable* table) {
    table->size = TABLE_SIZE;
    table->items = (HashItem*)calloc(TABLE_SIZE, sizeof(HashItem));
}

void insert(HashTable* table, const char* key) {
    if (search(table, key)) return;

    unsigned int idx = hash1(key);
    unsigned int step = hash2(key);
    unsigned int i = 0;

    while (i < TABLE_SIZE) {
        if (!table->items[idx].is_occupied || table->items[idx].is_deleted) {
            if (table->items[idx].key) free(table->items[idx].key);
            table->items[idx].key = strdup(key);
            table->items[idx].is_occupied = 1;
            table->items[idx].is_deleted = 0;
            return;
        }
        i++;
        idx = (idx + step) % TABLE_SIZE;
    }
    fprintf(stderr, "Hash table is full\n");
}

void removeKey(HashTable* table, const char* key) {
    unsigned int idx = hash1(key);
    unsigned int step = hash2(key);
    unsigned int i = 0;

    while (i < TABLE_SIZE && table->items[idx].is_occupied) {
        if (!table->items[idx].is_deleted &&
            strcmp(table->items[idx].key, key) == 0) {
            free(table->items[idx].key);
            table->items[idx].key = NULL;
            table->items[idx].is_deleted = 1;
            return;
        }
        i++;
        idx = (idx + step) % TABLE_SIZE;
    }
}

int search(HashTable* table, const char* key) {
    unsigned int idx = hash1(key);
    unsigned int step = hash2(key);
    unsigned int i = 0;

    while (i < TABLE_SIZE && table->items[idx].is_occupied) {
        if (!table->items[idx].is_deleted &&
            strcmp(table->items[idx].key, key) == 0) {
            return 1;
        }
        i++;
        idx = (idx + step) % TABLE_SIZE;
    }
    return 0;
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->items[i].key) free(table->items[i].key);
    }
    free(table->items);
}

int main() {
    HashTable table;
    initHashTable(&table);

    char op[2];
    char key[256];

    while (scanf("%1s %255s", op, key) == 2) {
        if (op[0] == 'a') {
            insert(&table, key);
        }
        else if (op[0] == 'r') {
            removeKey(&table, key);
        }
        else if (op[0] == 'f') {
            printf(search(&table, key) ? "yes\n" : "no\n");
        }
    }

    freeHashTable(&table);
    return 0;
}