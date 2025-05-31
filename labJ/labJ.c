#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_CAPACITY 10000000
#define MAX_STR_LEN 100
#define INPUT_BUFFER_SIZE (MAX_STR_LEN + 2)

typedef struct {
    char* data;
} HashEntry;

static HashEntry* hashStorage = NULL;

static inline unsigned int primaryHash(const char* str) {
    unsigned int value = 2166136261u;
    while (*str) {
        value = (value ^ (unsigned char)*str++) * 16777619u;
    }
    return value % HASH_CAPACITY;
}

static inline unsigned int secondaryHash(const char* str) {
    unsigned int value = 0;
    while (*str) {
        value = (value * 65599) + (unsigned char)*str++;
    }
    return (value % (HASH_CAPACITY - 100)) + 1;
}

void initializeHashStorage() {
    if (!hashStorage) {
        hashStorage = (HashEntry*)calloc(HASH_CAPACITY, sizeof(HashEntry));
    }
}

void releaseHashStorage() {
    if (hashStorage) {
        for (int i = 0; i < HASH_CAPACITY; i++) {
            char* entry = hashStorage[i].data;
            if (entry && entry != (char*)-1) {
                free(entry);
            }
        }
        free(hashStorage);
        hashStorage = NULL;
    }
}

int locateEntry(const char* str) {
    unsigned int h1 = primaryHash(str);
    unsigned int h2 = secondaryHash(str);
    unsigned int position = h1;
    const int max_iterations = 50;

    for (int i = 0; i < max_iterations; i++) {
        char* current = hashStorage[position].data;
        if (!current)
            return -1;
        if (current != (char*)-1 && strcmp(current, str) == 0) {
            return position;
        }
        position = (position + h2) % HASH_CAPACITY;
    }
    return -1;
}

void storeEntry(const char* str) {
    if (locateEntry(str) != -1)
        return;

    unsigned int h1 = primaryHash(str);
    unsigned int h2 = secondaryHash(str);
    unsigned int position = h1;
    char* new_entry = strdup(str);
    if (!new_entry)
        return;

    const int max_iterations = 50;
    for (int i = 0; i < max_iterations; i++) {
        if (!hashStorage[position].data || hashStorage[position].data == (char*)-1) {
            hashStorage[position].data = new_entry;
            return;
        }
        position = (position + h2) % HASH_CAPACITY;
    }

    free(new_entry);
}

void eraseEntry(const char* str) {
    int pos = locateEntry(str);
    if (pos != -1) {
        free(hashStorage[pos].data);
        hashStorage[pos].data = (char*)-1;
    }
}

static inline int validateInput(const char* input) {
    if (strlen(input) < 3)
        return 0;
    if (input[0] != 'a' && input[0] != 'r' && input[0] != 'f')
        return 0;
    if (input[1] != ' ')
        return 0;
    return 1;
}

int main() {
    initializeHashStorage();
    char input[INPUT_BUFFER_SIZE + 1];

    while (fgets(input, sizeof(input), stdin)) {
        char* newline = strchr(input, '\n');
        if (newline)
            *newline = '\0';
        if (!input[0])
            continue;

        if (!validateInput(input))
            continue;

        char operation = input[0];
        const char* str = input + 2;

        switch (operation) {
        case 'a':
            storeEntry(str);
            break;
        case 'r':
            eraseEntry(str);
            break;
        case 'f':
            puts(locateEntry(str) != -1 ? "yes" : "no");
            break;
        }
    }

    releaseHashStorage();
    return 0;
}