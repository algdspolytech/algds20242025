#include "pch.h"
#include "../LabH_lib.c"
#include <gtest/gtest.h>

TEST(TreapTest, InsertToEmptyTree_no1) {
    Node* root = NULL;
    root = insert(root, 10);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->key, 10);
    freeTree(root);
}

TEST(TreapTest, InsertMultipleElements_no2) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    ASSERT_NE(root, nullptr);
    freeTree(root);
}

TEST(TreapTest, DeleteElement_no3) {
    Node* root = NULL;
    root = insert(root, 10);
    root = erase(root, 10);
    ASSERT_EQ(root, nullptr);
    freeTree(root);
}

TEST(TreapTest, DeleteNonExistentElement_no4) {
    Node* root = NULL;
    root = insert(root, 10);
    root = erase(root, 20);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->key, 10);
    freeTree(root);
}

TEST(TreapTest, SplitTree_no5) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    Node* left, * right;
    split(root, 15, &left, &right);
    ASSERT_NE(left, nullptr);
    ASSERT_EQ(left->key, 10);
    ASSERT_NE(right, nullptr);
    ASSERT_EQ(right->key, 20);
    freeTree(left);
    freeTree(right);
}

TEST(TreapTest, MergeTrees_no6) {
    Node* left = createNode(10);
    Node* right = createNode(20);
    Node* root = merge(left, right);
    ASSERT_NE(root, nullptr);
    freeTree(root);
}

TEST(TreapTest, InsertNegativeValues_no7) {
    Node* root = NULL;
    root = insert(root, -10);
    root = insert(root, -20);
    ASSERT_NE(root, nullptr);
    ASSERT_TRUE(root->key == -10 || root->key == -20);
    freeTree(root);
}

TEST(TreapTest, LargeNumberInsert_no8) {
    Node* root = NULL;
    root = insert(root, 1000000);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->key, 1000000);
    freeTree(root);
}

TEST(TreapTest, MergeWithEmptyTree_no9) {
    Node* root = createNode(10);
    root = merge(root, NULL);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->key, 10);
    freeTree(root);
}

TEST(TreapTest, SplitAtRoot_no10) {
    Node* root = createNode(25);
    Node* left, * right;
    split(root, 25, &left, &right);
    ASSERT_EQ(left, nullptr);
    ASSERT_NE(right, nullptr);
    ASSERT_EQ(right->key, 25);
    freeTree(right);
}

TEST(TreapTest, DeleteFromSingleNode_no11) {
    Node* root = createNode(10);
    root = erase(root, 10);
    ASSERT_EQ(root, nullptr);
}


TEST(TreapTest, MergeTreesDifferentPriorities_no12) {
    Node* left = createNode(10);
    left->priority = 100;
    Node* right = createNode(20);
    right->priority = 50;
    Node* root = merge(left, right);
    ASSERT_EQ(root->key, 10);
    freeTree(root);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}