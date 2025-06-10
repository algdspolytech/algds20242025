#include "pch.h"
extern "C" {
#include "Treap.h"
}

TEST(TreapTest, InsertIntoEmptyTree) {
    Node* root = nullptr;
    root = insert(root, 10);
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->key, 10);
    free_tree(root);
}

TEST(TreapTest, InsertMultipleElements) {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    EXPECT_TRUE(search(root, 5) != nullptr);
    EXPECT_TRUE(search(root, 15) != nullptr);
    free_tree(root);
}

TEST(TreapTest, SearchExistingElement) {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    Node* found = search(root, 20);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->key, 20);
    free_tree(root);
}

TEST(TreapTest, SearchNonExistentElement) {
    Node* root = nullptr;
    root = insert(root, 10);
    EXPECT_EQ(search(root, 99), nullptr);
    free_tree(root);
}

TEST(TreapTest, DeleteRoot) {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = deleteNode(root, 10);
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(search(root, 10), nullptr);
    free_tree(root);
}

TEST(TreapTest, DeleteLeaf) {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = deleteNode(root, 5);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(search(root, 5), nullptr);
    free_tree(root);
}

TEST(TreapTest, HeapProperty) {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    if (root->left) {
        EXPECT_GE(root->priority, root->left->priority);
    }
    if (root->right) {
        EXPECT_GE(root->priority, root->right->priority);
    }
    free_tree(root);
}

TEST(TreapTest, SplitTree) {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    Node* left = nullptr, * right = nullptr;
    split(root, 10, &left, &right);
    EXPECT_NE(left, nullptr);
    EXPECT_NE(right, nullptr);
    EXPECT_LE(left->key, 10);
    EXPECT_GT(right->key, 10);
    free_tree(left);
    free_tree(right);
}

TEST(TreapTest, MergeTrees) {
    Node* left = nullptr;
    left = insert(left, 5);
    Node* right = nullptr;
    right = insert(right, 15);
    Node* merged = merge(left, right);
    EXPECT_NE(merged, nullptr);
    EXPECT_NE(search(merged, 5), nullptr);
    EXPECT_NE(search(merged, 15), nullptr);
    free_tree(merged);
}

TEST(TreapTest, NoDuplicateKeys) {
    Node* root = nullptr;
    root = insert(root, 42);
    Node* new_root = insert(root, 42);
    EXPECT_EQ(root, new_root);
    free_tree(root);
}