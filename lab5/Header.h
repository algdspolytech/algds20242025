#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Структура узла бинарного дерева
typedef struct Node {
    int value;          // значение в узле
    int minLeafHeight;  // минимальная высота листа в поддеревье
    struct Node* left;  // указатель на левое поддеревье
    struct Node* right; // указатель на правое поддеревье
} Node;

// Функция для создания нового узла
Node* createNode(int value);

// Функция для вычисления минимальной высоты листа в поддеревье
int minLeafHeight(Node* root);

// Функция для обновления минимальной высоты листьев в поддеревьях
void updateMinLeafHeights(Node* root);

// Функция для печати дерева в файл
void printTreeToFile(Node* root, int space, FILE* file);

