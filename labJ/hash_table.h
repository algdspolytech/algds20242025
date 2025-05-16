#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

// Структура для узла цепочки
typedef struct HashNode {
    char* key;
    char* value;
    struct HashNode* next;
} HashNode;

// Структура хеш-таблицы
typedef struct {
    HashNode** buckets;
    int size;
    int capacity;
} HashTable;

// Инициализация хеш-таблицы
HashTable* ht_create(int capacity);

// Освобождение памяти хеш-таблицы
void ht_destroy(HashTable* table);

// Вставка элемента в хеш-таблицу
bool ht_insert(HashTable* table, const char* key, const char* value);

// Поиск элемента в хеш-таблице
char* ht_search(HashTable* table, const char* key);

// Удаление элемента из хеш-таблицы
bool ht_delete(HashTable* table, const char* key);

// Вывод содержимого хеш-таблицы (для отладки)
void ht_print(HashTable* table);

#endif // HASH_TABLE_H