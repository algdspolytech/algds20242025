#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000

typedef enum { EMPTY, OCCUPIED, DELETED } SlotStatus;

typedef struct {
    char* value;
    SlotStatus status;
} HashTableSlot;

typedef struct {
    int capacity;
    int size;
    HashTableSlot* slots;
} HashTable;

/* Функции работы с хеш-таблицей */
HashTable* hashTableCreate(int initial_size);
void hashTableDestroy(HashTable* table);
void hashTableInsert(HashTable* table, const char* key);
void hashTableRemove(HashTable* table, const char* key);
int hashTableContains(HashTable* table, const char* key);
void hashTableRehash(HashTable* table);
int hashTableFindSlotIndex(HashTable* table, const char* key, int* key_found);

/* Вспомогательные функции */
long long computeStringHash(const char* str);
int parseUserInput(char* input, char* command, char* word);

long long computeStringHash(const char* str) {
    long long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(c);

    return hash;
}

HashTable* hashTableCreate(int initial_size) {
    if (initial_size <= 0) return NULL;

    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->capacity = initial_size;
    table->size = 0;
    table->slots = (HashTableSlot*)calloc(initial_size, sizeof(HashTableSlot));
    if (!table->slots) {
        free(table);
        return NULL;
    }

    for (int i = 0; i < initial_size; i++) {
        table->slots[i].value = NULL;
        table->slots[i].status = EMPTY;
    }

    return table;
}

void hashTableDestroy(HashTable* table) {
    if (!table) return;

    for (int i = 0; i < table->capacity; i++) {
        free(table->slots[i].value);
    }
    free(table->slots);
    free(table);
}

int hashTableFindSlotIndex(HashTable* table, const char* key, int* key_found) {
    long long hash_value = computeStringHash(key);
    int capacity = table->capacity;
    *key_found = 0;

    for (int i = 0; i < capacity; i++) {
        int index = (hash_value + i * i) % capacity;
        HashTableSlot* slot = &table->slots[index];

        if (slot->status == EMPTY) {
            return index;
        }

        if (slot->status == OCCUPIED && strcmp(slot->value, key) == 0) {
            *key_found = 1;
            return index;
        }
    }

    return -1;
}

void hashTableRehash(HashTable* table) {
    int old_capacity = table->capacity;
    HashTableSlot* old_slots = table->slots;

    int new_capacity = old_capacity * 2;
    HashTableSlot* new_slots = (HashTableSlot*)calloc(new_capacity, sizeof(HashTableSlot));
    for (int i = 0; i < new_capacity; i++) {
        new_slots[i].value = NULL;
        new_slots[i].status = EMPTY;
    }

    table->slots = new_slots;
    table->capacity = new_capacity;
    table->size = 0;

    for (int i = 0; i < old_capacity; i++) {
        if (old_slots[i].status == OCCUPIED) {
            hashTableInsert(table, old_slots[i].value);
        }
        free(old_slots[i].value);
    }

    free(old_slots);
}

void hashTableInsert(HashTable* table, const char* key) {
    if (!key) return;

    if ((double)table->size / (double)table->capacity >= 0.7) {
        hashTableRehash(table);
    }

    int key_exists;
    int index = hashTableFindSlotIndex(table, key, &key_exists);
    if (index == -1 || key_exists) return;

    table->slots[index].value = strdup(key);
    table->slots[index].status = OCCUPIED;
    table->size++;
}

void hashTableRemove(HashTable* table, const char* key) {
    if (!key) return;

    int key_exists;
    int index = hashTableFindSlotIndex(table, key, &key_exists);
    if (index == -1 || !key_exists) return;

    free(table->slots[index].value);
    table->slots[index].value = NULL;
    table->slots[index].status = DELETED;
    table->size--;
}

int hashTableContains(HashTable* table, const char* key) {
    if (!key) return 0;

    int key_exists;
    hashTableFindSlotIndex(table, key, &key_exists);
    return key_exists;
}

int parseUserInput(char* input, char* command, char* word) {
    return sscanf(input, " %c %s", command, word) == 2 && isalpha(*command);
}

int main() {
    HashTable* hash_table = hashTableCreate(SIZE);
    char input[1000];
    char command, word[1000];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) break;

        if (parseUserInput(input, &command, word)) {
            switch (command) {
            case 'a':
                hashTableInsert(hash_table, word);
                break;
            case 'r':
                hashTableRemove(hash_table, word);
                break;
            case 'f':
                printf(hashTableContains(hash_table, word) ? "yes\n" : "no\n");
                break;
            default:
                break;
            }
        }
    }

    hashTableDestroy(hash_table);
    return 0;
}