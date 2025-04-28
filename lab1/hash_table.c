#include "hash_table.h"

char* table[TABLE_SIZE];

unsigned int hash(const char* str) {
    unsigned int h = 0;
    while (*str) h = h * 31 + *str++;
    return h % TABLE_SIZE;
}

char* my_strdup(const char* str) {
    char* copy = malloc(strlen(str) + 1);
    if (copy) strcpy(copy, str);
    return copy;
}

int insert(const char* str) {
    unsigned int idx = hash(str);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (idx + i) % TABLE_SIZE;
        if (table[probe] == NULL) {
            table[probe] = my_strdup(str);
            return 1;
        }
        if (strcmp(table[probe], str) == 0)
            return 0;
    }
    return 0;
}

int search(const char* str) {
    unsigned int idx = hash(str);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (idx + i) % TABLE_SIZE;
        if (table[probe] == NULL)
            return 0;
        if (strcmp(table[probe], str) == 0)
            return 1;
    }
    return 0;
}

void free_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) free(table[i]);
    }
}