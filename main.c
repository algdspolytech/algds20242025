#include "splay_tree.h"
#include <stdio.h>

void runTests() {
    Node* root = NULL;


    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    if (root->data == 5) {
        printf("Test 1: Passed - Корнем дерева стал элемент 5\n");
    } else {
        printf("Test 1: Failed - Ожидалось, что корнем станет элемент 5, но корень равен %d\n", root->data);
    }


    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 6);
    printf("Test 2: ");
    inorder(root);
    printf("\n");


    bool found = search(root, 7);
    if (found && root->data == 7) {
        printf("Test 3: Passed - Элемент 7 найден и стал корнем дерева\n");
    } else {
        printf("Test 3: Failed - Ожидалось, что элемент 7 станет корнем, но корень равен %d\n", root->data);
    }


    found = search(root, 100);
    if (!found) {
        printf("Test 4: Passed - Элемент 100 не найден\n");
    } else {
        printf("Test 4: Failed - Элемент 100 был найден,но его нет в дереве\n");
    }


    root = deleteNode(root, 4);
    printf("Test 5: ");
    inorder(root);
    printf("\n");


    root = deleteNode(root, 7);
    printf("Test 6: ");
    inorder(root);
    printf("\n");


    root = deleteNode(root, 100);
    printf("Test 7: ");
    inorder(root);
    printf("\n");


    root = deleteNode(root, 2);
    root = deleteNode(root, 3);
    root = deleteNode(root, 5);
    root = deleteNode(root, 6);
    root = deleteNode(root, 10);
    root = deleteNode(root, 20);
    if (root == NULL) {
        printf("Test 8: Passed - Дерево успешно очищено\n");
    } else {
        printf("Test 8: Failed - Дерево не пустое, корень равен %d\n", root->data);
    }


    root = insert(root, 5);
    root = insert(root, 5);
    printf("Test 9: ");
    inorder(root);
    printf("\n");


    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = deleteNode(root, 20);
    printf("Test 10: ");
    inorder(root);
    printf("\n");
}

int main() {
    runTests();
    return 0;
}