#include <gtest/gtest.h>
#include "bst.h"

// Тест: Вставка элементов и правильный размер дерева
TEST(BSTTests, InsertElements) {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    EXPECT_EQ(root->size, 5);
    EXPECT_EQ(root->left->size, 3);  // Левое поддерево содержит 3 узла
    EXPECT_EQ(root->right->size, 1); // Правое поддерево содержит 1 узел

    free_tree(root);
}

// Тест: Поиск элемента в дереве
TEST(BSTTests, FindElement) {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);

    Node* found = find(root, 30);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->key, 30);

    Node* not_found = find(root, 100);
    EXPECT_EQ(not_found, nullptr);

    free_tree(root);
}

// Тест: Нахождение ранга элемента
TEST(BSTTests, GetRank) {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    EXPECT_EQ(get_rank(root, 20), 1); // 20 - минимальный элемент
    EXPECT_EQ(get_rank(root, 30), 2);
    EXPECT_EQ(get_rank(root, 50), 4);
    EXPECT_EQ(get_rank(root, 70), 5);

    free_tree(root);
}

// Тест: Нахождение k-го предшественника
TEST(BSTTests, FindKthPredecessor) {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    // Предшественник для ключа 50 на 2 единицы меньше (30)
    Node* predecessor = find_kth_predecessor(root, 50, 2);
    ASSERT_NE(predecessor, nullptr);
    EXPECT_EQ(predecessor->key, 30);

    // Для минимального элемента предшественников нет
    Node* no_predecessor = find_kth_predecessor(root, 20, 1);
    EXPECT_EQ(no_predecessor, nullptr);

    // Если k больше, чем ранг элемента, предшественника нет
    Node* invalid_predecessor = find_kth_predecessor(root, 50, 10);
    EXPECT_EQ(invalid_predecessor, nullptr);

    free_tree(root);
}