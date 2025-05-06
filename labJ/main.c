#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1048576  // Размер хеш-таблицы (желательно простое число)

typedef struct {
    char* key;
    int is_deleted;  // Флаг удаленного элемента (для ленивого удаления)
    int is_occupied;  // Флаг занятой ячейки
} HashItem;

typedef struct {
    HashItem* items;
    int size;
} HashTable;

// Первая хеш-функция (простое хеширование)
unsigned int hash1(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash;
}

// Вторая хеш-функция (должна возвращать нечетное число)
unsigned int hash2(const char* key) {
    unsigned int hash = 5381;
    while (*key) {
        hash = (hash * 33) ^ *key++;
    }
    // Убедимся, что hash2 нечетный и не равен 0
    return hash | 1;
}

// Инициализация хеш-таблицы
void initHashTable(HashTable* table) {
    table->size = TABLE_SIZE;
    table->items = (HashItem*)calloc(TABLE_SIZE, sizeof(HashItem));
    if (!table->items) {
        perror("Failed to allocate memory for hash table");
        exit(EXIT_FAILURE);
    }
}

// Вставка элемента в хеш-таблицу
void insert(HashTable* table, const char* key) {
    // Проверим, не существует ли уже этот ключ
    if (search(table, key)) {
        return;
    }

    unsigned int h1 = hash1(key) % table->size;
    unsigned int h2 = hash2(key) % table->size;
    unsigned int index = h1;
    int i = 1;

    while (table->items[index].is_occupied && !table->items[index].is_deleted) {
        if (strcmp(table->items[index].key, key) == 0) {
            return;  // Ключ уже существует
        }
        index = (h1 + i * h2) % table->size;
        i++;
        if (i == table->size) {  // Таблица заполнена
            return;
        }
    }

    // Нашли свободное место или удаленную ячейку
    if (table->items[index].is_deleted) {
        free(table->items[index].key);  // Освобождаем память старой строки
    }

    table->items[index].key = strdup(key);
    table->items[index].is_occupied = 1;
    table->items[index].is_deleted = 0;
}

// Поиск элемента в хеш-таблице
int search(HashTable* table, const char* key) {
    unsigned int h1 = hash1(key) % table->size;
    unsigned int h2 = hash2(key) % table->size;
    unsigned int index = h1;
    int i = 1;

    while (table->items[index].is_occupied) {
        if (!table->items[index].is_deleted && strcmp(table->items[index].key, key) == 0) {
            return 1;  // Нашли
        }
        index = (h1 + i * h2) % table->size;
        i++;
        if (i == table->size) {  // Прошли всю таблицу
            break;
        }
    }

    return 0;  // Не нашли
}

// Удаление элемента из хеш-таблицы
void remove_item(HashTable* table, const char* key) {
    unsigned int h1 = hash1(key) % table->size;
    unsigned int h2 = hash2(key) % table->size;
    unsigned int index = h1;
    int i = 1;

    while (table->items[index].is_occupied) {
        if (!table->items[index].is_deleted && strcmp(table->items[index].key, key) == 0) {
            // Нашли элемент для удаления
            free(table->items[index].key);
            table->items[index].key = NULL;
            table->items[index].is_deleted = 1;
            return;
        }
        index = (h1 + i * h2) % table->size;
        i++;
        if (i == table->size) {  // Прошли всю таблицу
            break;
        }
    }
}

// Освобождение памяти хеш-таблицы
void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        if (table->items[i].is_occupied && !table->items[i].is_deleted) {
            free(table->items[i].key);
        }
    }
    free(table->items);
}

int main() {
    HashTable table;
    initHashTable(&table);

    char operation[2];
    char key[256];  // Буфер для ключа (ASCII-Z строки)

    while (scanf("%1s %255s", operation, key) == 2) {
        switch (operation[0]) {
        case 'a':  // Вставка
            insert(&table, key);
            break;
        case 'r':  // Удаление
            remove_item(&table, key);
            break;
        case 'f':  // Поиск
            printf("%s\n", search(&table, key) ? "yes" : "no");
            break;
        default:
            fprintf(stderr, "Unknown operation: %c\n", operation[0]);
            break;
        }
    }

    freeHashTable(&table);
    return 0;
}