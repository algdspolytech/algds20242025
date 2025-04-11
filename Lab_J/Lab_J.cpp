#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

HashTable* create_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = TABLE_SIZE;
    table->count = 0;
    table->items = (HashItem*)calloc(table->size, sizeof(HashItem));

    for (int i = 0; i < table->size; i++) {
        table->items[i].str = NULL;
        table->items[i].is_deleted = 0;
    }
    return table;
}

void free_table(HashTable* table) {
    if (table == NULL) return;

    for (int i = 0; i < table->size; i++) {
        if (table->items[i].str != NULL) {
            free(table->items[i].str);
        }
    }
    free(table->items);
    free(table);
}

unsigned int hash1(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31 + *str) % TABLE_SIZE;
        str++;
    }
    return hash;
}

unsigned int hash2(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 17 + *str) % (TABLE_SIZE - 1) + 1;
        str++;
    }
    return hash;
}

int insert(HashTable* table, const char* str) {
    if (table->count >= table->size * 0.7) return -1;

    unsigned int index = hash1(str);
    unsigned int step = hash2(str);
    unsigned int original_index = index;
    int i = 0;
    int first_deleted = -1;

    while (table->items[index].str != NULL) {
        if (table->items[index].is_deleted && first_deleted == -1) {
            first_deleted = index;
        }
        else if (strcmp(table->items[index].str, str) == 0 && !table->items[index].is_deleted) {
            return 0;
        }

        unsigned int curr_hash = hash1(table->items[index].str);
        unsigned int curr_step = hash2(table->items[index].str);
        unsigned int new_pos = (curr_hash + curr_step) % TABLE_SIZE;

        if (table->items[new_pos].str == NULL || table->items[new_pos].is_deleted) {
            char* temp = table->items[index].str;
            table->items[new_pos].str = temp;
            table->items[new_pos].is_deleted = 0;
            if (first_deleted != -1) {
                index = first_deleted;
            }
            break;
        }

        i++;
        index = (original_index + i * step) % TABLE_SIZE;
        if (i >= TABLE_SIZE) return -1; 
    }

    if (table->items[index].str == NULL) {
        if (first_deleted != -1) {
            index = first_deleted;
        }

        table->items[index].str = (char*)malloc(strlen(str) + 1);
        strcpy(table->items[index].str, str);
        table->items[index].is_deleted = 0;
        table->count++;
        return 1;
    }
    return 0;
}

int search(HashTable* table, const char* str) {
    unsigned int index = hash1(str);
    unsigned int step = hash2(str);
    int i = 0;

    while (table->items[index].str != NULL || table->items[index].is_deleted) {
        if (table->items[index].str != NULL &&
            !table->items[index].is_deleted &&
            strcmp(table->items[index].str, str) == 0) {
            return index;
        }
        i++;
        index = (hash1(str) + i * step) % TABLE_SIZE;
        if (i >= TABLE_SIZE) break;
    }
    return -1;
}

int delete(HashTable* table, const char* str) {
    int index = search(table, str);
    if (index != -1) {
        table->items[index].is_deleted = 1;
        table->count--;
        return 1;
    }
    return 0;
}
