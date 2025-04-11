#include "Header.h"

char* table[TABLE_SIZE];

// Простая хеш-функция
unsigned int hash(const char* str) {
    unsigned int h = 0;
    while (*str) {
        h = h * 31 + *str++;
    }
    return h % TABLE_SIZE;
}

// Безопасная реализация strdup
char* my_strdup(const char* str) {
    char* copy = malloc(strlen(str) + 1);
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

// Вставка строки
int insert(const char* str) {
    unsigned int idx = hash(str);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (idx + i) % TABLE_SIZE;
        if (table[probe] == NULL) {
            // Если на позиции пусто, вставляем строку
            table[probe] = my_strdup(str);
            return 1;
        }
        if (strcmp(table[probe], str) == 0) {
            // Если строка уже есть в таблице, возвращаем 0
            return 0;
        }
    }
    return 0; // Таблица переполнена
}


// Поиск строки
int search(const char* str) {
    unsigned int idx = hash(str);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (idx + i) % TABLE_SIZE;
        if (table[probe] == NULL)
            return 0;
        if (strcmp(table[probe], str) == 0)
            return 1;
    }
    return 0;
}

// Очистка памяти
void free_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            free(table[i]);
        }
    }
}
