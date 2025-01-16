#pragma once
#ifndef BST_H
#define BST_H

// Структура узла дерева
typedef struct Node {
    int key;              // Значение ключа
    int size;             // Размер поддерева, включая этот узел
    struct Node* left;    // Левый потомок
    struct Node* right;   // Правый потомок
} Node;

// Прототипы функций
Node* insert(Node* root, int key);
Node* find(Node* root, int key);
Node* find_kth_predecessor(Node* root, int key, int k);
void free_tree(Node* root);

#endif // BST_H