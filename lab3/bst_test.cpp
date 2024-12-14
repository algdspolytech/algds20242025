#include <gtest/gtest.h>
#include "bst.h"

// Тесты для функции вставки
TEST(BSTTest, AddToEmptyTree_no1) {
    Node* root = NULL;
    root = insert(root, 10);
    EXPECT_EQ(root->data, 10);
    EXPECT_EQ(root->count, 1);
}

TEST(BSTTest, AddMultipleElements_HappyPath_no2) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    EXPECT_EQ(root->data, 10);
    EXPECT_EQ(root->left->data, 5);
    EXPECT_EQ(root->right->data, 15);
    EXPECT_EQ(root->count, 3);
}

TEST(BSTTest, AddDuplicateElements_no3) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 10); // Дубликат
    EXPECT_EQ(root->data, 10);
    EXPECT_EQ(root->count, 1); // Дубликаты не учитываются
}

TEST(BSTTest, AddNegativeAndPositiveElements_no4) {
    Node* root = NULL;
    root = insert(root, -10);
    root = insert(root, 0);
    root = insert(root, 10);
    EXPECT_EQ(root->data, 0);
    EXPECT_EQ(root->left->data, -10);
    EXPECT_EQ(root->right->data, 10);
}

TEST(BSTTest, AddElementsInDescendingOrder_no5) {
    Node* root = NULL;
    for (int i = 10; i > 0; --i) {
        root = insert(root, i);
    }
    EXPECT_EQ(root->data, 5); // Корень должен быть в середине
}

// Тесты для поиска K-го наименьшего элемента
TEST(BSTTest, KthSmallest_EmptyTree_no6) {
    Node* root = NULL;
    int count = 0;
    int result = kthSmallest(root, 1, &count);
    EXPECT_EQ(result, -1); // Пустое дерево
}

TEST(BSTTest, KthSmallest_SingleElement_no7) {
    Node* root = insert(NULL, 10);
    int count = 0;
    int result = kthSmallest(root, 1, &count);
    EXPECT_EQ(result, 10); // K=1
}

TEST(BSTTest, KthSmallest_MultipleElements_no8) {
    Node* root = NULL;
    for (int i = 1; i <= 5; ++i) {
        root = insert(root, i);
    }
    
    int count = 0;
    int result = kthSmallest(root, 3, &count);
    EXPECT_EQ(result, 3); // K=3
}

TEST(BSTTest, KthSmallest_KGreaterThanCount_no9) {
    Node* root = NULL;
    for (int i = 1; i <= 5; ++i) {
        root = insert(root, i);
    }
    
    int count = 0;
    int result = kthSmallest(root, 10, &count); // K больше количества узлов
    EXPECT_EQ(result, -1);
}

// Тесты для печати элементов с порядковыми номерами меньше K
TEST(BSTTest, PrintElementsLessThanK_EmptyTree_no10) {
    Node* root = NULL;
    int K = 3;
        testing::internal::CaptureStdout();
    printElementsLessThanK(root, K);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, ""); // Пустое дерево
}

TEST(BSTTest, PrintElementsLessThanK_SingleElement_no11) {
    Node* root = insert(NULL, 10);
    int K = 2; // Элементов меньше K нет
    testing::internal::CaptureStdout();
    printElementsLessThanK(root, K);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, ""); // Нет элементов меньше K
}

TEST(BSTTest, PrintElementsLessThanK_MultipleElements_no12) {
    Node* root = NULL;
    for (int i = 1; i <= 5; ++i) {
        root = insert(root, i);
    }
    
    int K = 4; // Элементы: 1, 2, 3
    testing::internal::CaptureStdout();
    printElementsLessThanK(root, K);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "1 2 3 "); // Ожидаемый вывод
}