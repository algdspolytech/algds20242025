#include "gtest/gtest.h"
extern "C" {
#include "bst.h"  // ����������� C-������� �� ���������
}

// ���� ��� createNode
TEST(createNode_ValidInput_no1, ReturnValidNode) {
    Node* node = createNode(10);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->key, 10);
    EXPECT_EQ(node->size, 1);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);
}

// ����� ��� insert
TEST(insert_NewElement_no2, IncreasesSize) {
    Node* root = createNode(50);
    root = insert(root, 30);
    EXPECT_EQ(root->size, 2); // ������ ������ �����������
    free(root->left);
    free(root);
}

TEST(insert_DuplicateKey_no3, NoSizeChange) {
    Node* root = createNode(50);
    root = insert(root, 50); // ������� ���������
    EXPECT_EQ(root->size, 1); // ������ �� ������ ����������
    free(root);
}

// ����� ��� updateSize
TEST(updateSize_LeftChild_no4, UpdatesSize) {
    Node* root = createNode(50);
    root->left = createNode(30);
    updateSize(root);
    EXPECT_EQ(root->size, 2); // ������ ����� ������ ���� 2
    free(root->left);
    free(root);
}

TEST(updateSize_RightChild_no4, UpdatesSize) {
    Node* root = createNode(50);
    root->right = createNode(70);
    updateSize(root);
    EXPECT_EQ(root->size, 2); // ������ ����� ������ ���� 2
    free(root->right);
    free(root);
}

// ����� ��� findKthSmallest
TEST(findKthSmallest_SecondElement_no5, ReturnValidNode) {
    Node* root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 70);
    Node* result = findKthSmallest(root, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->key, 50); // ������ ������� � �������� ����
    free(root->left);
    free(root->right);
    free(root);
}

TEST(findKthSmallest_KTooLarge_no6, ReturnNull) {
    Node* root = createNode(50);
    root = insert(root, 30);
    Node* result = findKthSmallest(root, 3); // ������ ������ ������ 3
    EXPECT_EQ(result, nullptr);
    free(root->left);
    free(root);
}

// ����� ��� findOrderOfElement
TEST(findOrderOfElement_ValidKey_no7, ReturnOrder) {
    Node* root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 70);
    int order = findOrderOfElement(root, 70);
    EXPECT_EQ(order, 3); // ���� � ������ 70 � ������ �� �������
    free(root->left);
    free(root->right);
    free(root);
}

TEST(findOrderOfElement_NonExistentKey_no8, ReturnMinusOne) {
    Node* root = createNode(50);
    root = insert(root, 30);
    int order = findOrderOfElement(root, 70); // ����� 70 ��� � ������
    EXPECT_EQ(order, -1);
    free(root->left);
    free(root);
}

// ����� ��� findElementMinusK
TEST(findElementMinusK_ValidKeyAndK_no9, ReturnValidNode) {
    Node* root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    Node* result = findElementMinusK(root, 70, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->key, 30); // �� 2 �������� ������ �� �������
    free(root->left->left);
    free(root->left);
    free(root->right);
    free(root);
}

TEST(findElementMinusK_InvalidK_no10, ReturnNull) {
    Node* root = createNode(50);
    root = insert(root, 30);
    root = insert(root, 70);
    Node* result = findElementMinusK(root, 50, 3); // K ������, ��� ������� ��������
    EXPECT_EQ(result, nullptr);
    free(root->left);
    free(root->right);
    free(root);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}