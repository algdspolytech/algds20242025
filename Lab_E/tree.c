#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


// Функция для создания нового узла
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для печати дерева в обычном виде
void printTree(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("%d\n", root->data);
    printTree(root->left, level + 1);
}

// Функция для печати дерева в формате: узел (левое поддерево) (правое поддерево)
void printTreeFormatted(struct Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d", root->data);
    if (root->left != NULL || root->right != NULL) {
        printf(" (");
        printTreeFormatted(root->left);
        printf(") (");
        printTreeFormatted(root->right);
        printf(")");
    }
}

// Функция для освобождения памяти, занятой деревом
void freeTree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);   // Освобождение левого поддерева
    freeTree(root->right);  // Освобождение правого поддерева
    free(root);             // Освобождение текущего узла
}


