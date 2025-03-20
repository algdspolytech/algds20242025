#include <gtest/gtest.h>

// #include "CartesianTree.h"
extern "C" {
#include "CartesianTree.h"
}

bool tree_contains(node *root, int key) {
    return contains(&root, key);
}

TEST(TreapTest, InsertInEmptyTest) {
    node *root = nullptr;
    insert(&root, 10);
    EXPECT_TRUE(tree_contains(root, 10));
    destroy_tree(root);
}

TEST(TreapTest, InsertInNotEmptyTest) {
    node *root = create_node(4);
    root->left = create_node(3);
    root->right = create_node(2);

    root->priority = 10;
    root->left->priority = 3;
    root->right->priority = 2;
    insert(&root, 10);
    EXPECT_TRUE(tree_contains(root, 10));
    destroy_tree(root);
}

TEST(TreapTest, EraseTest) {
    node *root = nullptr;
    insert(&root, 10);
    erase(&root, 10);
    EXPECT_FALSE(tree_contains(root, 10));
    destroy_tree(root);
}

TEST(TreapTest, EraseаFromEmptyTest) {
    node *root = nullptr;
    erase(&root, 10);
    EXPECT_FALSE(tree_contains(root, 10));
    destroy_tree(root);
}

TEST(TreapTest, SplitTest) {
    node *root = nullptr;
    insert(&root, 10);
    insert(&root, 20);
    node *left = nullptr, *right = nullptr;
    split(root, 15, &left, &right);
    EXPECT_TRUE(tree_contains(left, 10));
    EXPECT_FALSE(tree_contains(left, 20));
    EXPECT_TRUE(tree_contains(right, 20));
    destroy_tree(left);
    destroy_tree(right);
}


TEST(TreapTest, MergeTest) {
    node *left = nullptr, *right = nullptr;
    insert(&left, 5);
    insert(&right, 15);
    node *merged = merge(left, right);
    EXPECT_TRUE(tree_contains(merged, 5));
    EXPECT_TRUE(tree_contains(merged, 15));
    destroy_tree(merged);
}

TEST(TreapTest, MergeWithEmptyTest) {
    node *tree = nullptr;
    insert(&tree, 5);
    insert(&tree, 15);
    node *merged = merge(tree, NULL);
    EXPECT_TRUE(tree_contains(merged, 5));
    EXPECT_TRUE(tree_contains(merged, 15));
    destroy_tree(merged);
}

TEST(TreapTest, ContainsTest) {
    node *root = nullptr;
    insert(&root, 10);
    EXPECT_FALSE(tree_contains(root, 20));
    destroy_tree(root);
}

TEST(TreapTest, MultipleInsertEraseTest) {
    node *root = nullptr;
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    EXPECT_TRUE(tree_contains(root, 10));
    EXPECT_TRUE(tree_contains(root, 20));
    EXPECT_TRUE(tree_contains(root, 30));
    erase(&root, 20);
    EXPECT_FALSE(tree_contains(root, 20));
    EXPECT_TRUE(tree_contains(root, 10));
    EXPECT_TRUE(tree_contains(root, 30));
    destroy_tree(root);
}

TEST(TreapTest, DuplicateInsertTest) {
    node *root = nullptr;
    insert(&root, 10);
    insert(&root, 10);
    EXPECT_TRUE(tree_contains(root, 10));
    erase(&root, 10);
    EXPECT_FALSE(tree_contains(root, 10));
    destroy_tree(root);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
