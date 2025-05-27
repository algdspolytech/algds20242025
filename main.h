#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

// Структура узла декартова дерева
typedef struct Node {
    int x; // ключ
    int c; // приоритет
    int max_c; // максимальное значение c в поддереве
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(int x, int c);
void updateMax(Node* node);
Node* merge(Node* left, Node* right);
void split(Node* root, int x, Node** left, Node** right);
Node* insert(Node* root, int x, int c);
int queryMax(Node* root, int x, int y);
void freeTree(Node* root);

#endif 