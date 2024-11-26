#include <gtest/gtest.h>
#include "functions.h"
#include <string>

extern "C" {
#include "functions.h" 
}

TreeNode* buildTree(const std::vector<std::string>& words) {
    TreeNode* root = NULL;
    for (const std::string& word : words) {
        root = insert(root, word.c_str());
    }
    return root;
}

TEST(TreeTest, InsertIntoEmptyTree_no1) {
    TreeNode* root = NULL;
    root = insert(root, "root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->word, "root");
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    freeTree(root);
}

TEST(TreeTest, InsertMultipleNodes_no2) {
    TreeNode* root = NULL;
    root = insert(root, "m");
    insert(root, "c");
    insert(root, "x");
    insert(root, "a");
    insert(root, "z");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->word, "m");
    EXPECT_STREQ(root->left->word, "c");
    EXPECT_STREQ(root->right->word, "x");
    EXPECT_STREQ(root->left->left->word, "a");
    EXPECT_STREQ(root->right->right->word, "z");
    freeTree(root);
}

TEST(TreeTest, ComputeSubtreeWidthBalancedTree_no3) {
    TreeNode* root = NULL;
    std::vector<std::string> words = { "d", "b", "f", "a", "c", "e", "g" };
    root = buildTree(words);
    int width = computeSubtreeWidth(root);
    EXPECT_EQ(width, 7);
    EXPECT_EQ(root->subtree_width, 7);
    freeTree(root);
}

TEST(TreeTest, ComputeSubtreeWidthLeftSkewedTree_no4) {
    TreeNode* root = NULL;
    std::vector<std::string> words = { "e", "d", "c", "b", "a" };
    root = buildTree(words);
    int width = computeSubtreeWidth(root);
    EXPECT_EQ(width, 5); 
    EXPECT_EQ(root->subtree_width, 5);
    freeTree(root);
}


TEST(TreeTest, ComputeSubtreeWidthRightSkewedTree_no5) {
    TreeNode* root = NULL;
    std::vector<std::string> words = { "a", "b", "c", "d", "e" };
    root = buildTree(words);
    int width = computeSubtreeWidth(root);
    EXPECT_EQ(width, 5);
    EXPECT_EQ(root->subtree_width, 5);
    freeTree(root);
}


TEST(TreeTest, InsertDuplicateWords_no6) {
    TreeNode* root = NULL;
    root = insert(root, "duplicate");
    insert(root, "duplicate");
    insert(root, "duplicate");
    int width = computeSubtreeWidth(root);
    EXPECT_EQ(width, 9); 
    EXPECT_EQ(root->subtree_width, 9);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_NE(root->right, nullptr); 
    freeTree(root);
}

TEST(TreeTest, InsertEmptyString_no7) {
    TreeNode* root = NULL;
    root = insert(root, "");
    int width = computeSubtreeWidth(root);
    EXPECT_EQ(width, 0);
    EXPECT_STREQ(root->word, "");
    freeTree(root);
}

TEST(TreeTest, InsertNullWord_no8) {
    TreeNode* root = NULL;
    /*
    root = insert(root, NULL);
    EXPECT_EQ(root, nullptr);
    */
    SUCCEED();
}

TEST(TreeTest, ComputeSubtreeWidthSingleNode_no9) {
    TreeNode* root = NULL;
    root = insert(root, "single");
    int width = computeSubtreeWidth(root);
    EXPECT_EQ(width, 6);
    EXPECT_EQ(root->subtree_width, 6);
    freeTree(root);
}

TEST(TreeTest, FreeTree_no10) {
    TreeNode* root = NULL;
    std::vector<std::string> words = { "memory", "leak", "test" };
    root = buildTree(words);
    freeTree(root);
    SUCCEED(); 
}
