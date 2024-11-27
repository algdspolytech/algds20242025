#include <gtest/gtest.h>
extern "C" {
#include "bst.h"
}

TEST(TreeTest, CreateNode) {
    struct Node* node = create_node(5);
    EXPECT_TRUE(node != NULL);
    EXPECT_EQ(node->value, 5);
    clear_tree(&node);
}

TEST(TreeTest, AddToEmpty) {
    struct Node* root = NULL;
    root = add_to_tree(root, 10);
    EXPECT_TRUE(root != NULL);
    EXPECT_EQ(root->value, 10);
    clear_tree(&root);
}

TEST(TreeTest, AddElements) {
    struct Node* root = NULL;
    root = add_to_tree(root, 5);
    root = add_to_tree(root, 3);
    root = add_to_tree(root, 7);

    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->left->value, 3);
    EXPECT_EQ(root->right->value, 7);
    clear_tree(&root);
}

TEST(TreeTest, FindInEmpty) {
    struct Node* root = NULL;
    EXPECT_EQ(find_kth_smallest(root, 1), -1);
}

TEST(TreeTest, FindInSingle) {
    struct Node* root = NULL;
    root = add_to_tree(root, 5);
    EXPECT_EQ(find_kth_smallest(root, 1), 5);
    clear_tree(&root);
}

TEST(TreeTest, FindKth) {
    struct Node* root = NULL;
    root = add_to_tree(root, 5);
    root = add_to_tree(root, 3);
    root = add_to_tree(root, 7);

    EXPECT_EQ(find_kth_smallest(root, 2), 5);
    clear_tree(&root);
}

TEST(TreeTest, FindNonexistent) {
    struct Node* root = NULL;
    root = add_to_tree(root, 5);
    EXPECT_EQ(find_kth_smallest(root, 2), -1);
    clear_tree(&root);
}

TEST(TreeTest, CountNodes) {
    struct Node* root = NULL;
    root = add_to_tree(root, 5);
    root = add_to_tree(root, 3);
    root = add_to_tree(root, 7);

    EXPECT_EQ(root->count, 3);
    clear_tree(&root);
}

TEST(TreeTest, PrintEven) {
    struct Node* root = NULL;
    root = add_to_tree(root, 5);
    root = add_to_tree(root, 2);
    root = add_to_tree(root, 4);

    testing::internal::CaptureStdout();
    print_if_kth_even(root, 2);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "2 \n");
    clear_tree(&root);
}

TEST(TreeTest, PrintOdd) {
    struct Node* root = NULL;
    root = add_to_tree(root, 5);
    root = add_to_tree(root, 3);
    root = add_to_tree(root, 7);

    testing::internal::CaptureStdout();
    print_if_kth_even(root, 2);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "");
    clear_tree(&root);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}