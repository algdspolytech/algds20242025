#include "tree.h"
#include <gtest/gtest.h>

// Тест 1: Проверка создания узла
TEST(TreeTest, CreateNode) {
    Node* node = createNode(10);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, 10);
    EXPECT_EQ(node->width, 0);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);
}

// Тест 2: Вставка в пустое дерево
TEST(TreeTest, InsertIntoEmptyTree) {
    Node* root = nullptr;
    insertNode(&root, 20);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    freeTree(root);
}

// Тест 3: Вставка нескольких значений
TEST(TreeTest, InsertMultipleValues) {
    Node* root = nullptr;
    insertNode(&root, 50);
    insertNode(&root, 30);
    insertNode(&root, 70);
    EXPECT_EQ(root->value, 50);
    EXPECT_EQ(root->left->value, 30);
    EXPECT_EQ(root->right->value, 70);
    freeTree(root);
}

// Тест 4: Вычисление ширины поддерева для одного узла
TEST(TreeTest, CalculateWidthSingleNode) {
    Node* root = createNode(123);
    calculateWidth(root);
    EXPECT_EQ(root->width, 3); // 123 занимает 3 символа
    free(root);
}

// Тест 5: Вычисление ширины поддерева для дерева с одним потомком
TEST(TreeTest, CalculateWidthTwoNodes) {
    Node* root = createNode(50);
    insertNode(&root, 30);
    calculateWidth(root);
    EXPECT_EQ(root->width, 5); // 50 (2 символа) + 30 (2 символа) + 1 (разделитель)
    EXPECT_EQ(root->left->width, 2); // Только 30
    freeTree(root);
}

// Тест 6: Вычисление ширины сложного дерева
TEST(TreeTest, CalculateWidthComplexTree) {
    Node* root = nullptr;
    insertNode(&root, 50);
    insertNode(&root, 30);
    insertNode(&root, 70);
    insertNode(&root, 20);
    insertNode(&root, 40);
    insertNode(&root, 60);
    insertNode(&root, 80);
    calculateWidth(root);
    EXPECT_EQ(root->width, 16); // Ширина всего дерева
    EXPECT_EQ(root->left->width, 7); // Поддерево с корнем 30
    EXPECT_EQ(root->right->width, 4); // Поддерево с корнем 70
    freeTree(root);
}

// Тест 7: Проверка пустого дерева
TEST(TreeTest, CalculateWidthEmptyTree) {
    Node* root = nullptr;
    EXPECT_EQ(calculateWidth(root), 0);
}

// Тест 8: Проверка освобождения памяти
TEST(TreeTest, FreeTree) {
    Node* root = nullptr;
    insertNode(&root, 50);
    insertNode(&root, 30);
    insertNode(&root, 70);
    freeTree(root);
    EXPECT_EQ(root, nullptr); // root должен остаться пустым
}

// Тест 9: Проверка структуры дерева
TEST(TreeTest, TreeStructure) {
    Node* root = nullptr;
    insertNode(&root, 50);
    insertNode(&root, 30);
    insertNode(&root, 70);
    insertNode(&root, 20);
    EXPECT_EQ(root->left->value, 30);
    EXPECT_EQ(root->left->left->value, 20);
    EXPECT_EQ(root->right->value, 70);
    freeTree(root);
}

// Тест 10: Ширина для дерева с отрицательными числами
TEST(TreeTest, NegativeValuesWidth) {
    Node* root = nullptr;
    insertNode(&root, -50);
    insertNode(&root, -30);
    insertNode(&root, -70);
    calculateWidth(root);
    EXPECT_EQ(root->width, 12); // Учитываются отрицательные числа
    EXPECT_EQ(root->left->width, 4); // Ширина поддерева с корнем -70
    freeTree(root);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}