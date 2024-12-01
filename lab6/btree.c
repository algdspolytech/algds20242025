#include <stdlib.h>
#include "btree.h"

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->value = value;
        newNode->count = 1;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

void updateCount(Node* node) {
    if (node) {
        node->count = 1;
        if (node->left) node->count += node->left->count;
        if (node->right) node->count += node->right->count;
    }
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    Node* current = root;
    Node* parent = NULL;
    Node** path[100];  // стек для хранения пути
    int pathLen = 0;

    // Поиск места для вставки
    while (current != NULL) {
        path[pathLen++] = &current;
        
        if (value == current->value) {
            return root;  // значение уже существует
        }

        parent = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Создание нового узла
    Node* newNode = createNode(value);
    if (!newNode) return root;

    // Определение, куда вставлять новый узел
    int leftCount = (parent->left) ? parent->left->count : 0;
    int rightCount = (parent->right) ? parent->right->count : 0;

    if (leftCount <= rightCount) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Обновление счетчиков для всех узлов по пути
    while (--pathLen >= 0) {
        updateCount(*path[pathLen]);
    }

    return root;
}

Node* findMin(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* delete(Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    Node* current = root;
    Node* parent = NULL;
    Node** path[100];  // стек для хранения пути
    int pathLen = 0;
    int isLeftChild = 0;

    // Поиск узла для удаления
    while (current != NULL && current->value != value) {
        path[pathLen++] = &current;
        parent = current;
        if (value < current->value) {
            current = current->left;
            isLeftChild = 1;
        } else {
            current = current->right;
            isLeftChild = 0;
        }
    }

    if (current == NULL) {
        return root;  // значение не найдено
    }

    // Случай 1: узел без потомков
    if (current->left == NULL && current->right == NULL) {
        if (current == root) {
            free(root);
            return NULL;
        }
        if (isLeftChild) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
    // Случай 2: узел с одним потомком
    else if (current->left == NULL) {
        Node* temp = current->right;
        if (current == root) {
            free(root);
            return temp;
        }
        if (isLeftChild) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        free(current);
    }
    else if (current->right == NULL) {
        Node* temp = current->left;
        if (current == root) {
            free(root);
            return temp;
        }
        if (isLeftChild) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        free(current);
    }
    // Случай 3: узел с двумя потомками
    else {
        Node* successor = findMin(current->right);
        int successorValue = successor->value;
        delete(root, successor->value);
        current->value = successorValue;
        return root;
    }

    // Обновление счетчиков для всех узлов по пути
    while (--pathLen >= 0) {
        updateCount(*path[pathLen]);
    }

    return root;
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
