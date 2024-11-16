#include "LabE_lib.h"

#include <gtest/gtest.h>

TEST(CreateNode_ValidInput_NodeCreated_0) {
    TreeNode* node = create_node(10);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, 10);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    free_tree(node);
}

TEST(CreateNode_NegativeValue_NodeCreated_1) {
    TreeNode* node = create_node(-5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, -5);
    free_tree(node);
}

TEST(AddNode_EmptyTree_NodeAdded_2) {
    TreeNode* root = nullptr;
    root = add_node(root, 15);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 15);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    free_tree(root);
}

TEST(AddNode_LessThanRoot_LeftChildAdded_3) {
    TreeNode* root = create_node(20);
    add_node(root, 10);
    ASSERT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right, nullptr);
    free_tree(root);
}

TEST(AddNode_GreaterThanRoot_RightChildAdded_4) {
    TreeNode* root = create_node(20);
    add_node(root, 30);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->value, 30);
    EXPECT_EQ(root->left, nullptr);
    free_tree(root);
}

TEST(InitializeTree_SingleElement_TreeCreated_5) {
    int elements[] = { 25 };
    TreeNode* root = initialize_tree(elements, 1);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 25);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    free_tree(root);
}

TEST(InitializeTree_MultipleElements_TreeCreated_6) {
    int elements[] = { 15, 10, 20, 5, 12, 18, 25 };
    TreeNode* root = initialize_tree(elements, 7);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 15);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 20);
    free_tree(root);
}

TEST(AddNode_DuplicateValue_NodeIgnored_7) {
    TreeNode* root = create_node(15);
    add_node(root, 10);
    add_node(root, 15); 
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->value, 15); 
    free_tree(root);
}

TEST(InitializeTree_EmptyArray_TreeNull_8) {
    TreeNode* root = initialize_tree(nullptr, 0);
    EXPECT_EQ(root, nullptr);
}

TEST(FreeTree_SingleNode_TreeFreed_9) {
    TreeNode* root = create_node(10);
    free_tree(root);
    EXPECT_TRUE(true);
}

TEST(FreeTree_MultipleNodes_TreeFreed_10) {
    int elements[] = { 15, 10, 20 };
    TreeNode* root = initialize_tree(elements, 3);
    free_tree(root);
    EXPECT_TRUE(true);
}

TEST(AddNode_MultipleLevels_TreeBalanced_11) {
    TreeNode* root = create_node(15);
    add_node(root, 10);
    add_node(root, 20);
    add_node(root, 5);
    add_node(root, 12);
    add_node(root, 18);
    add_node(root, 25);
    ASSERT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->value, 10);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->value, 20);
    free_tree(root);
}

TEST(CreateNode_MaxIntValue_NodeCreated_12) {
    TreeNode* node = create_node(INT_MAX);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, INT_MAX);
    free_tree(node);
}

TEST(CreateNode_MinIntValue_NodeCreated_13) {
    TreeNode* node = create_node(INT_MIN);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->value, INT_MIN);
    free_tree(node);
}

TEST(InitializeTree_UnorderedElements_TreeCreated_14) {
    int elements[] = { 25, 5, 20, 15, 10 };
    TreeNode* root = initialize_tree(elements, 5);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 25);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->left->right->value, 20);
    free_tree(root);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
