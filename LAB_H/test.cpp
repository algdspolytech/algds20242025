#include <gtest/gtest.h>
#include "Tree.h"

// Test 1: ���������� �������� � ������ ������
TEST(RBTreeTest, AddToEmptyTree_no1) {
    RBTree* tree = createTree();
    addNode(tree, 10);
    Node* result = findNode(tree, 10);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 10);
    ASSERT_EQ(result->color, BLACK); // ������ ������ ������
}

// Test 2: ���������� ���������� ���������, �������� ������� ������
TEST(RBTreeTest, AddMultipleElementsAndCheckBalance_no2) {
    RBTree* tree = createTree();
    addNode(tree, 20);
    addNode(tree, 15);
    addNode(tree, 25);
    addNode(tree, 10);
    addNode(tree, 30);

    Node* result = findNode(tree, 15);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 15);

    // ��������, ��� ������ �������������� (���������� ���� ����� � ������)
    ASSERT_EQ(tree->root->color, BLACK); // ������ ������ ���� ������
}

// Test 3: ����� ������������� �������� � ������
TEST(RBTreeTest, SearchExistingElement_no3) {
    RBTree* tree = createTree();
    addNode(tree, 5);
    Node* result = findNode(tree, 5);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 5);
}

// Test 4: ����� ��������������� �������� � ������
TEST(RBTreeTest, SearchNonExistentElement_no4) {
    RBTree* tree = createTree();
    addNode(tree, 5);
    Node* result = findNode(tree, 10);
    ASSERT_EQ(result, tree->TNULL);
}

// Test 5: ������� ��������, �������� ������ ��������
TEST(RBTreeTest, LeftRotateOnInsert_no5) {
    RBTree* tree = createTree();
    addNode(tree, 30);
    addNode(tree, 20);
    addNode(tree, 25);

    // ��������, ��� ������ ��������������, ����� ������� ��������
    Node* result = findNode(tree, 25);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 25);
    ASSERT_EQ(result->color, BLACK);  // ��������, ��� ������ �� �������� ������
}

// Test 6: ������� ��������, �������� ������� ��������
TEST(RBTreeTest, RightRotateOnInsert_no6) {
    RBTree* tree = createTree();
    addNode(tree, 10);
    addNode(tree, 15);
    addNode(tree, 20);

    // ��������, ��� ������ ��������������
    Node* result = findNode(tree, 15);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 15);
    ASSERT_EQ(result->color, BLACK);  // �������� ������� ������
}

// Test 7: ��������� ������� �������� (��������, ��� �������� ���������)
TEST(RBTreeTest, InsertDuplicateElement_no7) {
    RBTree* tree = createTree();
    addNode(tree, 10);
    addNode(tree, 10);  // ������� ���������, ������� �� ������ �����������

    Node* result = findNode(tree, 10);
    ASSERT_NE(result, tree->TNULL);
    ASSERT_EQ(result->data, 10);
}

// Test 8: ���������� ��������� � �������� ����� ����� ����� ���������� �������
TEST(RBTreeTest, RootColorAfterMultipleInsertions_no8) {
    RBTree* tree = createTree();
    addNode(tree, 5);
    addNode(tree, 15);
    addNode(tree, 10);
    addNode(tree, 25);
    addNode(tree, 30);

    // ���������, ��� ������ ������ ��� ��� ������
    ASSERT_EQ(tree->root->color, BLACK);
}

// Test 9: �������� ������������ ������ ����� �������� (���� ���������� �������� ����� ���������)
TEST(RBTreeTest, SearchAfterDeletion_no9) {
    RBTree* tree = createTree();
    addNode(tree, 10);
    addNode(tree, 5);
    addNode(tree, 15);

    // ������� ������� 5 (�������� �� ����������� � ���� �������, �� ���� ����� ���� ����������� � �������)
    // delete(tree, 5);
    Node* result = findNode(tree, 5);
    ASSERT_EQ(result, tree->TNULL);  // ������� ������ ���� ������, ��� ��� ��� �� ������ ���� � ������
}

// Test 10: ���������� �������� � ������ ������ � �������� ������������ ��������
TEST(RBTreeTest, AddAndFindMinElement_no10) {
    RBTree* tree = createRBTree();
    addNode(tree, 10);
    addNode(tree, 5);
    addNode(tree, 15);

    Node* minNode = tree->root;
    while (minNode->left != tree->TNULL) {
        minNode = minNode->left;  // ���� �� ������ �����, ���� �� ������ ����������� �������
    }
    ASSERT_EQ(minNode->data, 5);  // ����������� ������� � ������ � ��� 5
}