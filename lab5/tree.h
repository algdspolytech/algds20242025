#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

// Структура узла бинарного дерева
typedef struct Node {
    int value;
    int balance;
    struct Node* left;
    struct Node* right;
} Node;

// Функции для работы с деревом
Node* createNode(int value);
Node* insert(Node* root, int value);
int getHeight(Node* node);
int updateBalances(Node* root);
void printTree(Node* root, int level);
void freeTree(Node* root);

#endif