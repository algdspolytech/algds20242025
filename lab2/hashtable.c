#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция хеширования
unsigned int hash(char *key) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value * 31) + *key++;
    }
    return hash_value % TABLE_SIZE;
}

// Создание хеш-таблицы
HashTable* create_table() {
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Удаление хеш-таблицы
void destroy_table(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i]) {
            free(ht->table[i]->key);
            free(ht->table[i]);
        }
    }
    free(ht);
}

// Вставка элемента с разрешением коллизий с помощью квадратичной последовательности проб
int insert(HashTable *ht, char *key, int value) {
    unsigned int index = hash(key);
    int i = 0;

    // Ищем подходящее место для вставки
    while (ht->table[(index + i * i) % TABLE_SIZE] != NULL) {
        if (strcmp(ht->table[(index + i * i) % TABLE_SIZE]->key, key) == 0) {
            // Если ключ уже есть, обновляем значение
            ht->table[(index + i * i) % TABLE_SIZE]->value = value;
            return 0; // Элемент обновлён
        }
        i++;
        if (i == TABLE_SIZE) return -1; // Хеш-таблица переполнена
    }

    // Вставка нового элемента
    HashEntry *new_entry = (HashEntry*)malloc(sizeof(HashEntry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    ht->table[(index + i * i) % TABLE_SIZE] = new_entry;
    
    return 0;
}

// Поиск элемента по ключу
int search(HashTable *ht, char *key) {
    unsigned int index = hash(key);
    int i = 0;

    while (ht->table[(index + i * i) % TABLE_SIZE] != NULL) {
        if (strcmp(ht->table[(index + i * i) % TABLE_SIZE]->key, key) == 0) {
            return ht->table[(index + i * i) % TABLE_SIZE]->value;
        }
        i++;
        if (i == TABLE_SIZE) return -1; // Элемент не найден
    }
    return -1; // Элемент не найден
}

// Удаление элемента
int remove_entry(HashTable *ht, char *key) {
    unsigned int index = hash(key);
    int i = 0;

    while (ht->table[(index + i * i) % TABLE_SIZE] != NULL) {
        if (strcmp(ht->table[(index + i * i) % TABLE_SIZE]->key, key) == 0) {
            free(ht->table[(index + i * i) % TABLE_SIZE]->key);
            free(ht->table[(index + i * i) % TABLE_SIZE]);
            ht->table[(index + i * i) % TABLE_SIZE] = NULL;
            return 0; // Успешное удаление
        }
        i++;
        if (i == TABLE_SIZE) return -1; // Элемент не найден
    }
    return -1; // Элемент не найден
}

// Вывод всех элементов таблицы
void print_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i] != NULL) {
            printf("Ключ: %s, Значение: %d\n", ht->table[i]->key, ht->table[i]->value);
        }
    }
}