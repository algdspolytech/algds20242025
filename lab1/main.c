#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <assert.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define _CRTDBG_MAP_ALLOC

typedef struct Node {
    char* word;            // Слово в узле
    struct Node* left;    // Левый дочерний узел
    struct Node* right;   // Правый дочерний узел
    int subtree_width;    // Ширина поддерева
} Node;

// Функция для создания нового узла
Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->word = strdup(word); // Копируем слово
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->subtree_width = 0;   // Инициализируем ширину поддерева
    return newNode;
}

// Функция для вычисления ширины поддеревьев
int calculateSubtreeWidth(Node* node) {
    if (node == NULL) {
        return 0;
    }

    int leftWidth = calculateSubtreeWidth(node->left);
    int rightWidth = calculateSubtreeWidth(node->right);

    // Ширина поддерева = длина слова + ширина левого поддерева + ширина правого поддерева
    node->subtree_width = strlen(node->word) + leftWidth + rightWidth;

    return node->subtree_width; // Возвращаем ширину текущего поддерева
}

// Функция для печати дерева с шириной поддеревьев
void printTree(Node* node) {
    if (node == NULL) {
        return;
    }

    printTree(node->left);

    printf("Слово: %s, Ширина поддерева: %d\n", node->word, node->subtree_width);

    printTree(node->right);
}

// Функция для освобождения памяти
void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }

    freeTree(node->left);
    freeTree(node->right);
    free(node->word);
    free(node);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Пример создания бинарного дерева
    Node* root = createNode("hello");
    root->left = createNode("world");
    root->right = createNode("!");
    root->left->left = createNode("good");
    root->left->right = createNode("morning");

    // Вычисляем ширину поддеревьев
    calculateSubtreeWidth(root);

    // Печатаем дерево с шириной поддеревьев
    printTree(root);

    // Освобождаем память
    freeTree(root);

    return 0;
}

//Тесты
void Test_EmptyTree_no1() {
    Node* root = NULL;
    printf("Тест 1: Пустое дерево\n");
    calculateSubtreeWidth(root);
    printTree(root);
}

void Test_SingleNode_no2() {
    Node* root = createNode("A");
    printf("Тест 2: Одно слово\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_TwoNodes_no3() {
    Node* root = createNode("A");
    root->left = createNode("B");
    printf("Тест 3: Два узла, один левый\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_TwoNodes_Right_no4() {
    Node* root = createNode("A");
    root->right = createNode("C");
    printf("Тест 4: Два узла, один правый\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_ThreeNodes_Left_no5() {
    Node* root = createNode("A");
    root->left = createNode("B");
    root->left->left = createNode("D");
    printf("Тест 5: Три узла, все слева\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_ThreeNodes_Right_no6() {
    Node* root = createNode("A");
    root->right = createNode("C");
    root->right->right = createNode("E");
    printf("Тест 6: Три узла, все справа\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_BalancedTree_no7() {
    Node* root = createNode("A");
    root->left = createNode("B");
    root->right = createNode("C");
    printf("Тест 7: Сбалансированное дерево\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_ComplexTree_no8() {
    Node* root = createNode("A");
    root->left = createNode("B");
    root->right = createNode("C");
    root->left->left = createNode("D");
    root->left->right = createNode("E");

    printf("Тест 8: Сложное дерево\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_LongWords_no9() {
    Node* root = createNode("HelloWorld!");
    root->left = createNode("Goodbye!");

    printf("Тест 9: Длинные слова\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_EmptyLeftSubtree_no10() {
    Node* root = createNode("A");
    root->right = createNode("B");

    printf("Тест 10: Пустое левое поддерево\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Run_tests() {
    Test_EmptyTree_no1();
    Test_SingleNode_no2();
    Test_TwoNodes_no3();
    Test_TwoNodes_Right_no4();
    Test_ThreeNodes_Left_no5();
    Test_ThreeNodes_Right_no6();
    Test_BalancedTree_no7();
    Test_ComplexTree_no8();
    Test_LongWords_no9();
    Test_EmptyLeftSubtree_no10();
    printf("Success!");
}