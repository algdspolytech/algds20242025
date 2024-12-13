#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 
#include "tree.h"
// ������� ��� �������� ������ ����
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ������� ��� ���������� ������ ���������
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// ������� ��� ������ ��������� ����� � ������ ����
void updateHeightDifference(struct Node* node) {
    if (node == NULL)
        return;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    // ���������� �������� ����� � ������� ����
    node->data = leftHeight - rightHeight;

    // ���������� ��������� ������� � ������ � ������� �����������
    updateHeightDifference(node->left);
    updateHeightDifference(node->right);
}

// ������� ��� ������������� ������ ������ � ������ �������� � ������
void printTreeInOrder(struct Node* node) {
    if (node == NULL)
        return;
    printTreeInOrder(node->left);     // ����� ���������
    printf("%d ", node->data);        // ������� ����
    printTreeInOrder(node->right);    // ������ ���������
}