#include <stdlib.h>
#include <string.h>
#include "labJ.h"

// хэш-функция = сумма ASCII-кодов символов
static unsigned int hash(const char* str) {
    unsigned int h = 0;
    while (*str) {
        h = h * 31 + (unsigned char)(*str++);
    }
    return h;
}

HashTable* ht_create(int capacity) {
    if (capacity <= 0) return NULL;
    HashTable* ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;
    ht->data = calloc(capacity, sizeof(char*));
    if (!ht->data) {
        free(ht);
        return NULL;
    }
    ht->capacity = capacity;
    ht->size = 0;
    return ht;
}

void ht_free(HashTable* ht) {
    if (!ht) return;
    for (int i = 0; i < ht->capacity; ++i) {
        free(ht->data[i]);
    }
    free(ht->data);
    free(ht);
}

// 1 - вставлено, 0 - ошибка вставки
int ht_insert(HashTable* ht, const char* str) {
    if (ht->size >= ht->capacity) return 0;

    unsigned int h = hash(str) % ht->capacity;
    for (int i = 0; i < ht->capacity; ++i) {
        int idx = (h + i) % ht->capacity;
        if (ht->data[idx] == NULL) {
            ht->data[idx] = _strdup(str);
            if (!ht->data[idx]) return 0;
            ht->size++;
            return 1;
        }
        if (strcmp(ht->data[idx], str) == 0) {
            return 1;
        }
    }
    return 0; 
}

// 1 - найдено, 0 - не найдено
int ht_search(HashTable* ht, const char* str) {
    unsigned int h = hash(str) % ht->capacity;
    for (int i = 0; i < ht->capacity; ++i) {
        int idx = (h + i) % ht->capacity;
        if (ht->data[idx] == NULL) {
            return 0;
        }
        if (strcmp(ht->data[idx], str) == 0) {
            return 1;
        }
    }
    return 0;
}
