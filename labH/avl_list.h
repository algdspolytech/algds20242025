#pragma once
#ifndef AVL_LIST_H
#define AVL_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Структура узла AVL-дерева
typedef struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
    int size;
} Node;

// Функции для работы с AVL-деревом
Node* createNode(int key);
int height(Node* n);
int size(Node* n);
int getBalance(Node* n);
void updateNode(Node* node);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
Node* insert(Node* node, int key, int position);
Node* search(Node* root, int key);
Node* findKth(Node* root, int k);
void inorder(Node* root);
Node* mergeTrees(Node* root1, Node* root2);

#endif // AVL_LIST_H
