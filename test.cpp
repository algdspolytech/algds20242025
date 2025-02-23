#include "pch.h"
#include <gtest/gtest.h>
#include "binary_tree.h"


bool search(TreeNode* root, int value) {
    if (root == NULL) return false;
    if (root->value == value) return true;
    return search(root->left, value) || search(root->right, value);
}


TEST(BinaryTreeTest, InsertIntoEmptyTree) {
    TreeNode* root = NULL;
    insert(&root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->node_count, 1);
    free_tree(root);
}


TEST(BinaryTreeTest, InsertMultipleNodes) {
    TreeNode* root = NULL;
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);

    EXPECT_EQ(root->node_count, 3);
    EXPECT_TRUE(search(root, 10));
    EXPECT_TRUE(search(root, 20));
    EXPECT_TRUE(search(root, 30));

    free_tree(root);
}


TEST(BinaryTreeTest, DeleteLeafNode) {
    TreeNode* root = NULL;
    insert(&root, 10);
    insert(&root, 20);

    delete_node(&root, 20);
    EXPECT_FALSE(search(root, 20));
    EXPECT_EQ(root->node_count, 1);

    free_tree(root);
}


TEST(BinaryTreeTest, DeleteRootNode) {
    TreeNode* root = NULL;
    insert(&root, 10);

    delete_node(&root, 10);
    EXPECT_EQ(root, nullptr);

    free_tree(root);
}


TEST(BinaryTreeTest, DeleteNodeWithTwoChildren) {
    TreeNode* root = NULL;
    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);

    delete_node(&root, 10);
    EXPECT_FALSE(search(root, 10));
    EXPECT_EQ(root->node_count, 2);

    free_tree(root);
}


TEST(BinaryTreeTest, InsertBalancedTree) {
    TreeNode* root = NULL;
    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 12);
    insert(&root, 17);

    EXPECT_EQ(root->node_count, 7);

    free_tree(root);
}


TEST(BinaryTreeTest, DeleteNonExistentNode) {
    TreeNode* root = NULL;
    insert(&root, 10);
    delete_node(&root, 20);
    EXPECT_EQ(root->node_count, 1);

    free_tree(root);
}


TEST(BinaryTreeTest, ComplexOperations) {
    TreeNode* root = NULL;
    for (int i = 1; i <= 15; ++i) {
        insert(&root, i);
    }
    EXPECT_EQ(root->node_count, 15);

    delete_node(&root, 10);
    delete_node(&root, 5);
    EXPECT_EQ(root->node_count, 13);
    EXPECT_FALSE(search(root, 10));
    EXPECT_FALSE(search(root, 5));

    free_tree(root);
}


TEST(BinaryTreeTest, InsertAndDeleteAll) {
    TreeNode* root = NULL;
    insert(&root, 10);
    insert(&root, 20);

    delete_node(&root, 10);
    delete_node(&root, 20);
    EXPECT_EQ(root, nullptr);

    free_tree(root);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}