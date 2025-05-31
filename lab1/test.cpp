#include <gtest/gtest.h>
#include "code.h"

bool tree_check(node *root, int key) {
    return check(&root, key);
}

TEST(TreapTest, InsertInEmptyTest) {
    node *root = nullptr;
    add(&root, 1);
    EXPECT_TRUE(tree_check(root, 1));
    destroy_tree(root);
}

TEST(TreapTest, InsertInNotEmptyTest) {
    node *root = create_node(9);
    root->left = create_node(8);
    root->right = create_node(7);

    root->priority = 9;
    root->left->priority = 8;
    root->right->priority = 7;
    add(&root, 10);
    EXPECT_TRUE(tree_check(root, 10));
    destroy_tree(root);
}

TEST(TreapTest, DeleteTest) {
    node *root = nullptr;
    add(&root, 7);
    del(&root, 7);
    EXPECT_FALSE(tree_check(root, 7));
    destroy_tree(root);
}

TEST(TreapTest, DeleteFromEmptyTest) {
    node *root = nullptr;
    del(&root, 7);
    EXPECT_FALSE(tree_check(root, 7));
    destroy_tree(root);
}

TEST(TreapTest, SplitTest) {
    node *root = nullptr;
    add(&root, 6);
    add(&root, 8);
    node *left = nullptr, *right = nullptr;
    split(root, 7, &left, &right);
    EXPECT_TRUE(tree_check(left, 6));
    EXPECT_FALSE(tree_check(left, 8));
    EXPECT_TRUE(tree_check(right, 8));
    destroy_tree(left);
    destroy_tree(right);
}


TEST(TreapTest, MergeTest) {
    node *left = nullptr, *right = nullptr;
    add(&left, 6);
    add(&right, 7);
    node *merged = merge(left, right);
    EXPECT_TRUE(tree_check(merged, 6));
    EXPECT_TRUE(tree_check(merged, 7));
    destroy_tree(merged);
}

TEST(TreapTest, MergeWithEmptyTest) {
    node *tree = nullptr;
    add(&tree, 6);
    add(&tree, 9);
    node *merged = merge(tree, NULL);
    EXPECT_TRUE(tree_check(merged, 6));
    EXPECT_TRUE(tree_check(merged, 9));
    destroy_tree(merged);
}

TEST(TreapTest, ContainsTest) {
    node *root = nullptr;
    add(&root, 4);
    EXPECT_FALSE(tree_check(root, 44));
    destroy_tree(root);
}

TEST(TreapTest, MultipleInsertDeleteTest) {
    node *root = nullptr;
    add(&root, 34);
    add(&root, 51);
    add(&root, 86);
    EXPECT_TRUE(tree_check(root, 34));
    EXPECT_TRUE(tree_check(root, 51));
    EXPECT_TRUE(tree_check(root, 86));
    del(&root, 51);
    EXPECT_TRUE(tree_check(root, 34));
    EXPECT_FALSE(tree_check(root, 51));
    EXPECT_TRUE(tree_check(root, 86));
    destroy_tree(root);
}

TEST(TreapTest, DuplicateInsertTest) {
    node *root = nullptr;
    add(&root, 4);
    add(&root, 4);
    EXPECT_TRUE(tree_check(root, 4));
    del(&root, 4);
    EXPECT_FALSE(tree_check(root, 4));
    destroy_tree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
