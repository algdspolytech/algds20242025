#include <cstdio>
#include <stdlib.h>
#include <tree.c>
#include <gtest/gtest.h>

TEST(TreeTest, InitNode_n1) {
    TreeNode* node = initNode(10);
    EXPECT_EQ(node->data, 10);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free(node);
}

TEST(TreeTest, AddNodeToEmptyTree_n2) {
    TreeNode* root = nullptr;
    addNode(&root,1);
    EXPECT_EQ(root->data, 1);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    free(root);
}

TEST(TreeTest, AddNodeToLeft_n3) {
    TreeNode* root = initNode(1);
    addNode(&root, 0);
    EXPECT_EQ(root->left->data, 0);
    freeTree(root);
}

TEST(TreeTest, AddNodeToRight_n4) {
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    EXPECT_EQ(root->right->data, 2);
    freeTree(root);
}

TEST(TreeTest, AddNodeSeveralNodes_n5) {
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    addNode(&root, 0);
    addNode(&root, -1);
    EXPECT_EQ(root->right->data, 2);
    EXPECT_EQ(root->left->data, 0);
    EXPECT_EQ(root->left->left->data, -1);
    freeTree(root);
}

TEST(TreeTest, AddNodeEqualNode_n6) {
    TreeNode* root = initNode(1);
    addNode(&root, 1);
    EXPECT_EQ(root->right->data, 1);
    freeTree(root);
}

TEST(TreeTest, DeleteSubTreeRootIsNull_n7) {
    TreeNode* root = nullptr;
    EXPECT_FALSE(deleteSubtree(&root,1));
    freeTree(root);
}

TEST(TreeTest, DeleteSubTreeNotNodeIsExsist_n8) {
    TreeNode* root = initNode(2);
    EXPECT_FALSE(deleteSubtree(&root,1));
    freeTree(root);
}

TEST(TreeTest, DeleteSubTreeNormalCase_n9) {
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    addNode(&root, 0);
    addNode(&root, -1);
    EXPECT_TRUE(deleteSubtree(&root,0));
    freeTree(root);
}

TEST(TreeTest, DeleteSubTreeDeleteSeveral_n10) {
    TreeNode* root = initNode(1);
    addNode(&root, 2);
    addNode(&root, 0);
    addNode(&root, -1);
    EXPECT_TRUE(deleteSubtree(&root,0));
    EXPECT_FALSE(deleteSubtree(&root,-1));
    freeTree(root);
}
