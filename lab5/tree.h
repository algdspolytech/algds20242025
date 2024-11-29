#ifndef TREE_H
#define TREE_H

// Определение структуры узла бинарного дерева
struct Node {
    int data;          // Данные узла
    struct Node* left; // Левый потомок
    struct Node* right; // Правый потомок
};

// Функция для создания нового узла
struct Node* createNode(int data);

// Функция для вычисления высоты поддерева
int height(struct Node* node);

// Функция для записи разностей высот в каждом узле
void updateHeightDifference(struct Node* node);

// Функция для симметричного обхода дерева и печати значений в строку
void printTreeInOrder(struct Node* node);

#endif // TREE_H
