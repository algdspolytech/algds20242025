#include "labE.h"

// ������� ��� �������� ������ ����
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->leafCount = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ������� ��� �������� ���������� ������� � ���������
int fillAndCountLeaves(Node* node) {
    if (node == NULL) return 0;

    // ���� ����
    if (node->left == NULL && node->right == NULL) {
        node->leafCount = 0;
        return 1;
    }

    int leftLeaves = fillAndCountLeaves(node->left);
    int rightLeaves = fillAndCountLeaves(node->right);

    node->leafCount = leftLeaves + rightLeaves;
    return node->leafCount;
}

// ������� ��� ������ ������ � �������������� �������
void fillMatrix(Node* node, int** matrix, int row, int col, int depth, int maxDepth) {
    if (node == NULL) {
        return;
    }
    matrix[row][col] = node->leafCount;

    int offset = (1 << (maxDepth - depth - 1)); // �������� ��� ��������

    fillMatrix(node->left, matrix, row + 1, col - offset, depth + 1, maxDepth);
    fillMatrix(node->right, matrix, row + 1, col + offset, depth + 1, maxDepth);
}

// �������� ������� ������ ������
void printTree(Node* root, int maxDepth) {
    int width = (1 << (maxDepth + 1)) - 1;  // ������ �������
    int height = maxDepth + 1;             // ������ �������

    // �������� ������������ �������
    int** matrix = (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) {
        matrix[i] = (int*)malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) {
            matrix[i][j] = -1;  // ��������� ������� ��������� �� ���������
        }
    }

    // ���������� ������� ���������� �� ������
    fillMatrix(root, matrix, 0, (width - 1) / 2, 0, maxDepth);

    // ������ �������
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

    // ������������ ������
    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
