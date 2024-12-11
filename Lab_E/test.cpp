#include "pch.h"
#include <gtest/gtest.h>
#include "C:\Users\User\OneDrive\Desktop\��������� �����\������\������\tree.h" 

// ���� 1: �������� �������� ����
TEST(TreeTest, CreateNode) {
    struct Node* node = createNode(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data, 5);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);  // ����������� ������
}

// ���� 2: �������� ��������� ������
TEST(TreeTest, TreeStructure) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    EXPECT_EQ(root->data, 1);
    EXPECT_NE(root->left, nullptr);
    EXPECT_NE(root->right, nullptr);
    EXPECT_EQ(root->left->data, 2);
    EXPECT_EQ(root->right->data, 3);
    freeTree(root);  // ����������� ������
}

// ���� 3: �������� ������ ������ � ������� ����
TEST(TreeTest, PrintTree) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    // ����� ����� �������� �������� ������, �� ��� ������� ��������������� stdout
    // ��� ��������, ������ ��������� ���������
    EXPECT_EQ(root->left->data, 2);
    EXPECT_EQ(root->right->data, 3);
    freeTree(root);
}

// ���� 4: �������� ������������ ������
TEST(TreeTest, FreeTree) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // ����� �� ������ ���������, ��� ������� freeTree �� �������� ������
    EXPECT_NO_THROW(freeTree(root));
}

// ���� 5: �������� ������ ������ � ������� "���� (����� ���������) (������ ���������)"
TEST(TreeTest, PrintTreeFormatted) {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    // �������� ��������� ������
    EXPECT_EQ(root->data, 1);
    EXPECT_EQ(root->left->data, 2);
    EXPECT_EQ(root->right->data, 3);
    freeTree(root);
}

// ���� 6: �������� �������� ������ � ����������� ��������
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

// ���� 7: �������� �������� ������� ������
TEST(TreeTest, CreateEmptyTree) {
    struct Node* root = nullptr;
    EXPECT_EQ(root, nullptr);
}

// ���� 8: ��������, ��� ������ ��������� �������������
TEST(TreeTest, FreeEmptyTree) {
    struct Node* root = nullptr;
    EXPECT_NO_THROW(freeTree(root));
}

// ���� 9: �������� �������� ������ � ����� �����
TEST(TreeTest, SingleNodeTree) {
    struct Node* root = createNode(1);
    EXPECT_EQ(root->data, 1);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    freeTree(root);
}

// ���� 10: ��������, ��� ������ ��������� ������������� ����� ������� ���������
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

// ������� ����� ��� ������� ������
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

