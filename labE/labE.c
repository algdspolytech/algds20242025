#include "labE.h"

// Функция для создания нового узла
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->leafCount = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для подсчета количества листьев в поддереве
int fillAndCountLeaves(Node* node) {
    if (node == NULL) return 0;

    // Если лист
    if (node->left == NULL && node->right == NULL) {
        node->leafCount = 0;
        return 1;
    }

    int leftLeaves = fillAndCountLeaves(node->left);
    int rightLeaves = fillAndCountLeaves(node->right);

    node->leafCount = leftLeaves + rightLeaves;
    return node->leafCount;
}

// Функция для печати дерева с использованием матрицы
void fillMatrix(Node* node, int** matrix, int row, int col, int depth, int maxDepth) {
    if (node == NULL) {
        return;
    }
    matrix[row][col] = node->leafCount;

    int offset = (1 << (maxDepth - depth - 1)); // Смещение для потомков

    fillMatrix(node->left, matrix, row + 1, col - offset, depth + 1, maxDepth);
    fillMatrix(node->right, matrix, row + 1, col + offset, depth + 1, maxDepth);
}

// Основная функция печати дерева
void printTree(Node* root, int maxDepth) {
    int width = (1 << (maxDepth + 1)) - 1;  // Ширина матрицы
    int height = maxDepth + 1;             // Высота матрицы

    // Создание динамической матрицы
    int** matrix = (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) {
        matrix[i] = (int*)malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) {
            matrix[i][j] = -1;  // Заполняем матрицу значением по умолчанию
        }
    }

    // Заполнение матрицы значениями из дерева
    fillMatrix(root, matrix, 0, (width - 1) / 2, 0, maxDepth);

    // Печать матрицы
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] != -1) {
                printf("%d ", matrix[i][j]);
            }
            else {
                printf("  ");
            }
        }
        printf("\n");
    }

    // Освобождение памяти
    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
