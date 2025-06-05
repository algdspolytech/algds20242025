#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 1000003 // Начальный размер таблицы (большое простое число)
#define LOAD_FACTOR 0.75    // Коэффициент загрузки для rehash

typedef struct {
    int key;              // Ключ
    char state;           // Состояние ячейки: 'E' (пусто), 'U' (используется), 'D' (удалено)
} HashEntry;

typedef struct {
    HashEntry *entries;   // Массив записей
    int capacity;         // Текущая ёмкость
    int size;             // Кол-во реально хранящихся элементов
} HashTable;

// Создание хеш-таблицы
HashTable* createTable(int cap) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) {
        fprintf(stderr, "Memory alloc error\n");
        exit(EXIT_FAILURE);
    }
    table->capacity = cap;
    table->size = 0;
    table->entries = (HashEntry*)malloc(sizeof(HashEntry) * cap);
    if (!table->entries) {
        fprintf(stderr, "Memory alloc error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < cap; i++) {
        table->entries[i].key = 0;
        table->entries[i].state = 'E';
    }
    return table;
}

void rehash(HashTable *table);
bool insertKey(HashTable *table, int key);


// Освобождение памяти
void freeTable(HashTable *table) {
    if (!table) return;
    free(table->entries);
    free(table);
}

// Хеш-функция для целых чисел
unsigned long hashFunction(unsigned long x) {
    return x * 2654435789ul; // ЗОЛОТОЕ ЧИСЛО
}

// Перехеширование таблицы
void rehash(HashTable *table) {
    int oldCap = table->capacity;
    int newCap = oldCap * 2 + 1;

    HashEntry *oldEntries = table->entries;

    table->capacity = newCap;
    table->size = 0;
    table->entries = (HashEntry*)malloc(sizeof(HashEntry) * newCap);
    if (!table->entries) {
        fprintf(stderr, "Memory alloc error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < newCap; i++) {
        table->entries[i].key = 0;
        table->entries[i].state = 'E';
    }

    for (int i = 0; i < oldCap; i++) {
        if (oldEntries[i].state == 'U') {
            insertKey(table, oldEntries[i].key);
        }
    }

    free(oldEntries);
}

// Вставка ключа
bool insertKey(HashTable *table, int key) {
    if ((double)(table->size + 1) / table->capacity > LOAD_FACTOR) {
        rehash(table);
    }

    unsigned long h = hashFunction((unsigned long)key);
    int idx = (int)(h % table->capacity);

    int firstDelPos = -1;

    for (int probe = 0; probe < table->capacity; probe++) {
        int pos = (idx + probe) % table->capacity;
        if (table->entries[pos].state == 'E') {
            int insertPos = (firstDelPos != -1) ? firstDelPos : pos;
            table->entries[insertPos].key = key;
            table->entries[insertPos].state = 'U';
            table->size++;
            return true;
        } else if (table->entries[pos].state == 'D') {
            if (firstDelPos == -1) {
                firstDelPos = pos;
            }
        } else if (table->entries[pos].state == 'U' && table->entries[pos].key == key) {
            return false;
        }
    }
    return false;
}

// Поиск ключа
bool searchKey(HashTable *table, int key) {
    unsigned long h = hashFunction((unsigned long)key);
    int idx = (int)(h % table->capacity);

    for (int probe = 0; probe < table->capacity; probe++) {
        int pos = (idx + probe) % table->capacity;
        if (table->entries[pos].state == 'E') {
            return false;
        }
        if (table->entries[pos].state == 'U' && table->entries[pos].key == key) {
            return true;
        }
    }
    return false;
}

// Удаление ключа
bool deleteKey(HashTable *table, int key) {
    unsigned long h = hashFunction((unsigned long)key);
    int idx = (int)(h % table->capacity);

    for (int probe = 0; probe < table->capacity; probe++) {
        int pos = (idx + probe) % table->capacity;
        if (table->entries[pos].state == 'E') {
            return false;
        }
        if (table->entries[pos].state == 'U' && table->entries[pos].key == key) {
            table->entries[pos].state = 'D';
            table->size--;
            return true;
        }
    }
    return false;
}

// Главная функция
int main(void) {
    HashTable *table = createTable(TABLE_SIZE);

    char op;
    int key;
    while (scanf(" %c %d", &op, &key) == 2) {
        switch(op) {
            case 'a':
                insertKey(table, key);
                break;
            case 'r':
                deleteKey(table, key);
                break;
            case 'f':
                printf("%s\n", searchKey(table, key) ? "yes" : "no");
                break;
            default:
                break;
        }
    }

    freeTable(table);
    return 0;
}