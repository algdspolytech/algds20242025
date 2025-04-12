#ifndef LABE_H
#define LABE_H

#include <stdio.h>
#include <stdlib.h>

// Структура узла бинарного дерева
typedef struct Node {
    int leafCount;          // Количество листьев в поддереве
    struct Node* left;      // Левый ребенок
    struct Node* right;     // Правый ребенок
} Node;

// Функция для создания нового узла
Node* createNode();

int fillAndCountLeaves(Node* node);

void fillMatrix(Node* node, int** matrix, int row, int col, int depth, int maxDepth);

void printTree(Node* root, int maxDepth);

#endif