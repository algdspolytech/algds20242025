#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10000000
#define MAX_STR_LEN 20

typedef struct {
    char* key;
} Cell;

Cell* table = NULL;



unsigned int hash1(char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
}

unsigned int hash2(char* str) {
    unsigned int hash = 0;
    int c;
    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return (hash % (TABLE_SIZE - 1)) | 1;
}

void initTable() {
    table = (Cell*)calloc(TABLE_SIZE, sizeof(Cell));
}

void freeTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i].key && table[i].key != (char*)-1) {
            free(table[i].key);
        }
    }
    free(table);
}

int findKey(const char* key) {
    unsigned int h1 = hash1(key);
    unsigned int h2 = hash2(key);
    unsigned int idx = h1;

    for (int i = 0; i < 10; i++) {
        char* k = table[idx].key;
        if (!k)
            return 0;
        if (k != (char*)-1 && strcmp(k, key) == 0)
            return 1;
        idx = (idx + h2) % TABLE_SIZE;
    }
    return 0;
}

void addKey(const char* key) {
    if (findKey(key))
        return;

    unsigned int h1 = hash1(key);
    unsigned int h2 = hash2(key);
    unsigned int idx = h1;
    char* new_key = strdup(key);
    if (!new_key)
        return;

    for (int i = 0; i < 10; i++) {
        if (!table[idx].key || table[idx].key == (char*)-1) {
            table[idx].key = new_key;
            return;
        }
        idx = (idx + h2) % TABLE_SIZE;
    }

    free(new_key);
}

void deleteKey(const char* key) {
    unsigned int h1 = hash1(key);
    unsigned int h2 = hash2(key);
    unsigned int idx = h1;

    for (int i = 0; i < 10; i++) {
        char* k = table[idx].key;
        if (!k)
            return;
        if (k != (char*)-1 && strcmp(k, key) == 0) {
            free(k);
            table[idx].key = (char*)-1;
            return;
        }
        idx = (idx + h2) % TABLE_SIZE;
    }
}

int main() {
    initTable();
    char ch;
    int num;
    char key_str[MAX_STR_LEN];

    while (scanf(" %c %d", &ch, &num) == 2) {
        snprintf(key_str, MAX_STR_LEN, "%d", num);

        switch (ch) {
        case 'a':
            addKey(key_str);
            break;
        case 'r':
            deleteKey(key_str);
            break;
        case 'f':
            printf("%s\n", findKey(key_str) ? "yes" : "no");
            break;
        }
    }

    freeTable();
    return 0;
}
