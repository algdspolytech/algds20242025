#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000003

typedef struct {
    char* key;
    int is_deleted;
    int is_used;
} Bucket;

typedef struct {
    Bucket* buckets;
    int size;
} StringTable;

unsigned int firstHashFunc(const char* s);
unsigned int secondHashFunc(const char* s);
void initTable(StringTable* tbl);
void insertKey(StringTable* tbl, const char* s);
void removeKey(StringTable* tbl, const char* s);
int hasKey(StringTable* tbl, const char* s);
void freeTable(StringTable* tbl);

unsigned int firstHashFunc(const char* s) {
    unsigned int h = 2166136261u;
    while (*s) {
        h ^= (unsigned char)*s;
        h *= 16777619u;
        s++;
    }
    return h % TABLE_SIZE;
}

unsigned int secondHashFunc(const char* s) {
    unsigned int h = 5381;
    while (*s) {
        h = ((h << 5) + h) ^ (unsigned char)*s;
        s++;
    }
    return (h % (TABLE_SIZE - 2)) + 1;
}

void initTable(StringTable* tbl) {
    tbl->size = TABLE_SIZE;
    tbl->buckets = (Bucket*)calloc(TABLE_SIZE, sizeof(Bucket));
}

void insertKey(StringTable* tbl, const char* s) {
    if (hasKey(tbl, s)) return;

    unsigned int idx = firstHashFunc(s);
    unsigned int step = secondHashFunc(s);
    unsigned int tries = 0;

    while (tries < TABLE_SIZE) {
        Bucket* b = &tbl->buckets[idx];

        if (!b->is_used || b->is_deleted) {
            free(b->key);
            b->key = strdup(s);
            b->is_used = 1;
            b->is_deleted = 0;
            return;
        }

        tries++;
        idx = (idx + step) % TABLE_SIZE;
    }

    fprintf(stderr, "Hash table full\n");
}

void removeKey(StringTable* tbl, const char* s) {
    unsigned int idx = firstHashFunc(s);
    unsigned int step = secondHashFunc(s);
    unsigned int tries = 0;

    while (tries < TABLE_SIZE && tbl->buckets[idx].is_used) {
        Bucket* b = &tbl->buckets[idx];

        if (!b->is_deleted && strcmp(b->key, s) == 0) {
            free(b->key);
            b->key = NULL;
            b->is_deleted = 1;
            return;
        }

        tries++;
        idx = (idx + step) % TABLE_SIZE;
    }
}

int hasKey(StringTable* tbl, const char* s) {
    unsigned int idx = firstHashFunc(s);
    unsigned int step = secondHashFunc(s);
    unsigned int tries = 0;

    while (tries < TABLE_SIZE && tbl->buckets[idx].is_used) {
        Bucket* b = &tbl->buckets[idx];

        if (!b->is_deleted && strcmp(b->key, s) == 0) {
            return 1;
        }

        tries++;
        idx = (idx + step) % TABLE_SIZE;
    }

    return 0;
}

void freeTable(StringTable* tbl) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        free(tbl->buckets[i].key);
    }
    free(tbl->buckets);
}

int main() {
    StringTable strTable;
    initTable(&strTable);

    char command[2];
    char value[256];

    while (scanf("%1s %255s", command, value) == 2) {
        switch (command[0]) {
        case 'a':
            insertKey(&strTable, value);
            break;
        case 'r':
            removeKey(&strTable, value);
            break;
        case 'f':
            printf(hasKey(&strTable, value) ? "yes\n" : "no\n");
            break;
        }
    }

    freeTable(&strTable);
    return 0;
}