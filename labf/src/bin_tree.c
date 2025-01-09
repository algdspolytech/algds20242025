#include "../include/bin_tree.h"
#include <stdio.h>
#include <stdlib.h>

Node* createNode(int value, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}

// Функция для обновления счетчика узлов в поддереве
void updateCount(Node* node) {
    while (node) {
        int leftCount = node->left ? node->left->count : 0;
        int rightCount = node->right ? node->right->count : 0;
        node->count = leftCount + rightCount + 1;
        node = node->parent;
    }
}

// Процедура добавления узла в дерево
void insert(Node** root, int value) {
    if (*root == NULL) {
        *root = createNode(value, NULL);
        return;
    }

    Node* current = *root;
    while (1) {
        int leftCount = current->left ? current->left->count : 0;
        int rightCount = current->right ? current->right->count : 0;

        if (leftCount <= rightCount) {
            // Идем в левое поддерево
            if (current->left) {
                current = current->left;
            } else {
                current->left = createNode(value, current);
                updateCount(current);
                break;
            }
        } else {
            // Идем в правое поддерево
            if (current->right) {
                current = current->right;
            } else {
                current->right = createNode(value, current);
                updateCount(current);
                break;
            }
        }
    }
}

// Поиск узла с минимальным значением в поддереве
Node* findMin(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

void delete(Node** root, int value) {
    Node* current = *root;
    Node* parent = NULL;

    // Поиск узла для удаления
    while (current && current->value != value) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (!current) {
        printf("Значение %d не найдено в дереве.\n", value);
        return;
    }

    // Узел найден
    if (!current->left && !current->right) {
        // Удаление листа
        if (current == *root) {
            *root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    } else if (current->left && current->right) {
        // Удаление узла с двумя потомками
        Node* successor = findMin(current->right);
        int successorValue = successor->value; // Сохраняем значение
        delete(root, successor->value); // Удаляем минимальный узел
        current->value = successorValue; // Устанавливаем значение узла
    } else {
        // Удаление узла с одним поддеревом
        Node* child = current->left ? current->left : current->right;
        if (current == *root) {
            *root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        child->parent = parent;
        free(current);
    }

    // Обновляем счетчики узлов
    updateCount(parent);
}

// Обход дерева (для отладки)
void inorderTraversal(Node* node) {
    if (!node) return;
    inorderTraversal(node->left);
    printf("Value: %d, Count: %d\n", node->value, node->count);
    inorderTraversal(node->right);
}