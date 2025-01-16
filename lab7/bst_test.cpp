#include <gtest/gtest.h>
#include "bst.h"

// ����: ������� ��������� � ���������� ������ ������
TEST(BSTTests, InsertElements) {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    EXPECT_EQ(root->size, 5);
    EXPECT_EQ(root->left->size, 3);  // ����� ��������� �������� 3 ����
    EXPECT_EQ(root->right->size, 1); // ������ ��������� �������� 1 ����

    free_tree(root);
}

// ����: ����� �������� � ������
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

// ����: ���������� ����� ��������
TEST(BSTTests, GetRank) {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    EXPECT_EQ(get_rank(root, 20), 1); // 20 - ����������� �������
    EXPECT_EQ(get_rank(root, 30), 2);
    EXPECT_EQ(get_rank(root, 50), 4);
    EXPECT_EQ(get_rank(root, 70), 5);

    free_tree(root);
}

// ����: ���������� k-�� ���������������
TEST(BSTTests, FindKthPredecessor) {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    // �������������� ��� ����� 50 �� 2 ������� ������ (30)
    Node* predecessor = find_kth_predecessor(root, 50, 2);
    ASSERT_NE(predecessor, nullptr);
    EXPECT_EQ(predecessor->key, 30);

    // ��� ������������ �������� ���������������� ���
    Node* no_predecessor = find_kth_predecessor(root, 20, 1);
    EXPECT_EQ(no_predecessor, nullptr);

    // ���� k ������, ��� ���� ��������, ��������������� ���
    Node* invalid_predecessor = find_kth_predecessor(root, 50, 10);
    EXPECT_EQ(invalid_predecessor, nullptr);

    free_tree(root);
}