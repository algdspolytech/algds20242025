#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000

typedef struct Node {
    char *key;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
} HashTable;

unsigned int hash(const char *key) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value * 31) + *key;
        key++;
    }
    return hash_value % TABLE_SIZE;
}

void initTable(HashTable *table) {
    table->buckets = (Node **)calloc(TABLE_SIZE, sizeof(Node *));
    table->size = TABLE_SIZE;
}

Node *createNode(const char *key) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode) {
        newNode->key = strdup(key);
        newNode->next = NULL;
    }
    return newNode;
}

void addNode(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Node *newNode = createNode(key);
    if (!newNode) return;

    if (!table->buckets[index]) {
        table->buckets[index] = newNode;
        return;
    }

    Node *current = table->buckets[index];
    Node *prev = NULL;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            free(newNode->key);
            free(newNode);
            return;
        }
        prev = current;
        current = current->next;
    }

    prev->next = newNode;
}

int findNode(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Node *current = table->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void deleteNode(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Node *current = table->buckets[index];
    Node *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void freeList(Node *head) {
    Node *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp);
    }
}

void freeHashTable(HashTable *table) {
    for (size_t i = 0; i < table->size; i++) {
        if (table->buckets[i]) {
            freeList(table->buckets[i]);
        }
    }
    free(table->buckets);
}

int main(void) {
    HashTable table;
    initTable(&table);

    char ch[2];
    char key[133];
    while (scanf("%1s %132s", ch, key) == 2) {
        switch (ch[0]) {
        case 'a':
            addNode(&table, key);
            break;
        case 'r':
            deleteNode(&table, key);
            break;
        case 'f':
            printf(findNode(&table, key) ? "yes\n" : "no\n");
            break;
        default:
            break;
        }
    }
    freeHashTable(&table);
    return 0;
}