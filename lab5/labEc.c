#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Для поддержки русского языка
#include "tree.h"
// Функция для создания нового узла
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для вычисления высоты поддерева
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Функция для записи разностей высот в каждом узле
void updateHeightDifference(struct Node* node) {
    if (node == NULL)
        return;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    // Записываем разность высот в текущий узел
    node->data = leftHeight - rightHeight;

    // Рекурсивно применяем функцию к левому и правому поддеревьям
    updateHeightDifference(node->left);
    updateHeightDifference(node->right);
}

// Функция для симметричного обхода дерева и печати значений в строку
void printTreeInOrder(struct Node* node) {
    if (node == NULL)
        return;
    printTreeInOrder(node->left);     // Левое поддерево
    printf("%d ", node->data);        // Текущий узел
    printTreeInOrder(node->right);    // Правое поддерево
}
