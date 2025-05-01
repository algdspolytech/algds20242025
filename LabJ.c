#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define TABLE_SIZE 1000039

typedef enum { EMPTY, OCCUPIED, DELETED } state_t;

typedef struct {
    char* key;
    state_t state;
} entry_t;

entry_t table[TABLE_SIZE];

unsigned int primary_hash(const char* key) {
    unsigned int hash = 0x9747b28c;
    while (*key) {
        hash ^= (unsigned char)(*key++);
        hash *= 0x5bd1e995;
        hash ^= hash >> 15;
    }
    return hash % TABLE_SIZE;
}

unsigned int secondary_hash(const char* key) {
    unsigned int hash = 1;
    while (*key) {
        hash *= ((unsigned char)(*key++) + 31);
        hash ^= (hash >> 3);
    }
    return (hash % (TABLE_SIZE - 2)) + 1;
}

int addNode(entry_t* table, const char* key) {
    unsigned int h1 = primary_hash(key);
    unsigned int h2 = secondary_hash(key);
    int first_deleted = -1;

    for (int i = 0; i < TABLE_SIZE; ++i) {
        unsigned int idx = (h1 + i * h2) % TABLE_SIZE;

        if (table[idx].state == OCCUPIED && strcmp(table[idx].key, key) == 0)
            return 0; 

        if (table[idx].state == DELETED && first_deleted == -1)
            first_deleted = idx;

        if (table[idx].state == EMPTY) {
            if (first_deleted != -1) idx = first_deleted;
            table[idx].key = strdup(key);
            table[idx].state = OCCUPIED;
            return 1;
        }
    }

    if (first_deleted != -1) {
        table[first_deleted].key = strdup(key);
        table[first_deleted].state = OCCUPIED;
        return 1;
    }
    return 0; 
}


int deleteNode(entry_t* table, const char* key) {
    unsigned int h1 = primary_hash(key);
    unsigned int h2 = secondary_hash(key);

    for (int i = 0; i < TABLE_SIZE; ++i) {
        unsigned int idx = (h1 + i * h2) % TABLE_SIZE;

        if (table[idx].state == EMPTY)
            return 0;

        if (table[idx].state == OCCUPIED && strcmp(table[idx].key, key) == 0) {
            free(table[idx].key);
            table[idx].state = DELETED;
            return 1;
        }
    }
    return 0;
}

int findNode(entry_t* table, const char* key) {
    unsigned int h1 = primary_hash(key);
    unsigned int h2 = secondary_hash(key);

    for (int i = 0; i < TABLE_SIZE; ++i) {
        unsigned int idx = (h1 + i * h2) % TABLE_SIZE;

        if (table[idx].state == EMPTY)
            return 0;

        if (table[idx].state == OCCUPIED && strcmp(table[idx].key, key) == 0)
            return 1;
    }
    return 0;
}

int main(void) {
    char ch;
    char key[256];

    while (scanf(" %c %255s", &ch, key) == 2) {
        switch (ch) {
        case 'a':
            addNode(table, key);
            break;
        case 'r':
            deleteNode(table, key);
            break;
        case 'f':
            printf("%s\n", findNode(table, key) ? "yes" : "no");
            break;
        default:
            break;
        }
    }
    return 0;
}
