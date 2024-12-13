//
//  tree.c
//  LAB_F
//
//  Created by Фёдор Филь on 11.12.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

// Функция для создания нового узла
Node* createNode(int low, int high) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->low = low;
    node->high = high;
    node->max_high = high;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для вставки нового интервала в дерево
Node* insert(Node* root, int low, int high) {
    if (root == NULL) {
        return createNode(low, high);
    }

    if (low < root->low) {
        root->left = insert(root->left, low, high);
    } else {
        root->right = insert(root->right, low, high);
    }

    // Обновляем max_high
    if (root->max_high < high) {
        root->max_high = high;
    }

    return root;
}

// Функция для нахождения минимального узла в правом поддереве
Node* findMin(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Функция для удаления интервала из дерева
Node* deleteNode(Node* root, int low) {
    if (root == NULL) {
        return NULL;
    }

    if (low < root->low) {
        root->left = deleteNode(root->left, low);
    } else if (low > root->low) {
        root->right = deleteNode(root->right, low);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            Node* temp = (root->left != NULL) ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Node* minNode = findMin(root->right);
            root->low = minNode->low;
            root->high = minNode->high;
            root->right = deleteNode(root->right, minNode->low);
        }
    }

    // Пересчёт max_high после удаления
    if (root->left != NULL) {
        root->max_high = (root->high > root->left->max_high) ? root->high : root->left->max_high;
    }
    if (root->right != NULL) {
        root->max_high = (root->max_high > root->right->max_high) ? root->max_high : root->right->max_high;
    }

    return root;
}

void findOverlappingIntervals(Node* root, int intervalLow, int intervalHigh, Node** result, int* count) {
    if (root == NULL) {
        return;
    }

    // Если текущий узел может иметь пересекающийся интервал
    if (root->low <= intervalHigh && root->high >= intervalLow) {
        result[*count] = root;
        (*count)++;
    }

    // Проверка левого поддерева
    if (root->left != NULL && root->left->max_high >= intervalLow) {
        findOverlappingIntervals(root->left, intervalLow, intervalHigh, result, count);
    }

    // Проверка правого поддерева
    if (root->right != NULL && root->right->low <= intervalHigh) {
        findOverlappingIntervals(root->right, intervalLow, intervalHigh, result, count);
    }
}
