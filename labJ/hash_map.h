#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура узла связного списка
struct Node {
    char *key;          // Ключ - ASCIIZ строка
    struct Node *next;  // Указатель на следующий узел
};

// Структура хеш-таблицы
struct HashTable {
    struct Node **table; // Массив указателей на узлы
    int size;            // Размер таблицы
};


#endif //HASH_MAP_H
