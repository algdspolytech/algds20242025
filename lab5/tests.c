#define _CRT_SECURE_NO_WARNINGS
#include <locale.h> // Для поддержки русского языка
#include <assert.h>  // Для использования assert
#include "tree.h"

// Тест 1: Проверка пустого дерева
void test_updateHeightDifference_empty() {
    struct Node* root = NULL;
    updateHeightDifference(root);  // Для пустого дерева не должно быть изменений
}

// Тест 2: Проверка дерева с одним узлом
void test_updateHeightDifference_single_node() {
    struct Node* root = createNode(5);
    updateHeightDifference(root);
    assert(root->data == 0);  // Узел без потомков, разница высот = 0
}

// Тест 3: Проверка дерева с левым поддеревом
void test_updateHeightDifference_left_only() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    updateHeightDifference(root);
    assert(root->data == 1);  // Разница высот: 1 (наличие только левого поддерева)
    assert(root->left->data == 0);  // Узел без потомков, разница высот = 0
}

// Тест 4: Проверка дерева с правым поддеревом
void test_updateHeightDifference_right_only() {
    struct Node* root = createNode(5);
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == -1);  // Разница высот: -1 (наличие только правого поддерева)
    assert(root->right->data == 0);  // Узел без потомков, разница высот = 0
}

// Тест 5: Проверка дерева с двумя узлами (левым и правым)
void test_updateHeightDifference_two_nodes() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == 0);  // Разница высот левого и правого поддерева равна 0
    assert(root->left->data == 0);  // Узел без потомков, разница высот = 0
    assert(root->right->data == 0);  // Узел без потомков, разница высот = 0
}

// Тест 6: Проверка дерева, где одно поддерево пустое
void test_updateHeightDifference_one_subtree_empty() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    updateHeightDifference(root);
    assert(root->data == 1);  // Разница высот между левым поддеревом и отсутствием правого
    assert(root->left->data == 0);  // Узел без потомков, разница высот = 0
}
// Тест 7: Проверка дерева, где левое поддерево глубже правого
void test_updateHeightDifference_left_deeper() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->left->left = createNode(1);  // Левое поддерево глубже
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == 1);  // Разница высот: левое поддерево глубже правого
    assert(root->left->data == 1);  // Разница высот в левом поддереве
    assert(root->right->data == 0);  // Разница высот у правого поддерева
}


// Тест 8: Проверка дерева, где правое поддерево глубже левого
void test_updateHeightDifference_right_deeper() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(8);
    root->right->right = createNode(9);  // Правое поддерево глубже
    updateHeightDifference(root);
    assert(root->data== -1);  // Разница высот: правое поддерево глубже
    assert(root->left->data== 0);  // Разница высот у левого поддерева
    assert(root->right->data == -1);  // Разница высот в правом поддереве
}

// Тест 9: Проверка несбалансированного дерева с левым поддеревом
void test_updateHeightDifference_unbalanced() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->left->left = createNode(1);
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == 1);  // Разница высот между левым (глубже) и правым поддеревом
    assert(root->left->data == 1);  // Разница высот в левом поддереве
    assert(root->right->data == 0);  // Разница высот у правого поддерева
}



// Тест 10: Проверка дерева с глубоким правым поддеревом
void test_updateHeightDifference_deep_right_subtree() {
    struct Node* root = createNode(10);
    root->right = createNode(20);
    root->right->right = createNode(30);
    root->right->right->right = createNode(40);  // Глубокое правое поддерево
    updateHeightDifference(root);
    assert(root->data == -3);  // Разница высот правого (глубже) поддерева
    assert(root->right->data == -2);  // Разница высот в правом поддереве
}

// Тест 11: Проверка сбалансированного дерева
void test_updateHeightDifference_balanced() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == 0);  // Разница высот левого и правого поддерева равна 0
    assert(root->left->data == 0);  // Узел без потомков, разница высот = 0
    assert(root->right->data == 0);  // Узел без потомков, разница высот = 0
}

int main() {
    // Устанавливаем локаль на русский язык
    setlocale(LC_ALL, "Russian");

    // Вызов всех тестов
    test_updateHeightDifference_empty();
    test_updateHeightDifference_single_node();
    test_updateHeightDifference_left_only();
    test_updateHeightDifference_right_only();
    test_updateHeightDifference_two_nodes();
    test_updateHeightDifference_one_subtree_empty();
    test_updateHeightDifference_left_deeper();
    test_updateHeightDifference_right_deeper();
    test_updateHeightDifference_unbalanced();
    test_updateHeightDifference_deep_right_subtree();
    test_updateHeightDifference_balanced();
    return 0;
}
