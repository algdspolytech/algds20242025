#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "Lab_H.h" // ?????????? ??? ??? ? ????????
}

TEST(RBTreeTest, CreateNode) {
    Node* node = createNode(10, RED);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->key, 10);
    EXPECT_EQ(node->color, RED);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    EXPECT_EQ(node->parent, nullptr);
    free(node);
}

TEST(RBTreeTest, BlackHeight) {
    Node* root = createNode(10, BLACK);
    root->left = createNode(5, RED);
    root->left->parent = root;
    root->right = createNode(20, RED);
    root->right->parent = root;
    EXPECT_EQ(blackHeight(root), 1);
    free(root->left);
    free(root->right);
    free(root);
}

TEST(RBTreeTest, FindBlHeightRight) {
    Node* root = createNode(10, BLACK);
    root->right = createNode(20, RED);
    root->right->parent = root;
    Node* res = findBlHeightRight(root, 1);
    ASSERT_NE(res, nullptr);
    EXPECT_EQ(res->key, 20);
    free(root->right);
    free(root);
}

TEST(RBTreeTest, FindBlHeightLeft) {
    Node* root = createNode(10, BLACK);
    root->left = createNode(5, RED);
    root->left->parent = root;
    Node* res = findBlHeightLeft(root, 1);
    ASSERT_NE(res, nullptr);
    EXPECT_EQ(res->key, 5);
    free(root->left);
    free(root);
}

TEST(RBTreeTest, Rotations) {
    Node* root = createNode(10, BLACK);
    root->right = createNode(20, RED);
    root->right->parent = root;
    leftRotate(&root, root);
    EXPECT_EQ(root->key, 20);
    EXPECT_EQ(root->left->key, 10);
    rightRotate(&root, root);
    EXPECT_EQ(root->key, 10);
    free(root->right);
    free(root);
}

TEST(RBTreeTest, RBUnion) {
    Node* T1 = createNode(10, BLACK);
    Node* T2 = createNode(30, BLACK);
    Node* root = nullptr;
    root = rbUnion(&root, T1, T2, 20);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 20);
    EXPECT_EQ(root->left->key, T1->key);
    EXPECT_EQ(root->right->key, T2->key);
    free(T1);
    free(T2);
    free(root);
}

TEST(RBTreeTest, RBUnionNullTest) {
    Node* T1 = NULL;
    Node* T2 = NULL;
    int x = 1;
    Node* root = nullptr;
    root = rbUnion(&root, T1, T2, x);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 1);
    EXPECT_EQ(root->right, nullptr);
    EXPECT_EQ(root->left, nullptr);
    free(T1);
    free(T2);
    free(root);
}

TEST(RBTreeTest, RBUnionTripleMatch) {
    Node* T1 = createNode(1, BLACK);
    Node* T2 = createNode(1, BLACK);
    int x = 1;
    Node* root = nullptr;
    root = rbUnion(&root, T1, T2, x);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 1);
    EXPECT_EQ(root->right, nullptr);
    EXPECT_EQ(root->left, nullptr);
    free(T1);
    free(T2);
}

TEST(RBTreeTest, MultipleInsertFixups) {
    Node* root = createNode(10, BLACK);
    Node* n1 = createNode(5, RED);
    Node* n2 = createNode(15, RED);
    Node* n3 = createNode(20, RED);

    root->left = n1;
    n1->parent = root;
    root->right = n2;
    n2->parent = root;

    n2->right = n3;
    n3->parent = n2;

    insertFixup(&root, n3);

    EXPECT_EQ(root->right->right->color, RED);
    EXPECT_EQ(root->color, BLACK);
}

TEST(RBTreeTest, InsetingCheck) {
    Node* root = createNode(10, BLACK);
    Node* n1 = createNode(5, RED);
    Node* n2 = createNode(15, RED);

    root->left = n1;
    n1->parent = root;
    root->right = n2;
    n2->parent = root;

    insert(&root, 20);

    EXPECT_EQ(root->right->right->color, RED);
    EXPECT_EQ(root->color, BLACK);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}