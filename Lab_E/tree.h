#ifndef TREE_H
#define TREE_H

// Определение структуры узла дерева
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Функция для создания нового узла
struct Node* createNode(int data);

// Функция для печати дерева в обычном виде
void printTree(struct Node* root, int level);

// Функция для печати дерева в формате: узел (левое поддерево) (правое поддерево)
void printTreeFormatted(struct Node* root);

// Функция для освобождения памяти, занятой деревом
void freeTree(struct Node* root);

#endif // TREE_H



