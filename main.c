#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data; // Оригинальные данные
    size_t width; // Ширина узла
    struct Node* left;
    struct Node* right;
} Node;

// Функция для создания нового узла
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data; // Сохраняем оригинальные данные
    newNode->width = 0; // Инициализируем ширину
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для вычисления ширины поддеревьев
size_t calculateWidth(Node* root) {
    if (root == NULL) {
        return 0;
    }
    // Преобразуем число в строку для вычисления ширины
    char buffer[20];
    sprintf(buffer, "%d", root->data);
    size_t width = strlen(buffer); // Используем size_t
    return width + calculateWidth(root->left) + calculateWidth(root->right);
}

// Функция для заполнения ширины поддеревьев
void fillSubtreeWidths(Node* root) {
    if (root == NULL) {
        return;
    }
    root->width = calculateWidth(root); // Сохраняем ширину в отдельном поле
    fillSubtreeWidths(root->left);
    fillSubtreeWidths(root->right);
}

// Функция для печати дерева
void printTree(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("Data: %d, Width: %zu\n", root->data, root->width);
    printTree(root->left);
    printTree(root->right);
}

// Функция для освобождения памяти
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}




// Юнит-тесты

// Тест 1: Проверка простого бинарного дерева с двумя узлами
void testFillSubtreeWidths_no1() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    fillSubtreeWidths(root);
    printf("Test 1: ");
    if (root->width == 3 && root->left->width == 1 && root->right->width == 1) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// Тест 2: Проверка дерева с несколькими уровнями и узлами
void testFillSubtreeWidths_no2() {
    Node* root = createNode(10);
    root->left = createNode(20);
    root->right = createNode(30);
    root->left->left = createNode(40);
    fillSubtreeWidths(root);
    printf("Test 2: ");
    if (root->width == 8 && root->left->width == 4 && root->right->width == 2) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// Тест 3: Проверка случая с единственным узлом
void testFillSubtreeWidths_no3() {
    Node* root = createNode(100);
    fillSubtreeWidths(root);
    printf("Test 3: ");
    if (root->width == 3) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// Тест 4: Проверка случая с пустым деревом
void testFillSubtreeWidths_no4() {
    Node* root = NULL;
    fillSubtreeWidths(root);
    printf("Test 4: ");
    if (root == NULL) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
}

// Тест 5: Проверка дерева с одним узлом и одним дочерним узлом
void testFillSubtreeWidths_no5() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = NULL;
    fillSubtreeWidths(root);
    printf("Test 5: ");
    if (root->width == 2 && root->left->width == 1) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// Тест 6: Проверка дерева с несколькими уровнями и узлами, включая ноль
void testFillSubtreeWidths_no6() {
    Node* root = createNode(123);
    root->left = createNode(456);
    root->right = createNode(789);
    root->left->left = createNode(0);
    root->left->right = createNode(1);
    fillSubtreeWidths(root);
    printf("Test 6: ");
    if (root->width == 11 && root->left->width == 5 && root->right->width == 3) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// Тест 7: Проверка дерева с несколькими уровнями и узлами, все узлы имеют трехзначные значения
void testFillSubtreeWidths_no7() {
    Node* root = createNode(999);
    root->left = createNode(888);
    root->right = createNode(777);
    root->left->left = createNode(666);
    root->left->right = createNode(555);
    root->right->left = createNode(444);
    root->right->right = createNode(333);
    fillSubtreeWidths(root);
    printf("Test 7: ");
    if (root->width == 21 && root->left->width == 9 && root->right->width == 9 &&
        root->left->left->width == 3 && root->left->right->width == 3 &&
        root->right->left->width == 3 && root->right->right->width == 3) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// Тест 8: Проверка полного бинарного дерева с несколькими уровнями
void testFillSubtreeWidths_no8() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    fillSubtreeWidths(root);
    printf("Test 8: ");
    if (root->width == 7 && root->left->width == 3 && root->right->width == 3) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// Тест 9: Проверка дерева с отрицательными значениями
void testFillSubtreeWidths_no9() {
    Node* root = createNode(0);
    root->left = createNode(-1);
    root->right = createNode(-2);
    fillSubtreeWidths(root);
    printf("Test 9: ");
    if (root->width == 5 && root->left->width == 2 && root->right->width == 2) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

// Тест 10: Проверка дерева с большими значениями
void testFillSubtreeWidths_no10() {
    Node* root = createNode(12345);
    root->left = createNode(67890);
    root->right = createNode(11111);
    root->left->left = createNode(22222);
    root->left->right = createNode(33333);
    root->right->left = createNode(44444);
    root->right->right = createNode(55555);
    fillSubtreeWidths(root);
    printf("Test 10: ");
    if (root->width == 35 && root->left->width == 15 && root->right->width == 15 &&
        root->left->left->width == 5 && root->left->right->width == 5 &&
        root->right->left->width == 5 && root->right->right->width == 5) {
        printf("Successfully\n");
    }
    else {
        printf("Failed\n");
    }
    freeTree(root);
}

int main() {
    testFillSubtreeWidths_no1();
    testFillSubtreeWidths_no2();
    testFillSubtreeWidths_no3();
    testFillSubtreeWidths_no4();
    testFillSubtreeWidths_no5();
    testFillSubtreeWidths_no6();
    testFillSubtreeWidths_no7();
    testFillSubtreeWidths_no8();
    testFillSubtreeWidths_no9();
    testFillSubtreeWidths_no10();

    return 0;
}