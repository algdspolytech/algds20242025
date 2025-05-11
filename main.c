#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_TABLE_SIZE 1000
#define MAX_KEY_STR_LEN 32

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

HashTable* createHashTable(int size);
void deleteHashTable(HashTable *table);
int findIndex(HashTable *table, const char *key, int *found);
void rehash(HashTable *table);
void addString(HashTable *table, const char *key);
void removeString(HashTable *table, const char *key);
int containsString(HashTable *table, const char *key);
long long hashString(const char *str);

long long hashString(const char *str) {
    long long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

HashTable* createHashTable(int size) {
    if (size <= 0) return NULL;
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->capacity = size;
    table->size = 0;
    table->slots = (Node*)calloc(size, sizeof(Node));
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
        if (table->slots[i].str && table->slots[i].status != EMPTY)
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
    Node *new_slots = (Node*)calloc(new_capacity, sizeof(Node));
    if (!new_slots) {
        fprintf(stderr, "Ошибка при выделении памяти для новой таблицы.\n");
        return;
    }

    for (int i = 0; i < new_capacity; i++) {
        new_slots[i].str = NULL;
        new_slots[i].status = EMPTY;
    }

    table->slots = new_slots;
    table->capacity = new_capacity;
    table->size = 0;

    for (int i = 0; i < old_capacity; i++) {
        if (old_slots[i].status == OCCUPIED) {
            addString(table, old_slots[i].str);
            free(old_slots[i].str);
        }
    }

    free(old_slots);
}

void addString(HashTable *table, const char *key) {
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

void removeString(HashTable *table, const char *key) {
    if (!key) return;

    int found;
    int index = findIndex(table, key, &found);
    if (index == -1 || !found) return;

    free(table->slots[index].str);
    table->slots[index].str = NULL;
    table->slots[index].status = DELETED;
    table->size--;
}

int containsString(HashTable *table, const char *key) {
    if (!key) return 0;

    int found;
    findIndex(table, key, &found);
    return found;
}

int main(void)
{
    int key;
    char ch;
    HashTable *table = createHashTable(INITIAL_TABLE_SIZE);

    if (!table) {
        fprintf(stderr, "Не удалось создать хеш-таблицу.\n");
        return EXIT_FAILURE;
    }

    while (scanf(" %c %d", &ch, &key) == 2)
    {
        char key_str[MAX_KEY_STR_LEN];
        snprintf(key_str, sizeof(key_str), "%d", key);

        switch (ch)
        {
        case 'a':
            addString(table, key_str);
            break;

        case 'r':
            removeString(table, key_str);
            break;

        case 'f':
            printf("%s\n", containsString(table, key_str) ? "yes" : "no");
            break;

        default:
            break;
        }
    }

    deleteHashTable(table);
    return 0;
}