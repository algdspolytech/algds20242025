#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 200003 
#define MAX_LOAD_FACTOR 0.75
#define GROWTH_FACTOR 2

typedef enum {
    EMPTY,
    OCCUPIED,
    DELETED
} CellStatus;

typedef struct {
    char* key;
    CellStatus status;
} Cell;

typedef struct {
    Cell* cells;
    int size;
    int count;
    int deleted_count;  
} HashTable;

unsigned int hash_function(const char* str, int table_size) {
    unsigned int hash = 2166136261u;
    while (*str) {
        hash ^= (unsigned char)(*str++);
        hash *= 16777619u;
    }
    return hash % table_size;
}

HashTable* create_hash_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->size = TABLE_SIZE;
    table->count = 0;
    table->deleted_count = 0;
    table->cells = (Cell*)calloc(table->size, sizeof(Cell));

    if (!table->cells) {
        free(table);
        return NULL;
    }
    for (int i = 0; i < table->size; i++) {
        table->cells[i].status = EMPTY;
        table->cells[i].key = NULL;
    }
    return table;
}

static void resize_table(HashTable* table, int new_size) {
    Cell* old_cells = table->cells;
    int old_size = table->size;

    table->cells = (Cell*)calloc(new_size, sizeof(Cell));
    if (!table->cells) {
        table->cells = old_cells;
        return;
    }

    table->size = new_size;
    table->count = 0;
    table->deleted_count = 0;

    for (int i = 0; i < old_size; i++) {
        if (old_cells[i].status == OCCUPIED) {
            unsigned int index = hash_function(old_cells[i].key, table->size);

            while (table->cells[index].status==OCCUPIED) {
                index = (index + 1) % table->size;
            }

            table->cells[index] = old_cells[i];
            table->count++;
        }
    }

    free(old_cells);
}

void free_hash_table(HashTable* table) {
    if (!table) return;

    for (int i = 0; i < table->size; i++) {
        if (table->cells[i].key) {
            free(table->cells[i].key);
        }
    }
    free(table->cells);
    free(table);
}

void insert(HashTable* table, const char* key) {
    if (!table || !key) return;

    if ((table->count + table->deleted_count) > table->size * MAX_LOAD_FACTOR) {
        resize_table(table, table->size * GROWTH_FACTOR);
    }

    unsigned int index = hash_function(key, table->size);
    int original_index = index;
    int probe = 1;

    while (table->cells[index].status == OCCUPIED ||
        table->cells[index].status == DELETED) {
        if (table->cells[index].status == OCCUPIED &&
            strcmp(table->cells[index].key, key) == 0) {
            return; 
        }
        index = (original_index + probe) % table->size;
        probe++;
        if (index == original_index) return; 
    }

    if (table->cells[index].key) {
        free(table->cells[index].key);
    }

    table->cells[index].key = strdup(key);
    if (!table->cells[index].key) {
        return;
    }

    if (table->cells[index].status == DELETED) {
        table->deleted_count--;
    }

    table->cells[index].status = OCCUPIED;
    table->count++;
}

bool search(HashTable* table, const char* key) {
    if (!table || !key) return false;

    unsigned int index = hash_function(key, table->size);
    int original_index = index;
    int probe = 1;

    while (table->cells[index].status != EMPTY) {
        if (table->cells[index].status == OCCUPIED &&
            strcmp(table->cells[index].key, key) == 0) {
            return true;
        }
        index = (original_index + probe) % table->size;
        probe++;
        if (index == original_index) break;
    }
    return false;
}

void delete(HashTable* table, const char* key) {
    if (!table || !key) return;

    unsigned int index = hash_function(key, table->size);
    int original_index = index;
    int probe = 1;

    while (table->cells[index].status != EMPTY) {
        if (table->cells[index].status == OCCUPIED &&
            strcmp(table->cells[index].key, key) == 0) {
            free(table->cells[index].key);
            table->cells[index].key = NULL;
            table->cells[index].status = DELETED;
            table->count--;
            table->deleted_count++;
            return;
        }
        index = (original_index + probe) % table->size;
        probe++;
        if (index == original_index) break;
    }
}

int main() {
    HashTable* table = create_hash_table();
    if (!table) return 1;

    char operation;
    char key[256];

    while (scanf(" %c %255s", &operation, key) == 2) {
        switch (operation) {
        case 'a':
            insert(table, key);
            break;
        case 'r':
            delete(table, key);
            break;
        case 'f':
            printf(search(table, key) ? "yes\n" : "no\n");
            break;
        }
    }

    free_hash_table(table);
    return 0;
}
