#include "tree.h"
#include <gtest/gtest.h>

// ���� 1: �������� �������� ����
TEST(TreeTest, CreateNode) {
    Node* node = createNode(10);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, 10);
    EXPECT_EQ(node->width, 0);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);
}

// ���� 2: ������� � ������ ������
TEST(TreeTest, InsertIntoEmptyTree) {
    Node* root = nullptr;
    insertNode(&root, 20);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    freeTree(root);
}

// ���� 3: ������� ���������� ��������
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

// ���� 4: ���������� ������ ��������� ��� ������ ����
TEST(TreeTest, CalculateWidthSingleNode) {
    Node* root = createNode(123);
    calculateWidth(root);
    EXPECT_EQ(root->width, 3); // 123 �������� 3 �������
    free(root);
}

// ���� 5: ���������� ������ ��������� ��� ������ � ����� ��������
TEST(TreeTest, CalculateWidthTwoNodes) {
    Node* root = createNode(50);
    insertNode(&root, 30);
    calculateWidth(root);
    EXPECT_EQ(root->width, 5); // 50 (2 �������) + 30 (2 �������) + 1 (�����������)
    EXPECT_EQ(root->left->width, 2); // ������ 30
    freeTree(root);
}

// ���� 6: ���������� ������ �������� ������
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
    EXPECT_EQ(root->width, 16); // ������ ����� ������
    EXPECT_EQ(root->left->width, 7); // ��������� � ������ 30
    EXPECT_EQ(root->right->width, 4); // ��������� � ������ 70
    freeTree(root);
}

// ���� 7: �������� ������� ������
TEST(TreeTest, CalculateWidthEmptyTree) {
    Node* root = nullptr;
    EXPECT_EQ(calculateWidth(root), 0);
}

// ���� 8: �������� ������������ ������
TEST(TreeTest, FreeTree) {
    Node* root = nullptr;
    insertNode(&root, 50);
    insertNode(&root, 30);
    insertNode(&root, 70);
    freeTree(root);
    EXPECT_EQ(root, nullptr); // root ������ �������� ������
}

// ���� 9: �������� ��������� ������
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

// ���� 10: ������ ��� ������ � �������������� �������
TEST(TreeTest, NegativeValuesWidth) {
    Node* root = nullptr;
    insertNode(&root, -50);
    insertNode(&root, -30);
    insertNode(&root, -70);
    calculateWidth(root);
    EXPECT_EQ(root->width, 12); // ����������� ������������� �����
    EXPECT_EQ(root->left->width, 4); // ������ ��������� � ������ -70
    freeTree(root);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}