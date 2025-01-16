#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include "tree.h"

// �������� ������ ����
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "������ ��������� ������!\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->width = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ������� �������� � �������� ������
void insertNode(Node** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
    }
    else if (value < (*root)->value) {
        insertNode(&((*root)->left), value);
    }
    else {
        insertNode(&((*root)->right), value);
    }
}

// ����������� ���������� ������ ���������
int calculateWidth(Node* root) {
    if (root == NULL) return 0;

    int leftWidth = calculateWidth(root->left);
    int rightWidth = calculateWidth(root->right);

    // ��������� ������ �������� ���� ��� ������������ ������ �������� ����� ���� ������� ����
    root->width = leftWidth + rightWidth + snprintf(NULL, 0, "%d", root->value);
    return root->width;
}

// ������ ������ (� ��������� ��� ������������)
void printTree(Node* root, int level) {
    if (root == NULL) return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("%d (%d)\n", root->value, root->width);

    printTree(root->left, level + 1);
}

// ������������ ������ ������
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    setlocale(LC_ALL, "Russian");

    Node* root = NULL;

    // ���� �������� ������
    int values[] = { 50, 30, 70, 20, 40, 60, 80 };
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        insertNode(&root, values[i]);
    }

    // ��������� ������ �����������
    calculateWidth(root);

    // �������� ������
    printf("������ � �������� �����������:\n");
    printTree(root, 0);

    // ����������� ������
    freeTree(root);

    return 0;
}