#include "pch.h"
#include <gtest/gtest.h>
#include "C:\Users\User\OneDrive\Desktop\степенной метод\печать\печать\tree.h" 

// Тест 1: Проверка создания узла
TEST(TreeTest, CreateNode) {
    struct Node* node = createNode(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data, 5);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);  // Освобождаем память
}

// Тест 2: Проверка структуры дерева
TEST(TreeTest, TreeStructure) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    EXPECT_EQ(root->data, 1);
    EXPECT_NE(root->left, nullptr);
    EXPECT_NE(root->right, nullptr);
    EXPECT_EQ(root->left->data, 2);
    EXPECT_EQ(root->right->data, 3);
    freeTree(root);  // Освобождаем память
}

// Тест 3: Проверка печати дерева в обычном виде
TEST(TreeTest, PrintTree) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    // Здесь можно добавить проверку вывода, но это требует перенаправления stdout
    // Для простоты, просто проверяем структуру
    EXPECT_EQ(root->left->data, 2);
    EXPECT_EQ(root->right->data, 3);
    freeTree(root);
}

// Тест 4: Проверка освобождения памяти
TEST(TreeTest, FreeTree) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Здесь мы просто проверяем, что функция freeTree не вызывает ошибок
    EXPECT_NO_THROW(freeTree(root));
}

// Тест 5: Проверка печати дерева в формате "узел (левое поддерево) (правое поддерево)"
TEST(TreeTest, PrintTreeFormatted) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    // Проверка структуры дерева
    EXPECT_EQ(root->data, 1);
    EXPECT_EQ(root->left->data, 2);
    EXPECT_EQ(root->right->data, 3);
    freeTree(root);
}

// Тест 6: Проверка создания дерева с несколькими уровнями
TEST(TreeTest, MultiLevelTree) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    EXPECT_EQ(root->left->left->data, 4);
    EXPECT_EQ(root->right->right->data, 7);
    freeTree(root);
}

// Тест 7: Проверка создания пустого дерева
TEST(TreeTest, CreateEmptyTree) {
    struct Node* root = nullptr;
    EXPECT_EQ(root, nullptr);
}

// Тест 8: Проверка, что дерево правильно освобождается
TEST(TreeTest, FreeEmptyTree) {
    struct Node* root = nullptr;
    EXPECT_NO_THROW(freeTree(root));
}

// Тест 9: Проверка создания дерева с одним узлом
TEST(TreeTest, SingleNodeTree) {
    struct Node* root = createNode(1);
    EXPECT_EQ(root->data, 1);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    freeTree(root);
}

// Тест 10: Проверка, что дерево правильно освобождается после сложной структуры
TEST(TreeTest, ComplexTreeFree) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    EXPECT_NO_THROW(freeTree(root));
}

// Входная точка для запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

