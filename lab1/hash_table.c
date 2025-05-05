#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Хеш-функция для строк (djb2)
unsigned long hash_function(const char* str, int capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % capacity;
}

HashTable* ht_create(int capacity) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->buckets = calloc(capacity, sizeof(HashNode*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }

    table->size = 0;
    table->capacity = capacity;
    return table;
}

void ht_destroy(HashTable* table) {
    if (!table) return;

    for (int i = 0; i < table->capacity; i++) {
        HashNode* node = table->buckets[i];
        while (node) {
            HashNode* next = node->next;
            free(node->key);
            free(node->value);
            free(node);
            node = next;
        }
    }

    free(table->buckets);
    free(table);
}

bool ht_insert(HashTable* table, const char* key, const char* value) {
    if (!table || !key || !value) return false;

    unsigned long index = hash_function(key, table->capacity);
    HashNode* node = table->buckets[index];

    // Проверяем, существует ли уже ключ
    while (node) {
        if (strcmp(node->key, key) == 0) {
            // Ключ существует, обновляем значение
            free(node->value);
            node->value = strdup(value);
            return node->value != NULL;
        }
        node = node->next;
    }

    // Создаем новый узел
    HashNode* new_node = malloc(sizeof(HashNode));
    if (!new_node) return false;

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    if (!new_node->key || !new_node->value) {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return false;
    }

    // Добавляем в начало цепочки
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->size++;

    return true;
}

char* ht_search(HashTable* table, const char* key) {
    if (!table || !key) return NULL;

    unsigned long index = hash_function(key, table->capacity);
    HashNode* node = table->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    return NULL;
}

bool ht_delete(HashTable* table, const char* key) {
    if (!table || !key) return false;

    unsigned long index = hash_function(key, table->capacity);
    HashNode* node = table->buckets[index];
    HashNode* prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            }
            else {
                table->buckets[index] = node->next;
            }

            free(node->key);
            free(node->value);
            free(node);
            table->size--;
            return true;
        }
        prev = node;
        node = node->next;
    }

    return false;
}

void ht_print(HashTable* table) {
    if (!table) return;

    printf("Hash Table (size: %d, capacity: %d):\n", table->size, table->capacity);
    for (int i = 0; i < table->capacity; i++) {
        printf("Bucket %d: ", i);
        HashNode* node = table->buckets[i];
        while (node) {
            printf("[%s: %s] -> ", node->key, node->value);
            node = node->next;
        }
        printf("NULL\n");
    }
}