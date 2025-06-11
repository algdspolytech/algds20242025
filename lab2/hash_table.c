#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000003

typedef struct Node {
    char* key;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    int size;
} HashTable;

unsigned int hash1(const char* key);
void initHashTable(HashTable* table);
void insert(HashTable* table, const char* key);
void removeKey(HashTable* table, const char* key);
int search(HashTable* table, const char* key);
void freeHashTable(HashTable* table);

unsigned int hash1(const char* key) {
    unsigned int h = 2166136261u;
    while (*key) {
        h ^= *key++;
        h *= 16777619u;
    }
    return h % TABLE_SIZE;
}

void initHashTable(HashTable* table) {
    table->size = TABLE_SIZE;
    table->buckets = (Node**)calloc(TABLE_SIZE, sizeof(Node*));
}

void insert(HashTable* table, const char* key) {
    unsigned int idx = hash1(key);

    Node* current = table->buckets[idx];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return;
        }
        current = current->next;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;

    newNode->key = strdup(key);
    if (!newNode->key) {
        free(newNode);
        return;
    }

    newNode->next = table->buckets[idx];
    table->buckets[idx] = newNode;
}

void removeKey(HashTable* table, const char* key) {
    unsigned int idx = hash1(key);

    Node* current = table->buckets[idx];
    Node* prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                table->buckets[idx] = current->next;
            }

            free(current->key);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

int search(HashTable* table, const char* key) {
    unsigned int idx = hash1(key);

    Node* current = table->buckets[idx];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Node* current = table->buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
}

int main() {
    HashTable table;
    initHashTable(&table);

    char op[2];
    char key[256];

    while (scanf("%1s %255s", op, key) == 2) {
        switch (op[0]) {
        case 'a':
            insert(&table, key);
            break;
        case 'r':
            removeKey(&table, key);
            break;
        case 'f':
            printf("%s\n", search(&table, key) ? "yes" : "no");
            break;
        }
    }

    freeHashTable(&table);
    return 0;
}