#include "gtest/gtest.h"

extern "C" {
#include "lab.h"
}

TEST(labETests, getNumWidth_positive) {
    ASSERT_EQ(get_num_width(12), 2);
}

TEST(labETests, getNumWidth_negative) {
    ASSERT_EQ(get_num_width(-12), 3);
}

TEST(labETests, getNumWidth_zero) {
    ASSERT_EQ(get_num_width(0), 1);
}

TEST(WidthTest, CountWidthSingleNode) {
    tree *node = create_tree_node(42);
    unsigned width = count_widths(node);
    EXPECT_EQ(width, 2); // Ширина числа 42
    EXPECT_EQ(node->width, 2);
    free(node);
}

// Тест на вычисление общей ширины для дерева
TEST(WidthTest, CountWidthTree) {
    tree *root = create_tree_node(10);
    root->left = create_tree_node(5);
    root->right = create_tree_node(20);

    unsigned totalWidth = count_widths(root);
    EXPECT_EQ(totalWidth, 5); // Ширина 10 + 5 + 20 = 5
    EXPECT_EQ(root->width, 5);
    EXPECT_EQ(root->left->width, 1);
    EXPECT_EQ(root->right->width, 2);
    delete_tree(root);
}

TEST(WidthTest, CountWidthEmptyTree) {
    tree *root = nullptr;
    unsigned totalWidth = count_widths(root);
    EXPECT_EQ(totalWidth, 0);
}

TEST(WidthTest, GetNumWidthZero) {
    EXPECT_EQ(get_num_width(0), 1);
}

TEST(WidthTest, CountWidthLargeNumber) {
    tree *node = create_tree_node(123456);
    unsigned width = count_widths(node);
    EXPECT_EQ(width, 6);
    free(node);
}

TEST(WidthTest, CountWidthMixedNumbers) {
    tree *root = create_tree_node(0);
    root->left = create_tree_node(-1);
    root->right = create_tree_node(12);

    unsigned totalWidth = count_widths(root);
    EXPECT_EQ(totalWidth, 5);
    delete_tree(root);
}

TEST(WidthTest, CountWidthMultiLevelTree) {
    tree *root = create_tree_node(10);
    root->left = create_tree_node(5);
    root->right = create_tree_node(20);
    root->left->left = create_tree_node(3);
    root->left->right = create_tree_node(7);

    unsigned totalWidth = count_widths(root);
    EXPECT_EQ(totalWidth, 7); // Ширина: 10 + 5 + 20 + 3 + 7 = 10

    delete_tree(root);
}
