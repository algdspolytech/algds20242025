#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_CAPACITY 1000039
#define MAX_INPUT_LENGTH 256

typedef enum {
    SLOT_VACANT,
    SLOT_FILLED,
    SLOT_REMOVED
} SlotStatus;

typedef struct {
    char* data;
    SlotStatus flag;
} HashSlot;

HashSlot hashTable[HASH_TABLE_CAPACITY];

unsigned int computeFirstHash(const char* str) {
    unsigned int value = 0xdeadbeef;
    while (*str) {
        value = (value * 131) + *str++;
        value ^= value >> 16;
    }
    return value % HASH_TABLE_CAPACITY;
}

unsigned int computeSecondHash(const char* str) {
    unsigned int value = 0xabcdef12;
    while (*str) {
        value = (value * 167) + *str++;
        value ^= value >> 13;
    }
    return (value % (HASH_TABLE_CAPACITY - 100)) + 1;
}

int storeElement(HashSlot* storage, const char* element) {
    unsigned int base = computeFirstHash(element);
    unsigned int step = computeSecondHash(element);
    int emptySlot = -1;

    for (int attempt = 0; attempt < HASH_TABLE_CAPACITY; ++attempt) {
        unsigned int current = (base + attempt * step) % HASH_TABLE_CAPACITY;

        if (storage[current].flag == SLOT_FILLED &&
            strcmp(storage[current].data, element) == 0)
            return 0;

        if (storage[current].flag == SLOT_REMOVED && emptySlot == -1)
            emptySlot = current;

        if (storage[current].flag == SLOT_VACANT) {
            if (emptySlot != -1) current = emptySlot;
            storage[current].data = strdup(element);
            storage[current].flag = SLOT_FILLED;
            return 1;
        }
    }

    if (emptySlot != -1) {
        storage[emptySlot].data = strdup(element);
        storage[emptySlot].flag = SLOT_FILLED;
        return 1;
    }
    return 0;
}

int removeElement(HashSlot* storage, const char* element) {
    unsigned int base = computeFirstHash(element);
    unsigned int step = computeSecondHash(element);

    for (int attempt = 0; attempt < HASH_TABLE_CAPACITY; ++attempt) {
        unsigned int current = (base + attempt * step) % HASH_TABLE_CAPACITY;

        if (storage[current].flag == SLOT_VACANT)
            return 0;

        if (storage[current].flag == SLOT_FILLED &&
            strcmp(storage[current].data, element) == 0) {
            free(storage[current].data);
            storage[current].flag = SLOT_REMOVED;
            return 1;
        }
    }
    return 0;
}

int checkElement(HashSlot* storage, const char* element) {
    unsigned int base = computeFirstHash(element);
    unsigned int step = computeSecondHash(element);

    for (int attempt = 0; attempt < HASH_TABLE_CAPACITY; ++attempt) {
        unsigned int current = (base + attempt * step) % HASH_TABLE_CAPACITY;

        if (storage[current].flag == SLOT_VACANT)
            return 0;

        if (storage[current].flag == SLOT_FILLED &&
            strcmp(storage[current].data, element) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char command;
    char input[MAX_INPUT_LENGTH];

    while (scanf(" %c %255s", &command, input) == 2) {
        switch (command) {
        case 'a': storeElement(hashTable, input); break;
        case 'r': removeElement(hashTable, input); break;
        case 'f':
            printf("%s\n", checkElement(hashTable, input) ? "yes" : "no");
            break;
        }
    }
    return 0;
}