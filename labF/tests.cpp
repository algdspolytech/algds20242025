#include "gtest/gtest.h"
extern "C" {
#include "bst.h"  // Подключение C-функций из заголовка
}

// Тест для createNode
TEST(createNode_ValidInput_no1, ReturnValidNode) {
    Node* node = createNode(10);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->key, 10);
    EXPECT_EQ(node->size, 1);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);
}

// Тесты для insert
TEST(insert_NewElement_no2, IncreasesSize) {
    Node* root = createNode(50);
    root = insert(root, 30);
    EXPECT_EQ(root->size, 2); // Размер должен увеличиться
    free(root->left);
    free(root);
}

TEST(insert_DuplicateKey_no3, NoSizeChange) {
    Node* root = createNode(50);
    root = insert(root, 50); // Вставка дубликата
    EXPECT_EQ(root->size, 1); // Размер не должен измениться
    free(root);
}

// Тесты для updateSize
TEST(updateSize_LeftChild_no4, UpdatesSize) {
    Node* root = createNode(50);
    root->left = createNode(30);
    updateSize(root);
    EXPECT_EQ(root->size, 2); // Размер корня должен быть 2
    free(root->left);
    free(root);
}

TEST(updateSize_RightChild_no4, UpdatesSize) {
    Node* root = createNode(50);
    root->right = createNode(70);
    updateSize(root);
    EXPECT_EQ(root->size, 2); // Размер корня должен быть 2
    free(root->right);
    free(root);
}

// Тесты для findKthSmallest
TEST(findKthSmallest_SecondElement_no5, ReturnValidNode) {
    Node* root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 70);
    Node* result = findKthSmallest(root, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->key, 50); // Второй элемент — корневой узел
    free(root->left);
    free(root->right);
    free(root);
}

TEST(findKthSmallest_KTooLarge_no6, ReturnNull) {
    Node* root = createNode(50);
    root = insert(root, 30);
    Node* result = findKthSmallest(root, 3); // Размер дерева меньше 3
    EXPECT_EQ(result, nullptr);
    free(root->left);
    free(root);
}

// Тесты для findOrderOfElement
TEST(findOrderOfElement_ValidKey_no7, ReturnOrder) {
    Node* root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 70);
    int order = findOrderOfElement(root, 70);
    EXPECT_EQ(order, 3); // Узел с ключом 70 — третий по порядку
    free(root->left);
    free(root->right);
    free(root);
}

TEST(findOrderOfElement_NonExistentKey_no8, ReturnMinusOne) {
    Node* root = createNode(50);
    root = insert(root, 30);
    int order = findOrderOfElement(root, 70); // Ключа 70 нет в дереве
    EXPECT_EQ(order, -1);
    free(root->left);
    free(root);
}

// Тесты для findElementMinusK
TEST(findElementMinusK_ValidKeyAndK_no9, ReturnValidNode) {
    Node* root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    Node* result = findElementMinusK(root, 70, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->key, 30); // На 2 элемента меньше по порядку
    free(root->left->left);
    free(root->left);
    free(root->right);
    free(root);
}

TEST(findElementMinusK_InvalidK_no10, ReturnNull) {
    Node* root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 70);
    Node* result = findElementMinusK(root, 50, 3); // K больше, чем порядок элемента
    EXPECT_EQ(result, nullptr);
    free(root->left);
    free(root->right);
    free(root);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}