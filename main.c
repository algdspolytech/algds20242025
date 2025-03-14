#include "splay_tree.h"
#include <stdio.h>
#include <stdbool.h>

void runTests() {
    Node* root = NULL;


    root = insert(root, 10);
    root = insert(root, 10);
    if (root->data == 10 && root->left == NULL && root->right == NULL) {
        printf("Test 1: Passed - Дубликат не добавлен\n");
    } else {
        printf("Test 1: Failed - Дубликат был добавлен\n");
    }

    // 2.
    bool found = search(root, 20); //
    if (!found) {
        printf("Test 2: Passed - Элемент 20 не найден\n");
    } else {
        printf("Test 2: Failed - Элемент 20 был найден, но его нет в дереве\n");
    }

    // 3.
    root = deleteNode(root, 30);
    if (root != NULL && root->data == 10) {
        printf("Test 3: Passed\n");
    } else {
        printf("Test 3: Failed\n");
    }

    // 4.
    root = deleteNode(root, 10);
    if (root == NULL) {
        printf("Test 4: Passed - Дерево пустое\n");
    } else {
        printf("Test 4: Failed - Дерево не стало пустым\n");
    }

    // 5.
    root = insert(root, 50);
    if (root != NULL && root->data == 50) {
        printf("Test 5: Passed - Элемент 50 успешно добавлен в дерево\n");
    } else {
        printf("Test 5: Failed - Элемент 50 не был добавлен в  дерево\n");
    }

    // 6.
    root = insert(root, 60);
    root = insert(root, 40);
    found = search(root, 40);
    if (found && root->data == 40) {
        printf("Test 6: Passed - Элемент 40 найден\n");
    } else {
        printf("Test 6: Failed - Элемент 40 не найден\n");
    }

    // 7.
    root = deleteNode(root, 40);
    if (root != NULL && root->data == 60) {
        printf("Test 7: Passed - Корневой элемент 40 удален, новый корень 60\n");
    } else {
        printf("Test 7: Failed - Корневой элемент 40 не был удален или новый корень некорректен\n");
    }

    // 8.
    found = search(NULL, 100);
    if (!found) {
        printf("Test 8: Passed\n");
    } else {
        printf("Test 8: Failed\n");
    }

    // 9.
    for (int i = 1; i <= 100; i++) {
        root = insert(root, i);
    }
    for (int i = 1; i <= 100; i++) {
        root = deleteNode(root, i);
    }
    if (root == NULL) {
        printf("Test 9: Passed - Дерево пустое\n");
    } else {
        printf("Test 9: Failed - Дерево не пустое\n");
    }

    //10.
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = deleteNode(root, 10);
    if (root != NULL && root->data == 5 && root->right != NULL && root->right->data == 20) {
        printf("Test 10: Passed - Структура дерева корректна \n");
    } else {
        printf("Test 10: Failed - Структура дерева некорректна\n");
    }
}

int main() {
    runTests();
    return 0;
}