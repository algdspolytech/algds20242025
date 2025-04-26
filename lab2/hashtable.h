#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 101 // Размер таблицы (простое число для минимизации коллизий)

// Структура для хранения данных
typedef struct {
    char *key;
    int value;
} HashEntry;

// Структура для хеш-таблицы
typedef struct {
    HashEntry *table[TABLE_SIZE];
} HashTable;

// Функции для работы с хеш-таблицей
// *по названиям их функционал понятен, но подробнее в hashtable.c
HashTable* create_table();
void destroy_table(HashTable* ht);
unsigned int hash(char *key);
int insert(HashTable *ht, char *key, int value);
int search(HashTable *ht, char *key);
int remove_entry(HashTable *ht, char *key);
void print_table(HashTable *ht);

#endif // HASHTABLE_H