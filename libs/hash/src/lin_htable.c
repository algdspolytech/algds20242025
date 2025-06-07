#include "lin_htable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 101


unsigned int hash(const char* str, size_t capacity) {
    unsigned int hash_value = 3234;
    while (*str) {
        hash_value = (hash_value * 31 + (unsigned char)(*str)) % capacity;
        str++;
    }
    return hash_value;
}


HashTable createTable(size_t capacity) {
    HashTable table;
    table.entries = (HashEntry*)malloc(sizeof(HashEntry) * capacity);
    table.capacity = capacity;

    for (size_t i = 0; i < capacity; i++) {
        table.entries[i].status = ENTRY_FREE;
        table.entries[i].value = NULL;
    }

    return table;
}

int insert(HashTable* table, const char* str) {
    unsigned int index = hash(str, table->capacity);
    unsigned int original_index = index;
    int first_deleted = -1;

    for (size_t i = 0; i < table->capacity; i++) {
        HashEntry* entry = &table->entries[index];

        if (entry->status == ENTRY_USED && strcmp(entry->value, str) == 0) {
            return INSERT_FAIL;
        }

        if (entry->status == ENTRY_DELETED && first_deleted == -1) {
            first_deleted = index;
        }

        if (entry->status == ENTRY_FREE) {
            if (first_deleted != -1) {
                index = first_deleted;
                entry = &table->entries[index];
            }
            entry->status = ENTRY_USED;
            entry->value = strdup(str);
            return INSERT_SUCCESS;
        }

        index = (original_index + i) % table->capacity;
    }

    return INSERT_OVERFLOW;
}

int search(HashTable* table, const char* str) {
    unsigned int index = hash(str, table->capacity);
    unsigned int original_index = index;

    for (size_t i = 0; i < table->capacity; i++) {
        HashEntry* entry = &table->entries[index];

        if (entry->status == ENTRY_FREE) {
            return 0;
        }

        if (entry->status == ENTRY_USED && strcmp(entry->value, str) == 0) {
            return 1;
        }

        index = (original_index + i) % table->capacity;
    }

    return 0;
}

int deleteEntry(HashTable* table, const char* str) {
    unsigned int index = hash(str, table->capacity);
    unsigned int original_index = index;

    for (size_t i = 0; i < table->capacity; i++) {
        HashEntry* entry = &table->entries[index];

        if (entry->status == ENTRY_FREE) {
            return 0;
        }

        if (entry->status == ENTRY_USED && strcmp(entry->value, str) == 0) {
            free(entry->value);
            entry->value = NULL;
            entry->status = ENTRY_DELETED;
            return 1;
        }

        index = (original_index + i) % table->capacity;
    }

    return 0;
}

void freeTable(HashTable* table) {
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].status == ENTRY_USED) {
            free(table->entries[i].value);
        }
    }
    free(table->entries);
    table->entries = NULL;
    table->capacity = 0;
}

void rehash(HashTable* table, size_t new_capacity) {
    HashTable new_table = createTable(new_capacity);

    for (size_t i = 0; i < table->capacity; i++) {
        HashEntry* entry = &table->entries[i];
        if (entry->status == ENTRY_USED) {
            insert(&new_table, strdup(entry->value));
        }
    }

    freeTable(table);

    table->entries = new_table.entries;
    table->capacity = new_table.capacity;
}