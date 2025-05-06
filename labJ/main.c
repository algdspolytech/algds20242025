#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10000000
#define MAX_KEY_LENGTH 100
#define MAX_INPUT_LENGTH (MAX_KEY_LENGTH + 2)

typedef struct {
    char* key;
} HashItem;

static HashItem* hashTable = NULL;

static inline unsigned int hash1(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (unsigned char)*key++;
    }
    return hash % TABLE_SIZE;
}

static inline unsigned int hash2(const char* key) {
    unsigned int hash = 5381;
    while (*key) {
        hash = (hash * 33) ^ (unsigned char)*key++;
    }
    return (hash % (TABLE_SIZE - 1)) | 1;
}

void initHashTable() {
    if (!hashTable) {
        hashTable = (HashItem*)calloc(TABLE_SIZE, sizeof(HashItem));
    }
}

void cleanupHashTable() {
    if (hashTable) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            char* key = hashTable[i].key;
            if (key && key != (char*)-1) {
                free(key);
            }
        }
        free(hashTable);
        hashTable = NULL;
    }
}

int find(const char* key) {
    unsigned int h1 = hash1(key);
    unsigned int h2 = hash2(key);
    unsigned int index = h1;
    const int max_attempts = 50;

    for (int i = 0; i < max_attempts; i++) {
        char* current_key = hashTable[index].key;
        if (!current_key)
            return -1;
        if (current_key != (char*)-1 && strcmp(current_key, key) == 0) {
            return index;
        }
        index = (index + h2) % TABLE_SIZE;
    }
    return -1;
}

void insert(const char* key) {
    if (find(key) != -1)
        return;

    unsigned int h1 = hash1(key);
    unsigned int h2 = hash2(key);
    unsigned int index = h1;
    char* new_key = strdup(key);
    if (!new_key)
        return;

    const int max_attempts = 50;
    for (int i = 0; i < max_attempts; i++) {
        if (!hashTable[index].key || hashTable[index].key == (char*)-1) {
            hashTable[index].key = new_key;
            return;
        }
        index = (index + h2) % TABLE_SIZE;
    }

    free(new_key);
}

void removeKey(const char* key) {
    int pos = find(key);
    if (pos != -1) {
        free(hashTable[pos].key);
        hashTable[pos].key = (char*)-1;
    }
}

static inline int isValidInput(const char* input) {
    if (strlen(input) < 3)
        return 0;
    if (input[0] != 'a' && input[0] != 'r' && input[0] != 'f')
        return 0;
    if (input[1] != ' ')
        return 0;
    return 1;
}

int main() {
    initHashTable();
    char input[MAX_INPUT_LENGTH + 1];

    while (fgets(input, sizeof(input), stdin)) {
        char* newline = strchr(input, '\n');
        if (newline)
            *newline = '\0';
        if (!input[0])
            continue;

        if (!isValidInput(input))
            continue;

        char operation = input[0];
        const char* key = input + 2;

        switch (operation) {
        case 'a':
            insert(key);
            break;
        case 'r':
            removeKey(key);
            break;
        case 'f':
            puts(find(key) != -1 ? "yes" : "no");
            break;
        }
    }

    cleanupHashTable();
    return 0;
}