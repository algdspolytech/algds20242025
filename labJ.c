#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define TABLE_SIZE 8191

typedef struct Node {
    char* key;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    int size;
} HashTable;

// Прототипы функций
unsigned int hash(const char* key, int size);
HashTable* create_hash_table();
Node* create_node(const char* key);
bool search(HashTable* ht, const char* key); // Добавлено объявление
bool insert(HashTable* ht, const char* key);
bool delete(HashTable* ht, const char* key);
void free_hash_table(HashTable* ht);

// Реализации функций
unsigned int hash(const char* key, int size) {
    unsigned long h = 0;
    while (*key) {
        h = (h * 31) + (unsigned char)(*key++);
    }
    return h % size;
}

HashTable* create_hash_table() {
    HashTable* ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->size = TABLE_SIZE;
    ht->buckets = calloc(TABLE_SIZE, sizeof(Node*));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    return ht;
}

Node* create_node(const char* key) {
    if (!key || strlen(key) == 0) return NULL;

    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->key = strdup(key);
    if (!node->key) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

bool search(HashTable* ht, const char* key) {
    if (!ht || !key || strlen(key) == 0) return false;

    unsigned int index = hash(key, ht->size);
    for (Node* curr = ht->buckets[index]; curr; curr = curr->next) {
        if (strcmp(curr->key, key) == 0) {
            return true;
        }
    }
    return false;
}

bool insert(HashTable* ht, const char* key) {
    if (!ht || !key || strlen(key) == 0) return false;
    if (search(ht, key)) return true;

    unsigned int index = hash(key, ht->size);
    Node* node = create_node(key);
    if (!node) return false;

    node->next = ht->buckets[index];
    ht->buckets[index] = node;
    return true;
}

bool delete(HashTable* ht, const char* key) {
    if (!ht || !key || strlen(key) == 0) return false;

    unsigned int index = hash(key, ht->size);
    Node** ptr = &ht->buckets[index];

    while (*ptr) {
        if (strcmp((*ptr)->key, key) == 0) {
            Node* tmp = *ptr;
            *ptr = (*ptr)->next;
            free(tmp->key);
            free(tmp);
            return true;
        }
        ptr = &(*ptr)->next;
    }
    return false;
}

void free_hash_table(HashTable* ht) {
    if (!ht) return;

    for (int i = 0; i < ht->size; i++) {
        Node* curr = ht->buckets[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(ht->buckets);
    free(ht);
}

int main() {
    HashTable* ht = create_hash_table();
    char cmd;
    char key[257];

    while (scanf(" %c %256s", &cmd, key) == 2) {
        // Нормализация ввода
        for (char* p = key; *p; p++) *p = tolower(*p);

        switch (cmd) {
        case 'a': insert(ht, key); break;
        case 'r': delete(ht, key); break;
        case 'f':
            printf("%s\n", search(ht, key) ? "yes" : "no");
            fflush(stdout);
            break;
        }
    }

    free_hash_table(ht);
    return 0;
}