#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Размер хеш-таблицы
#define TABLE_SIZE 1000033

// Структура для хранения элемента хеш-таблицы
typedef struct {
    char* key;    // Ключ (строка)
    int is_occupied;
    int is_deleted;
} HashItem;


typedef struct {
    HashItem* nodes;
    int size;
} HashTable;

int findNode(HashTable* table, const char* key);

void initTable(HashTable* table) 
{
    table->size = TABLE_SIZE;
    table->nodes = (HashItem*)calloc(TABLE_SIZE, sizeof(HashItem));
}

// Хеш-функция 1: для вычисления начального индекса
unsigned int hash1(const char* str) 
{
    unsigned int hashValue = 0;
    while (*str) 
    {
        hashValue = (hashValue << 5) + *str++; // (hashValue * 31) + символ
    }
    return hashValue % TABLE_SIZE;
}

// Хеш-функция 2: для вычисления шага при коллизии
unsigned int hash2(const char* str) 
{
    unsigned int hashValue = 0;
    while (*str) 
    {
        hashValue = (hashValue << 5) + *str++; // (hashValue * 31) + символ
    }
    return 1 + (hashValue % (TABLE_SIZE - 1)); // Шаг не может быть 0
}

// Функция для копирования строки в память
char* copyString(const char* str) 
{
    size_t len = strlen(str) + 1;  // +1 для учёта завершающего нуля
    char* new_str = (char*)malloc(len);  // Выделяем память
    if (new_str) 
    {
        strcpy(new_str, str);  // Копируем строку в выделенную память
    }
    return new_str;
}

void addNode(HashTable* table, const char* key) 
{
    if (findNode(table, key)) return;
    unsigned int index = hash1(key);  // Находим индекс с помощью первой хеш-функции
    unsigned int step = hash2(key);   // Вычисляем шаг для разрешения коллизий

    for (unsigned int i = 0; i < TABLE_SIZE; i++) 
    {
        // Если ячейка свободна или элемент удален, вставляем новый
        if (!table->nodes[index].is_occupied || table->nodes[index].is_deleted) 
        {
            if (table->nodes[index].key) free(table->nodes[index].key);
            table->nodes[index].key = copyString(key);  // Сохраняем строку в таблице
            table->nodes[index].is_occupied = 1;    // Отмечаем, что ячейка занята
            table->nodes[index].is_deleted = 0;     // Элемент не удален
            return;
        }
        // Ищем следующий индекс для коллизий
        index = (index + step) % TABLE_SIZE;
    }
    fprintf(stderr, "Hash table is full\n");
}

int findNode(HashTable* table, const char* key) 
{
    unsigned int index = hash1(key);  // Находим индекс с помощью первой хеш-функции
    unsigned int step = hash2(key);   // Вычисляем шаг для разрешения коллизий

    for (unsigned int i = 0; i < TABLE_SIZE; i++) 
    {
        if (!table->nodes[index].is_occupied) 
        {
            return 0;
        }
        if (!table->nodes[index].is_deleted && strcmp(table->nodes[index].key, key) == 0) 
        {
            return 1;  // Элемент найден
        }
        // Ищем следующий индекс для коллизий
        index = (index + step) % TABLE_SIZE;
    }
    return 0;  // Элемент не найден
}

void deleteNode(HashTable* table, const char* key) 
{
    unsigned int index = hash1(key);  // Находим индекс с помощью первой хеш-функции
    unsigned int step = hash2(key);   // Вычисляем шаг для разрешения коллизий

    for (unsigned int i = 0; i < TABLE_SIZE; i++) 
    {
        if (!table->nodes[index].is_occupied)
        {
            return;
        }
        if (!table->nodes[index].is_deleted && strcmp(table->nodes[index].key, key) == 0) 
        {
            free(table->nodes[index].key);
            table->nodes[index].is_deleted = 1;  // Помечаем элемент как удалённый
            table->nodes[index].key = NULL;      // Убираем ссылку на строку
            return;
        }
        // Ищем следующий индекс для коллизий
        index = (index + step) % TABLE_SIZE;
    }
}

void freeHashTable(HashTable* table) 
{
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        if (table->nodes[i].key) free(table->nodes[i].key);
    }
    free(table->nodes);
}

// Основная функция
int main(void) 
{
    HashTable table;
    initTable(&table);

    char ch[2];  // Для хранения строк
    char key[133];
    while (scanf("%1s %132s", ch, key) == 2) 
    {
        switch (ch[0]) {
        case 'a': // Добавление строки
            addNode(&table, key);
            break;
        case 'r': // Удаление строки
            deleteNode(&table, key);
            break;
        case 'f': // Поиск строки
            printf(findNode(&table, key) ? "yes\n" : "no\n");
            break;
        default:
            break;
        }
    }
    freeHashTable(&table);
    return 0;
}

