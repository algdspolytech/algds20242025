#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

static char* table[TABLE_SIZE];
static int used[TABLE_SIZE];

static unsigned long hash1(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

static unsigned long hash2(const char* str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;
    return 97 - (hash % 97);
}

int ht_init() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = NULL;
        used[i] = 0;
    }
    return 0;
}

HT_Result ht_insert(const char* key) {
    unsigned long h1 = hash1(key);
    unsigned long h2 = hash2(key);

    for (int i = 0; i < TABLE_SIZE; ++i) {
        int idx = (h1 + i * h2) % TABLE_SIZE;
        if (used[idx]) {
            if (table[idx] && strcmp(table[idx], key) == 0)
                return HT_ALREADY_EXISTS;
        } else {
            table[idx] = strdup(key);
            used[idx] = 1;
            return HT_OK;
        }
    }
    return HT_FULL;
}

HT_Result ht_search(const char* key) {
    unsigned long h1 = hash1(key);
    unsigned long h2 = hash2(key);

    for (int i = 0; i < TABLE_SIZE; ++i) {
        int idx = (h1 + i * h2) % TABLE_SIZE;
        if (!used[idx]) return HT_NOT_FOUND;
        if (table[idx] && strcmp(table[idx], key) == 0)
            return HT_OK;
    }
    return HT_NOT_FOUND;
}

HT_Result ht_delete(const char* key) {
    unsigned long h1 = hash1(key);
    unsigned long h2 = hash2(key);

    for (int i = 0; i < TABLE_SIZE; ++i) {
        int idx = (h1 + i * h2) % TABLE_SIZE;
        if (!used[idx]) return HT_NOT_FOUND;
        if (table[idx] && strcmp(table[idx], key) == 0) {
            free(table[idx]);
            table[idx] = NULL;
            used[idx] = 1;  // tombstone
            return HT_OK;
        }
    }
    return HT_NOT_FOUND;
}

void ht_free() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i]) {
            free(table[i]);
            table[i] = NULL;
        }
        used[i] = 0;
    }
}
