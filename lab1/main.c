#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"
#include "funcs.h"
#include "tests.h"

// ������������
int main() {

    setlocale(LC_ALL, "Rus");

    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("����� ������ (inorder): ");
    inorder(root);
    printf("\n");

    root = search(root, 30);
    printf("����� ������ 30 (������: %d)\n", root->key);

    root = delete(root, 30);
    printf("����� �������� 30:\n");
    inorder(root);
    printf("\n");

    run_tests();

    return 0;
}