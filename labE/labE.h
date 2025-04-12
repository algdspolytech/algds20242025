#ifndef LABE_H
#define LABE_H

#include <stdio.h>
#include <stdlib.h>

// ��������� ���� ��������� ������
typedef struct Node {
    int leafCount;          // ���������� ������� � ���������
    struct Node* left;      // ����� �������
    struct Node* right;     // ������ �������
} Node;

// ������� ��� �������� ������ ����
Node* createNode();

int fillAndCountLeaves(Node* node);

void fillMatrix(Node* node, int** matrix, int row, int col, int depth, int maxDepth);

void printTree(Node* root, int maxDepth);

#endif