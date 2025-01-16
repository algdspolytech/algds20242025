#include <stdio.h>
#include "bst.h"

int main() {
    Node* root = NULL;

    // ��������� �������� � ������
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    // ������� ���� � ������ 70 � ��� k-�� ���������������
    int key = 70, k = 2;
    Node* predecessor = find_kth_predecessor(root, key, k);

    if (predecessor) {
        printf("Kth predecessor of %d is: %d\n", key, predecessor->key);
    }
    else {
        printf("Kth predecessor of %d does not exist.\n", key);
    }

    // ����������� ������
    free_tree(root);
    return 0;
}