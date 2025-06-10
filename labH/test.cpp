//
// Created by frama on 14.03.2025.
//

#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>

extern "C" {
    #include "treap.h"
}

TEST(TreapTest, InsertAndSearch) {
    Node* root = NULL;
    root = insert(root, 10);
    ASSERT_NE(search(root, 10), nullptr);
    ASSERT_EQ(search(root, 20), nullptr);
}

TEST(TreapTest, DeleteNode) {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = deleteNode(root, 10);
    EXPECT_EQ(search(root, 10), nullptr);
    EXPECT_NE(search(root, 20), nullptr);
}

TEST(TreapTest, TreapPropertyAfterInsert) {
    Node* root = NULL;
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    EXPECT_TRUE(isTreap(root));
}

TEST(TreapTest, TreapPropertyAfterDelete) {
    Node* root = NULL;
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = deleteNode(root, 3);
    EXPECT_TRUE(isTreap(root));
}

TEST(TreapTest, InsertDuplicate) {
    Node* root = NULL;
    root = insert(root, 5);
    Node* newRoot = insert(root, 5);
    EXPECT_EQ(root, newRoot);
}

TEST(TreapTest, DeleteNonExistent) {
    Node* root = NULL;
    root = insert(root, 5);
    Node* newRoot = deleteNode(root, 10);
    EXPECT_EQ(root, newRoot);
}

TEST(TreapTest, MultipleOperations) {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = deleteNode(root, 20);
    root = deleteNode(root, 30);
    EXPECT_NE(search(root, 50), nullptr);
    EXPECT_EQ(search(root, 20), nullptr);
    EXPECT_TRUE(isTreap(root));
}

TEST(TreapTest, DeleteRoot) {
    Node* root = NULL;
    root = insert(root, 100);
    root = deleteNode(root, 100);
    EXPECT_EQ(root, nullptr);
}

TEST(TreapTest, LargeTree) {
    Node* root = NULL;
    for (int i = 0; i < 100; ++i) {
        root = insert(root, i);
    }
    EXPECT_TRUE(isTreap(root));
    for (int i = 0; i < 100; ++i) {
        root = deleteNode(root, i);
        EXPECT_TRUE(isTreap(root));
    }
    EXPECT_EQ(root, nullptr);
}

TEST(TreapTest, RandomInsertDelete) {
    Node* root = NULL;
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 6);
    root = deleteNode(root, 4);
    EXPECT_EQ(search(root, 4), nullptr);
    EXPECT_NE(search(root, 6), nullptr);
    EXPECT_TRUE(isTreap(root));
}
