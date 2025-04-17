#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_TABLE_SIZE 1000

typedef enum { EMPTY, OCCUPIED, DELETED } Status;

typedef struct {
    char *str;
    Status status;
} Node;

typedef struct {
    int capacity;
    int size;
    Node *slots;
} HashTable;

void add(HashTable *table, const char *key);
void rehash(HashTable *table);


long long hashString(const char *str) {
    long long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(c);

    return hash;
}

HashTable *createHashTable(int size) {
    if (size <= 0) return NULL;
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->capacity = size;
    table->size = 0;
    table->slots = (Node *)calloc(size, sizeof(Node));
    if (!table->slots) {
        free(table);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        table->slots[i].str = NULL;
        table->slots[i].status = EMPTY;
    }

    return table;
}

void deleteHashTable(HashTable *table) {
    if (!table) return;
    for (int i = 0; i < table->capacity; i++) {
        free(table->slots[i].str);
    }
    free(table->slots);
    free(table);
}

int findIndex(HashTable *table, const char *key, int *found) {
    long long hash = hashString(key);
    int capacity = table->capacity;
    *found = 0;

    for (int i = 0; i < capacity; i++) {
        int index = (hash + i * i) % capacity;
        Node *slot = &table->slots[index];

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

void rehash(HashTable *table) {
    int old_capacity = table->capacity;
    Node *old_slots = table->slots;

    int new_capacity = old_capacity * 2;
    Node *new_slots = (Node *)calloc(new_capacity, sizeof(Node));
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

void add(HashTable *table, const char *key) {
    if (!key) return;

    if ((double)table->size / (double)table->capacity >= 0.7) {
        rehash(table);
    }

    int found;
    int index = findIndex(table, key, &found);
    if (index == -1 || found) return;

    table->slots[index].str = strdup(key);
    table->slots[index].status = OCCUPIED;
    table->size++;
}

void del(HashTable *table, const char *key) {
    if (!key) return;
    int found;
    int index = findIndex(table, key, &found);
    if (index == -1 || !found) return;

    free(table->slots[index].str);
    table->slots[index].str = NULL;
    table->slots[index].status = DELETED;
    table->size--;
}

int contains(HashTable *table, const char *key) {
    if (!key) return 0;
    int found;
    int index = findIndex(table, key, &found);
    return found;
}

int parse_input(char *input, char *letter, char *word) {
    return sscanf(input, " %c %s", letter, word) == 2 && isalpha(*letter);
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
            } else if (letter == 'r') {
                del(set, word);
            } else if (letter == 'f') {
                printf(contains(set, word) ? "yes\n" : "no\n");
            }
        }
    }

    deleteHashTable(set);
    return 0;
}
