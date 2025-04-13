#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define MAX_LEN 256

typedef struct node {
    char* key;
    struct node* next;
} node_t;

// Хеш-функция
unsigned int hash(const char* str);

// Добавление ключа в таблицу
void addNode(node_t** table, const char* key);

// Удаление ключа из таблицы
void deleteNode(node_t** table, const char* key);

// Поиск ключа в таблице
int findNode(node_t** table, const char* key);

#endif // HASH_TABLE_H
