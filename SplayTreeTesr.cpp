#include "pch.h"
#include <gtest/gtest.h>
extern "C" {
#include "D:\Ucheba\algoritm\RealSecindSem\SplayTree.h"
}

#include <vector>
#include <algorithm>

// Вспомогательная функция для сбора in-order обхода дерева в вектор
void inorderCollect(Node* root, std::vector<int>& result) {
    if (root != nullptr) {
        inorderCollect(root->left, result);
        result.push_back(root->key);
        inorderCollect(root->right, result);
    }
}

// Тест 1: Вставка единственного узла
TEST(SplayTreeTest, InsertSingleNode) {
    Node* root = nullptr;
    root = insert(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 10);
    freeTree(root);
}

// Тест 2: Поиск существующего элемента
TEST(SplayTreeTest, SearchExistingNode) {
    Node* root = nullptr;
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = search(root, 30);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 30);
    freeTree(root);
}

// Тест 3: Поиск несуществующего элемента
TEST(SplayTreeTest, SearchNonExistingNode) {
    Node* root = nullptr;
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = search(root, 10);
    // Если элемента 10 нет, splay возвращает последний посещённый узел,
    // поэтому проверяем, что корень не равен 10.
    EXPECT_NE(root->key, 10);
    freeTree(root);
}

// Тест 4: Удаление листового узла
TEST(SplayTreeTest, DeleteLeafNode) {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20); // листовой узел
    root = deleteNode(root, 20);
    // При поиске 20 оно не должно оказаться корнем
    root = search(root, 20);
    EXPECT_NE(root->key, 20);
    freeTree(root);
}

// Тест 5: Удаление узла с одним ребёнком
TEST(SplayTreeTest, DeleteNodeWithOneChild) {
    Node* root = nullptr;
    root = insert(root, 40);
    root = insert(root, 20);
    root = insert(root, 60);
    root = insert(root, 10); // лист
    root = insert(root, 30); // второй элемент в левом поддереве
    root = deleteNode(root, 10);
    // Элемент 10 должен отсутствовать
    root = search(root, 10);
    EXPECT_NE(root->key, 10);
    freeTree(root);
}

// Тест 6: Удаление узла с двумя детьми
TEST(SplayTreeTest, DeleteNodeWithTwoChildren) {
    Node* root = nullptr;
    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 150);
    root = insert(root, 25);
    root = insert(root, 75);
    root = deleteNode(root, 50);
    // Элемент 50 должен быть удалён
    root = search(root, 50);
    EXPECT_NE(root->key, 50);
    freeTree(root);
}

// Тест 7: Вставка дубликата – дерево не должно измениться
TEST(SplayTreeTest, InsertDuplicateKey) {
    Node* root = nullptr;
    root = insert(root, 10);
    Node* root_before = root;
    root = insert(root, 10); // дубликат
    EXPECT_EQ(root->key, 10);
    freeTree(root);
}

// Тест 8: Inorder обход должен выдавать отсортированную последовательность
TEST(SplayTreeTest, InorderTraversalSorted) {
    Node* root = nullptr;
    std::vector<int> values = { 40, 20, 60, 10, 30, 50, 70 };
    for (int v : values)
        root = insert(root, v);
    std::vector<int> inorder;
    inorderCollect(root, inorder);
    std::vector<int> sorted = inorder;
    std::sort(sorted.begin(), sorted.end());
    EXPECT_EQ(inorder, sorted);
    freeTree(root);
}

// Тест 9: Последовательность операций (вставка, удаление, поиск) должна быть корректной
TEST(SplayTreeTest, MultipleOperationsConsistency) {
    Node* root = nullptr;
    // Вставка элементов
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 8);
    root = insert(root, 12);
    root = insert(root, 17);
    root = insert(root, 25);
    // Удаление некоторых элементов
    root = deleteNode(root, 10);
    root = deleteNode(root, 25);
    // Поиск
    root = search(root, 17);
    EXPECT_EQ(root->key, 17);
    // Inorder обход должен дать отсортированную последовательность: 8, 12, 15, 17, 20
    std::vector<int> inorder;
    inorderCollect(root, inorder);
    std::vector<int> expected = { 8, 12, 15, 17, 20 };
    EXPECT_EQ(inorder, expected);
    freeTree(root);
}

// Тест 10: После поиска элемент должен оказаться в корне (splay-эффект)
TEST(SplayTreeTest, SplayBringsSearchedNodeToRoot) {
    Node* root = nullptr;
    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 150);
    root = insert(root, 25);
    root = insert(root, 75);
    // Поиск элемента 25 – после splay он должен стать корнем
    root = search(root, 25);
    EXPECT_EQ(root->key, 25);
    freeTree(root);
}