#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "lib.h"

Node* createNode(const char *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node *root, const char *data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (strcmp(data, root->data) < 0) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

void printInOrder(Node *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%s", root->data);
        printInOrder(root->right);
    }
}

void saveToFile(Node *root, FILE *file) {
    if (root != NULL) {
        fprintf(file, "%s", root->data);
        saveToFile(root->left, file);
        saveToFile(root->right, file);
    }
}

Node* loadFromFile(FILE *file) {
    char buffer[256];
    Node *root = NULL;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; // Удаляем символ новой строки
        root = insert(root, buffer);
    }
    return root;
}

void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->data);
        free(root);
    }
}

