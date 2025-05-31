#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_TABLE_SIZE 101
#define LOAD_FACTOR_THRESHOLD 0.7

typedef enum { EMPTY, OCCUPIED, DELETED } EntryState;

typedef struct {
    char* str;
    EntryState status;
} Node;

typedef struct {
    Node* slots;
    int size;
    int capacity;
} HashTable;

void add(HashTable* table, const char* key);
void rehash(HashTable* table);

unsigned long long Hash(const char* str) {
    unsigned long long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int findIndex(HashTable* table, const char* key, int* found) {
    long long hash = Hash(key);
    int capacity = table->capacity;
    *found = 0;

    for (int i = 0; i < capacity; i++) {
        int index = (hash + i * i) % capacity;
        Node* slot = &table->slots[index];

        if (slot->status == EMPTY) {
            return index;
        }

        if (slot->status == OCCUPIED && strcmp(slot->str, key) == 0) {
            *found = 1;
            return index;
        }
    }

    return -1;
}

void rehash(HashTable* table) {
    int old_capacity = table->capacity;
    Node* old_slots = table->slots;

    int new_capacity = old_capacity * 2;
    Node* new_slots = (Node*)calloc(new_capacity, sizeof(Node));
    for (int i = 0; i < new_capacity; i++) {
        new_slots[i].str = NULL;
        new_slots[i].status = EMPTY;
    }

    table->slots = new_slots;
    table->capacity = new_capacity;
    table->size = 0;

    for (int i = 0; i < old_capacity; i++) {
        if (old_slots[i].status == OCCUPIED) {
            add(table, old_slots[i].str);
        }
        free(old_slots[i].str);
    }

    free(old_slots);
}

HashTable* createHashTable(int initial_capacity) {
    HashTable* table = malloc(sizeof(HashTable));
    table->capacity = initial_capacity;
    table->size = 0;
    table->slots = (Node*)calloc(table->capacity, sizeof(Node));
    for (int i = 0; i < table->capacity; i++) {
        table->slots[i].str = NULL;
        table->slots[i].status = EMPTY;
    }
    return table;
}

void deleteHashTable(HashTable* table) {
    if (!table) return;
    for (int i = 0; i < table->capacity; i++) {
        if (table->slots[i].status == OCCUPIED) {
            free(table->slots[i].str);
        }
    }
    free(table->slots);
    free(table);
}

void add(HashTable* table, const char* key) {
    if (!key) return;

    if ((double)table->size / table->capacity >= LOAD_FACTOR_THRESHOLD) {
        rehash(table);
    }

    int found;
    int index = findIndex(table, key, &found);

    if (found) {
        return;
    }

    table->slots[index].str = strdup(key);
    table->slots[index].status = OCCUPIED;
    table->size++;
}

void del(HashTable* table, const char* key) {
    int found = 0;
    int index = findIndex(table, key, &found);

    if (!found) {
        return;
    }

    free(table->slots[index].str);
    table->slots[index].str = NULL;
    table->slots[index].status = DELETED;
    table->size--;
}

int contains(HashTable* table, const char* key) {
    int found = 0;
    findIndex(table, key, &found);
    return found;
}

int parse_input(const char* input, char* letter, char* word) {
    while (*input && isspace((unsigned char)*input)) input++;
    if (!*input) return 0;

    *letter = *input++;
    while (*input && isspace((unsigned char)*input)) input++;
    if (!*input) return 0;

    strcpy(word, input);
    return 1;
}


int main() {
    HashTable *set = createHashTable(INITIAL_TABLE_SIZE);
    char input[1000];
    char letter, word[1000];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) break;

        if (parse_input(input, &letter, word)) {
            if (letter == 'a') {
                add(set, word);
            }
            else if (letter == 'r') {
                del(set, word);
            }
            else if (letter == 'f') {
                printf(contains(set, word) ? "yes\n" : "no\n");
            }
        }
    }

    deleteHashTable(set);
    return 0;
}