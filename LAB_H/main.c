#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

int main() {
    RBTree* tree = createTree();
    addNode(tree, 20);
    addNode(tree, 15);
    addNode(tree, 25);
    addNode(tree, 23);

    addNode(tree, 30);

    printf("������ ����� ������� ���������\n");

    displayTree(tree->root, tree->TNULL, 0);


    int key = 23;

    Node* fNode = findNode(tree, key);
    if (findNode != tree->TNULL) {
        printf("\n������� %d ������ � ������.\n", key);
    }
    else {
        printf("\n������� %d �� ������ � ������.\n", key);
    }

    // �������� ��������
    removeNode(tree, 25);
    printf("\n������ ����� �������� �������� 25:\n");
    displayTree(tree->root, tree->TNULL, 0);

    // �������� ��������, ������� �� ����������
    removeNode(tree, 1000);
    printf("\n������ ����� ������� �������� ��������������� �������� 1000:\n");
    displayTree(tree->root, tree->TNULL, 0);

    return 0;




}

