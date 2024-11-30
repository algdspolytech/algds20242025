#include <stdio.h>
#include "bst.h"

int main() {
    Node* root = NULL;

    // ������� ��������� � ������
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("������ �� ����������� (� �������� ���������):\n");
    inorderPrint(root);
    printf("\n");

    int key = 60; // �������, ��� �������� �� ���� ������� � �������� �� K ������
    int k = 2;

    Node* result = findElementMinusK(root, key, k);
    if (result != NULL) {
        printf("������� � �������� �� %d ������ �������� %d: %d\n", k, key, result->key);
    }
    else {
        printf("������� � �������� �� %d ������ �������� %d �� ������.\n", k, key);
    }

    return 0;
}