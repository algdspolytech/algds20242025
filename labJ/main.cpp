#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define START_SIZE 500

typedef enum { EMPTY, OCCUPIED, DELETED } Status;

typedef struct {
    char* str;
    Status status;
} Node;

typedef struct {
    int capacity;
    int size;
    Node* slots;
} HashTable;

void add(HashTable* t, const char* k);
void rehash(HashTable* t);

HashTable* createHashTable(int s) {
    if (s <= 0) return NULL;
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->capacity = s;
    table->size = 0;
    table->slots = (Node*)calloc(s, sizeof(Node));
    if (!table->slots) {
        free(table);
        return NULL;
    }

    for (int i = 0; i < s; i++) {
        table->slots[i].str = NULL;
        table->slots[i].status = EMPTY;
    }

    return table;
}

long long hashString(const char* str) {
    long long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + tolower(c);

    return hash;
}

int findIndex(HashTable* t, const char* k, int* flag) {
    long long hash = hashString(k);
    int capacity = t->capacity;
    *flag = 0;

    for (int i = 0; i < capacity; i++) {
        int index = (hash + i * i) % capacity;
        Node* slot = &t->slots[index];

        if (slot->status == EMPTY) {
            return index;
        }

        if (slot->status == OCCUPIED && strcmp(slot->str, k) == 0) {
            *flag = 1;
            return index;
        }
    }

    return -1;
}

void deleteHashTable(HashTable* t) {
    if (!t) return;
    for (int i = 0; i < t->capacity; i++) {
        free(t->slots[i].str);
    }
    free(t->slots);
    free(t);
}

void rehash(HashTable* t) {
    int old_capacity = t->capacity;
    Node* old_slots = t->slots;

    int new_capacity = old_capacity * 2;
    Node* new_slots = (Node*)calloc(new_capacity, sizeof(Node));
    for (int i = 0; i < new_capacity; i++) {
        new_slots[i].str = NULL;
        new_slots[i].status = EMPTY;
    }

    t->slots = new_slots;
    t->capacity = new_capacity;
    t->size = 0;

    for (int i = 0; i < old_capacity; i++) {
        if (old_slots[i].status == OCCUPIED) {
            add(t, old_slots[i].str);
        }
        free(old_slots[i].str);
    }

    free(old_slots);
}

void add(HashTable* t, const char* k) {
    if (!k) return;

    if ((double)t->size / (double)t->capacity >= 0.7) {
        rehash(t);
    }

    int found;
    int index = findIndex(t, k, &found);
    if (index == -1 || found) return;

    t->slots[index].str = strdup(k);
    t->slots[index].status = OCCUPIED;
    t->size++;
}

void del(HashTable* t, const char* k) {
    if (!k) return;
    int found;
    int index = findIndex(t, k, &found);
    if (index == -1 || !found) return;

    free(t->slots[index].str);
    t->slots[index].str = NULL;
    t->slots[index].status = DELETED;
    t->size--;
}

int contains(HashTable* t, const char* k) {
    if (!k) return 0;
    int found;
    int index = findIndex(t, k, &found);
    return found;
}

int read(char* str, char* letter, char* word) {
    return sscanf(str, " %c %s", letter, word) == 2 && isalpha(*letter);
}

int main() {
    HashTable* set = createHashTable(START_SIZE);
    char input[1000];
    char letter, word[1000];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) break;

        if (read(input, &letter, word)) {
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