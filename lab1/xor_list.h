#pragma once
#ifndef XOR_LIST_H
#define XOR_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Структура узла XOR-связного списка
typedef struct Node {
    char* data;           // ASCIIZ строка
    struct Node* np;      // XOR указатель: prev ^ next
} Node;

// Функция XOR двух указателей
Node* XOR(Node* a, Node* b);

// Добавить элемент в конец списка
void add(Node** head, char* str);

// Найти элемент по ключу
Node* find(Node* head, char* key);

// Удалить элемент по ключу
void deleteByKey(Node** head, char* key);

// Удалить элемент по адресу
void deleteByAddress(Node** head, Node* node);

// Итерация и вывод всех элементов
void printList(Node* head);

// Освобождение памяти всего списка
void freeList(Node* head);

#endif // XOR_LIST_H