#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


// ������� ��� �������� ������ ����
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ������� ��� ������ ������ � ������� ����
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

// ������� ��� ������ ������ � �������: ���� (����� ���������) (������ ���������)
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

// ������� ��� ������������ ������, ������� �������
void freeTree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);   // ������������ ������ ���������
    freeTree(root->right);  // ������������ ������� ���������
    free(root);             // ������������ �������� ����
}


