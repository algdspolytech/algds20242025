#include <stdio.h>
#include "tree.h"
#include <locale.h>
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS

int main() {
    setlocale(LC_ALL, "Rus");
    // �������� ������
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    
    printf("������ � ������� ����:\n");
    printTree(root, 0);
    
    printf("\n������ � �������: ���� (����� ���������) (������ ���������):\n");
    printTreeFormatted(root);
    printf("\n");

    freeTree(root);

    return 0;
}


