#include <gtest/gtest.h>
#include "treap.h"
#include <iostream>


TEST(TreapTest, CreateNode) {
    TreapNode* node = treap_create_node(10, 50);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->key, 10);
    EXPECT_EQ(node->priority, 50);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    treap_destroy(node);
}


TEST(TreapTest, Insert) {
    TreapNode* root = nullptr;
    root = treap_insert(root, 20, 80);
    root = treap_insert(root, 10, 90);
    root = treap_insert(root, 30, 70);

    EXPECT_TRUE(treap_search(root, 10));
    EXPECT_TRUE(treap_search(root, 20));
    EXPECT_TRUE(treap_search(root, 30));
    EXPECT_FALSE(treap_search(root, 40));

    treap_destroy(root);
}

TEST(TreapTest, Delete) {
    TreapNode* root = nullptr;
    root = treap_insert(root, 15, 60);
    root = treap_insert(root, 25, 70);
    root = treap_delete(root, 15);

    EXPECT_FALSE(treap_search(root, 15));
    EXPECT_TRUE(treap_search(root, 25));

    treap_destroy(root);
}

TEST(TreapTest, Merge) {
    TreapNode* left = treap_create_node(10, 50);
    TreapNode* right = treap_create_node(20, 40);

    TreapNode* merged = treap_merge(left, right);

    EXPECT_TRUE(treap_search(merged, 10));
    EXPECT_TRUE(treap_search(merged, 20));

    treap_destroy(merged);
}

TEST(TreapTest, Split) {
    TreapNode* root = nullptr;
    root = treap_insert(root, 30, 60);
    root = treap_insert(root, 20, 70);

    TreapNode* left = nullptr, * right = nullptr;
    treap_split(root, 25, &left, &right);

    EXPECT_TRUE(treap_search(left, 20));
    EXPECT_FALSE(treap_search(left, 30));
    EXPECT_TRUE(treap_search(right, 30));

    treap_destroy(left);
    treap_destroy(right);
}

TEST(TreapTest, IsValid) {
    TreapNode* root = nullptr;
    root = treap_insert(root, 50, 90);
    root = treap_insert(root, 40, 80);
    root = treap_insert(root, 60, 70);

    EXPECT_TRUE(treap_is_valid(root));

    treap_destroy(root);
}

TEST(TreapTest, Search) {
    TreapNode* root = nullptr;
    root = treap_insert(root, 45, 85);

    EXPECT_TRUE(treap_search(root, 45));
    EXPECT_FALSE(treap_search(root, 55));

    treap_destroy(root);
}

TEST(TreapTest, Size) {
    TreapNode* root = nullptr;
    root = treap_insert(root, 10, 50);
    root = treap_insert(root, 20, 60);

    EXPECT_EQ(treap_size(root), 2);

    treap_destroy(root);
}

TEST(TreapTest, MergeWithEmpty) {
    TreapNode* left = nullptr;
    TreapNode* right = treap_create_node(10, 40);

    TreapNode* merged = treap_merge(left, right);

    EXPECT_TRUE(treap_search(merged, 10));

    treap_destroy(merged);
}

TEST(TreapTest, DeleteFromEmpty) {
    TreapNode* root = nullptr;
    root = treap_delete(root, 10);

    EXPECT_EQ(root, nullptr);
}

TEST(TreapTest, InsertDuplicate) {
    TreapNode* root = nullptr;
    root = treap_insert(root, 30, 70);
    root = treap_insert(root, 30, 80);

    EXPECT_EQ(treap_size(root), 1);

    treap_destroy(root);
}

TEST(TreapTest, Destroy) {
    TreapNode* root = nullptr;
    root = treap_insert(root, 100, 99);

    treap_destroy(root);

    EXPECT_EQ(root, nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "Run Tests" << std::endl;
    return RUN_ALL_TESTS();
}
