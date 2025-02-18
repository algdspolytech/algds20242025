#include "gtest/gtest.h"
#include "btree.h"
#include <iostream>

TEST(BTreeTest, CreateNode) {
    Node* node = createNode(10);
    ASSERT_NE(node, nullptr);
    ASSERT_EQ(node->data, 10);
    ASSERT_EQ(node->count, 1);
    ASSERT_EQ(node->left, nullptr);
    ASSERT_EQ(node->right, nullptr);
    ASSERT_EQ(node->parent, nullptr);
    free(node);
}

TEST(BTreeTest, GetCountEmpty) {
    Node* node = nullptr;
    ASSERT_EQ(getCount(node), 0);
}

TEST(BTreeTest, GetCountNotEmpty) {
    Node* node = createNode(20);
    ASSERT_EQ(getCount(node), 1);
    free(node);
}

TEST(BTreeTest, InsertNodeEmpty) {
    Node* root = nullptr;
    root = insertNode(root, 30);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->data, 30);
    ASSERT_EQ(root->count, 1);
    freeTree(root);
}

TEST(BTreeTest, InsertNodeLeft) {
    Node* root = createNode(40);
    root = insertNode(root, 20);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->left->data, 20);
    ASSERT_EQ(root->count, 2);
    freeTree(root);
}

TEST(BTreeTest, InsertNodeRight) {
    Node* root = createNode(40);
    root = insertNode(root, 60);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->right->data, 60);
    ASSERT_EQ(root->count, 2);
    freeTree(root);
}

TEST(BTreeTest, FindMinEmpty) {
    Node* root = nullptr;
    ASSERT_EQ(findMin(root), nullptr);
}

TEST(BTreeTest, FindMinNotEmpty) {
    Node* root = createNode(50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    Node* minNode = findMin(root);
    ASSERT_NE(minNode, nullptr);
    ASSERT_EQ(minNode->data, 20);
    freeTree(root);
}

TEST(BTreeTest, DeleteNodeLeaf) {
    Node* root = createNode(50);
    root = insertNode(root, 30);
    root = deleteNode(root, 30);
    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->count, 1);
    freeTree(root);
}

TEST(BTreeTest, DeleteNodeOneChild) {
    Node* root = createNode(50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = deleteNode(root, 30);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->left->data, 20);
    ASSERT_EQ(root->count, 2);
    freeTree(root);
}

TEST(BTreeTest, DeleteNodeTwoChildren) {
    Node* root = createNode(50);
    root = insertNode(root, 30);
    root = insertNode(root, 70);
    root = insertNode(root, 60);
    root = insertNode(root, 80);
    root = deleteNode(root, 70);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->right->data, 80);
    ASSERT_EQ(root->right->left->data, 60);
    freeTree(root);
}

TEST(BTreeTest, DeleteNodeRoot) {
    Node* root = createNode(50);
    root = deleteNode(root, 50);
    ASSERT_EQ(root, nullptr);
}

TEST(BTreeTest, UpdateCount) {
    Node* root = createNode(50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    ASSERT_EQ(root->count, 4);
    ASSERT_EQ(root->left->count, 3);
    freeTree(root);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}