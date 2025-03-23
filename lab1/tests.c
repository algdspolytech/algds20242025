#include <gtest/gtest.h>
#include "splay_tree.h"

TEST(SplayTreeTest, InsertToEmptyTree_no1) {
    Node* root = NULL;
    root = insert(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 10);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    free_tree(root);
}

TEST(SplayTreeTest, InsertExistingKey_no2) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 10);

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 10);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->key, 20);
    EXPECT_EQ(root->left, nullptr);
    free_tree(root);
}

TEST(SplayTreeTest, SearchExistingKey_no3) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);

    int found = 0;
    root = search(root, 20, &found);
    EXPECT_TRUE(found);
    EXPECT_EQ(root->key, 20);
    free_tree(root);
}

TEST(SplayTreeTest, SearchNonExistingKey_no4) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);

    int found = 0;
    root = search(root, 15, &found);
    EXPECT_FALSE(found);
    free_tree(root);
}

TEST(SplayTreeTest, DeleteExistingKey_no5) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);

    root = delete(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 5);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->key, 20);
    EXPECT_EQ(root->left, nullptr);
    free_tree(root);
}

TEST(SplayTreeTest, DeleteNonExistingKey_no6) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);

    Node* newRoot = delete(root, 30);
    ASSERT_EQ(newRoot, root);
    free_tree(newRoot);
}

TEST(SplayTreeTest, MultipleInsertions_no7) {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 20);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->key, 30);
    ASSERT_NE(root->right->right, nullptr);
    EXPECT_EQ(root->right->right->key, 50);
    ASSERT_NE(root->right->right->right, nullptr);
    EXPECT_EQ(root->right->right->right->key, 70);
    free_tree(root);
}

TEST(SplayTreeTest, SplayAfterSearch_no8) {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);

    int found = 0;
    root = search(root, 30, &found);
    EXPECT_TRUE(found);
    EXPECT_EQ(root->key, 30);
    ASSERT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->key, 20);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->key, 50);
    ASSERT_NE(root->right->right, nullptr);
    EXPECT_EQ(root->right->right->key, 70);
    free_tree(root);
}

TEST(SplayTreeTest, DeleteRootWithSubtrees_no9) {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    root = delete(root, 50);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 40);
    ASSERT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->key, 30);
    ASSERT_NE(root->left->left, nullptr);
    EXPECT_EQ(root->left->left->key, 20);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->key, 70);
    free_tree(root);
}

TEST(SplayTreeTest, InsertAscendingOrder_no10) {
    Node* root = NULL;
    for (int i = 0; i < 5; ++i) {
        root = insert(root, i);
    }
    EXPECT_EQ(root->key, 4);
    ASSERT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->key, 3);
    ASSERT_NE(root->left->left, nullptr);
    EXPECT_EQ(root->left->left->key, 2);
    free_tree(root);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}