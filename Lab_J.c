#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define TABLE_SIZE 995009  // Размер хеш-таблицы (большое просто число)

typedef struct {
    char* key;
    int is_deleted;  // Флаг удаленного элемента (1 - удален, 0 - нет)
    int is_occupied; // Флаг занятой ячейки (1 - занята, 0 - свободна)
} HashEntry;

HashEntry hash_table[TABLE_SIZE];

// Хеш-функция для строк (djb2)
unsigned long hash_function(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

// Инициализация хеш-таблицы
void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i].key = NULL;
        hash_table[i].is_deleted = 0;
        hash_table[i].is_occupied = 0;
    }
}

// Вставка элемента в хеш-таблицу
void insert(const char* key) {
    unsigned long index = hash_function(key);
    int original_index = index;

    // Проверяем, есть ли уже такой ключ в таблице
    while (hash_table[index].is_occupied) {
        if (hash_table[index].key != NULL && strcmp(hash_table[index].key, key) == 0 && !hash_table[index].is_deleted) {
            return;  // Ключ уже существует
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == original_index) {
            return;  // Таблица переполнена
        }
    }

    // Находим место для вставки (свободная ячейка или удаленная)
    int insert_index = -1;
    index = original_index;
    while (hash_table[index].is_occupied) {
        if (hash_table[index].is_deleted) {
            insert_index = index;
            break;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == original_index) {
            return;  // Таблица переполнена
        }
    }

    if (insert_index == -1) {
        insert_index = index;
    }

    // Вставляем ключ
    hash_table[insert_index].key = strdup(key);
    hash_table[insert_index].is_occupied = 1;
    hash_table[insert_index].is_deleted = 0;
}

// Удаление элемента из хеш-таблицы
void remove_key(const char* key) {
    unsigned long index = hash_function(key);
    int original_index = index;

    while (hash_table[index].is_occupied) {
        if (hash_table[index].key != NULL && strcmp(hash_table[index].key, key) == 0 && !hash_table[index].is_deleted) {
            free(hash_table[index].key);
            hash_table[index].key = NULL;
            hash_table[index].is_deleted = 1;
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == original_index) {
            return;  // Ключ не найден
        }
    }
}

// Поиск элемента в хеш-таблице
void find(const char* key) {
    unsigned long index = hash_function(key);
    int original_index = index;

    while (hash_table[index].is_occupied) {
        if (hash_table[index].key != NULL && strcmp(hash_table[index].key, key) == 0 && !hash_table[index].is_deleted) {
            printf("yes\n");
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == original_index) {
            printf("no\n");
            return;
        }
    }

    printf("no\n");
}

// Освобождение памяти
void cleanup() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i].key != NULL) {
            free(hash_table[i].key);
        }
    }
}

int main() {
    init_hash_table();
    char operation;
    char key[1024];  // Буфер для ключа

    while (scanf(" %c %s", &operation, key) == 2) {
        switch (operation) {
        case 'a':
            insert(key);
            break;
        case 'r':
            remove_key(key);
            break;
        case 'f':
            find(key);
            break;
        default:
            break;
        }
    }

    cleanup();
    return 0;
}