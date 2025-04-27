#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define TABLE_SIZE 1000003 // Размер хеш-таблицы (простое число для лучшего распределения)

/// Структура элемента хеш-таблицы
typedef struct {
    char* key;          /// Ключ (массив символов = строка)
    int is_deleted;     /// Флаг удаления
    int is_occupied;    /// Флаг занятости
} HashItem;

/// Структура хеш-таблицы
typedef struct {
    HashItem* items;
    int size;
} HashTable;

int find_key(HashTable* table, const char* key);
unsigned int primary_hash(const char* key);
unsigned int primary_hash(const char* key) {
    unsigned int hash = 2166136261u;
    while (*key) {
        hash ^= (unsigned char)(*key++);
        hash *= 16777619u;
    }
    return hash % TABLE_SIZE;
}


unsigned int secondary_hash(const char* key) {
    unsigned int hash = 5381u;
    while (*key) {
        hash = ((hash << 5) + hash) ^ (unsigned char)(*key++);
    }
    return (hash % (TABLE_SIZE - 2)) + 1; 
}

/// Инициализация таблицы
void init_table(HashTable* table) {
    table->size = TABLE_SIZE;
    table->items = (HashItem*)calloc(TABLE_SIZE, sizeof(HashItem));
}

/// Вставка ключа в таблицу
void insert_key(HashTable* table, const char* key) {
    if (find_key(table, key)) return; /// Уже существует

    unsigned int index = primary_hash(key);
    unsigned int step = secondary_hash(key);
    unsigned int i = 0;

    while (i < TABLE_SIZE) {
        if (!table->items[index].is_occupied || table->items[index].is_deleted) {
            if (table->items[index].key) {
                free(table->items[index].key);
            }
            table->items[index].key = strdup(key);
            table->items[index].is_occupied = 1;
            table->items[index].is_deleted = 0;
            return;
        }
        i++;
        index = (index + step) % TABLE_SIZE;
    }
    fprintf(stderr, "Error: Hash table is full.\n");
}

/// Удаление ключа из таблицы
void delete_key(HashTable* table, const char* key);
void delete_key(HashTable* table, const char* key) {
    unsigned int index = primary_hash(key);
    unsigned int step = secondary_hash(key);
    unsigned int i = 0;

    while (i < TABLE_SIZE && table->items[index].is_occupied) {
        if (!table->items[index].is_deleted &&
            strcmp(table->items[index].key, key) == 0) {
            free(table->items[index].key);
            table->items[index].key = NULL;
            table->items[index].is_deleted = 1;
            return;
        }
        i++;
        index = (index + step) % TABLE_SIZE;
    }
}

/// Поиск ключа в таблице
int find_key(HashTable* table, const char* key) {
    unsigned int index = primary_hash(key);
    unsigned int step = secondary_hash(key);
    unsigned int i = 0;

    while (i < TABLE_SIZE && table->items[index].is_occupied) {
        if (!table->items[index].is_deleted &&
            strcmp(table->items[index].key, key) == 0) {
            return 1; /// Найдено
        }
        i++;
        index = (index + step) % TABLE_SIZE;
    }
    return 0; /// Не найдено
}

/// Освобождение памяти
void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->items[i].key) {
            free(table->items[i].key);
        }
    }
    free(table->items);
}

int main(void) {
    setlocale(LC_CTYPE, "RU");
    HashTable table;
    init_table(&table);

    char operation[2];
    char key[256];

    while (scanf("%1s %255s", operation, key) == 2) {
        switch (operation[0]) {
        case 'a':
            insert_key(&table, key);
            break;
        case 'r':
            delete_key(&table, key);
            break;
        case 'f':
            printf(find_key(&table, key) ? "yes\n" : "no\n");
            break;
        default:
            break;
        }
    }

    free_table(&table);
    return 0;
}
