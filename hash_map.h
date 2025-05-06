#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_CAPACITY 1000003
#define KEY_MAX_LEN 255

typedef struct BucketEntry {
    char* data;
    struct BucketEntry* chain;
} BucketEntry;

typedef struct {
    BucketEntry** slots;
    int capacity;
} StringHashMap;

// Хеш-функция для строк
unsigned int string_hash(const char* str);

// Создание хеш-таблицы
void map_init(StringHashMap* map);

// Вставка строки в таблицу
void map_put(StringHashMap* map, const char* key);

// Поиск строки в таблице
int map_contains(StringHashMap* map, const char* key) ;

// Удаление строки из таблицы
void map_delete(StringHashMap* map, const char* key);

// Освобождение памяти таблицы
void map_cleanup(StringHashMap* map);

#endif //HASH_MAP_H
