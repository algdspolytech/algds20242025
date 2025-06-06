#define _CRT_SECURE_NO_WARNINGS
#include "labJ.h"


unsigned int hash(const char* str) {
    unsigned int h = 0;
    while (*str) h = h * 31 + *str++;
    return h % TABLE_SIZE;
}

char* copystr(const char* str) {
    char* copy = (char*)malloc(strlen(str) + 1);
    return copy ? strcpy(copy, str) : NULL;
}

int insert(const char* str) {
    unsigned int idx = hash(str);
    int first_deleted = -1;
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (idx + i) % TABLE_SIZE;
        if (state[probe] == OCCUPIED) {
            if (strcmp(table[probe], str) == 0) return 0;
        }
        else {
            if (state[probe] == DELETED && first_deleted == -1) {
                first_deleted = probe;
            }
            else if (state[probe] == EMPTY) {
                int target = (first_deleted != -1) ? first_deleted : probe;
                free(table[target]); 
                table[target] = copystr(str);
                state[target] = OCCUPIED;
                return 1;
            }
        }
    }
    if (first_deleted != -1) {
        free(table[first_deleted]);
        table[first_deleted] = copystr(str);
        state[first_deleted] = OCCUPIED;
        return 1;
    }
    return 0;
}

int search(const char* str) {
    unsigned int idx = hash(str);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (idx + i) % TABLE_SIZE;
        if (state[probe] == EMPTY) return 0;
        if (state[probe] == OCCUPIED &&
            strcmp(table[probe], str) == 0) {
            return 1;
        }
    }
    return 0;
}

int del(const char* str) {
    unsigned int idx = hash(str);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (idx + i) % TABLE_SIZE;
        if (state[probe] == EMPTY) return 0;
        if (state[probe] == OCCUPIED &&
            strcmp(table[probe], str) == 0) {
            free(table[probe]);
            table[probe] = NULL;
            state[probe] = DELETED;
            return 1;
        }
    }
    return 0;
}

void freetable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        free(table[i]);
        table[i] = NULL;
        state[i] = EMPTY;
    }
}

