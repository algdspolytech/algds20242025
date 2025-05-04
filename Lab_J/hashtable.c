#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash1(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str++;
    }
    return hash;
}

unsigned int hash2(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 37) + *str++;
    }
    return (hash % (TABLE_SIZE - 1)) + 1;
}

HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    table->size = TABLE_SIZE;
    table->count = 0;
    table->items = calloc(table->size, sizeof(HashItem));
    return table;
}

void free_table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        if (table->items[i].key) {
            free(table->items[i].key);
        }
    }
    free(table->items);
    free(table);
}

bool insert(HashTable* table, const char* key) {
    if (table->count >= table->size) return false;

    unsigned int index = hash1(key) % table->size;
    unsigned int step = hash2(key);
    int initial_index = index;
    int i = 1;

    while (table->items[index].key && !table->items[index].is_deleted) {
        if (strcmp(table->items[index].key, key) == 0) return false;
        index = (initial_index + i * step) % table->size;
        i++;
        if (index == initial_index) return false;
    }

    if (table->items[index].key) free(table->items[index].key);
    table->items[index].key = strdup(key);
    table->items[index].is_deleted = false;
    table->count++;
    return true;
}

bool search(HashTable* table, const char* key) {
    unsigned int index = hash1(key) % table->size;
    unsigned int step = hash2(key);
    int initial_index = index;
    int i = 1;

    while (table->items[index].key) {
        if (!table->items[index].is_deleted && strcmp(table->items[index].key, key) == 0) {
            return true;
        }
        index = (initial_index + i * step) % table->size;
        i++;
        if (index == initial_index) break;
    }
    return false;
}

bool delete(HashTable* table, const char* key) {
    unsigned int index = hash1(key) % table->size;
    unsigned int step = hash2(key);
    int initial_index = index;
    int i = 1;

    while (table->items[index].key) {
        if (!table->items[index].is_deleted && strcmp(table->items[index].key, key) == 0) {
            free(table->items[index].key);
            table->items[index].key = NULL;
            table->items[index].is_deleted = true;
            table->count--;
            return true;
        }
        index = (initial_index + i * step) % table->size;
        i++;
        if (index == initial_index) break;
    }
    return false;
}

void print_table(HashTable* table) {
    printf("Hash Table (%d/%d):\n", table->count, table->size);
    for (int i = 0; i < table->size; i++) {
        if (table->items[i].key && !table->items[i].is_deleted) {
            printf("[%d]: %s\n", i, table->items[i].key);
        }
    }
}