#pragma once
#include <stdio.h>
#include<stdlib.h>

// Структура для узла двусвязного списка
typedef struct Node {
    char* data;
    struct Node* next;
    struct Node* prev;
} Node;

// Функция для создания нового узла
Node* createNode(const char* data);

// Функция для разделения списка на две половины
void split(Node* head, Node** firstHalf, Node** secondHalf);

// Функция для слияния двух отсортированных списков
Node* merge(Node* first, Node* second);

// Основная функция сортировки по слиянию
Node* mergeSort(Node* head);

// Функция для вывода списка
void printList(Node* node);

// Освобождение памяти
void freeList(Node* node);

