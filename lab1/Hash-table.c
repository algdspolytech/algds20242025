#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_CAPACITY 1000003

typedef struct {
    char* data;
    int removed;
    int active;
} HashEntry;

typedef struct {
    HashEntry* elements;
    int capacity;
} StringHashSet;


unsigned int primaryHash(const char* str);
unsigned int secondaryHash(const char* str);
void initializeSet(StringHashSet* set);
void addElement(StringHashSet* set, const char* str);
void deleteElement(StringHashSet* set, const char* str);
int containsElement(StringHashSet* set, const char* str);
void cleanupSet(StringHashSet* set);

unsigned int primaryHash(const char* str) {
    unsigned int h = 2166136261u;
    for (; *str; str++) {
        h ^= (unsigned char)*str;
        h *= 16777619u;
    }
    return h % HASH_CAPACITY;
}


unsigned int secondaryHash(const char* str) {
    unsigned int h = 5381;
    for (; *str; str++) {
        h = ((h << 5) + h) ^ (unsigned char)*str;
    }
    return (h % (HASH_CAPACITY - 2)) + 1;
}

void initializeSet(StringHashSet* set) {
    set->capacity = HASH_CAPACITY;
    set->elements = (HashEntry*)calloc(HASH_CAPACITY, sizeof(HashEntry));
}

void addElement(StringHashSet* set, const char* str) {
    if (containsElement(set, str)) return;

    unsigned int pos = primaryHash(str);
    unsigned int stride = secondaryHash(str);
    unsigned int attempts = 0;

    while (attempts < HASH_CAPACITY) {
        HashEntry* entry = &set->elements[pos];
        
        if (!entry->active || entry->removed) {
            free(entry->data);
            entry->data = strdup(str);
            entry->active = 1;
            entry->removed = 0;
            return;
        }
        
        attempts++;
        pos = (pos + stride) % HASH_CAPACITY;
    }
    
    fprintf(stderr, "Table overflow\n");
}

void deleteElement(StringHashSet* set, const char* str) {
    unsigned int pos = primaryHash(str);
    unsigned int stride = secondaryHash(str);
    unsigned int attempts = 0;

    while (attempts < HASH_CAPACITY && set->elements[pos].active) {
        HashEntry* entry = &set->elements[pos];
        
        if (!entry->removed && strcmp(entry->data, str) == 0) {
            free(entry->data);
            entry->data = NULL;
            entry->removed = 1;
            return;
        }
        
        attempts++;
        pos = (pos + stride) % HASH_CAPACITY;
    }
}

int containsElement(StringHashSet* set, const char* str) {
    unsigned int pos = primaryHash(str);
    unsigned int stride = secondaryHash(str);
    unsigned int attempts = 0;

    while (attempts < HASH_CAPACITY && set->elements[pos].active) {
        HashEntry* entry = &set->elements[pos];
        
        if (!entry->removed && strcmp(entry->data, str) == 0) {
            return 1;
        }
        
        attempts++;
        pos = (pos + stride) % HASH_CAPACITY;
    }
    
    return 0;
}

void cleanupSet(StringHashSet* set) {
    for (int i = 0; i < HASH_CAPACITY; i++) {
        free(set->elements[i].data);
    }
    free(set->elements);
}

int main() {
    StringHashSet stringSet;
    initializeSet(&stringSet);

    char cmd[2];
    char input[256];

    while (scanf("%1s %255s", cmd, input) == 2) {
        switch (cmd[0]) {
            case 'a':
                addElement(&stringSet, input);
                break;
            case 'r':
                deleteElement(&stringSet, input);
                break;
            case 'f':
                printf(containsElement(&stringSet, input) ? "yes\n" : "no\n");
                break;
        }
    }

    cleanupSet(&stringSet);
    return 0;
}