#include "pch.h"
#include <gtest/gtest.h>
#include "C:\Users\User\OneDrive\Desktop\ñ++\RB_tree\RB_tree\rbtree.h"

// Google Tests
TEST(RBTreeTest, InsertSingleElement) {
    RBTree tree;
    tree.insert(10);
    testing::internal::CaptureStdout();
    tree.inorder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 \n");
}

TEST(RBTreeTest, InsertMultipleElements) {
    RBTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    testing::internal::CaptureStdout();
    tree.inorder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 30 \n");
}

TEST(RBTreeTest, InsertDuplicateElement) {
    RBTree tree;
    tree.insert(10);
    tree.insert(10);
    testing::internal::CaptureStdout();
    tree.inorder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 10 \n");
}

TEST(RBTreeTest, InsertNegativeNumbers) {
    RBTree tree;
    tree.insert(-10);
    tree.insert(-20);
    tree.insert(-30);
    testing::internal::CaptureStdout();
    tree.inorder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "-30 -20 -10 \n");
}

TEST(RBTreeTest, InsertZero) {
    RBTree tree;
    tree.insert(0);
    testing::internal::CaptureStdout();
    tree.inorder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "0 \n");
}

TEST(RBTreeTest, InsertAscendingOrder) {
    RBTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    testing::internal::CaptureStdout();
    tree.inorder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 30 40 50 \n");
}

TEST(RBTreeTest, InsertDescendingOrder) {
    RBTree tree;
    tree.insert(50);
    tree.insert(40);
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    testing::internal::CaptureStdout();
    tree.inorder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 30 40 50 \n");
}

TEST(RBTreeTest, InsertRandomOrder) {
    RBTree tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(50);
    tree.insert(20);
    tree.insert(40);
    testing::internal::CaptureStdout();
    tree.inorder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 30 40 50 \n");
}

TEST(RBTreeTest, InsertSingleElementAndCheckLevelOrder) {
    RBTree tree;
    tree.insert(10);
    testing::internal::CaptureStdout();
    tree.levelOrder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(RBTreeTest, InsertMultipleElementsAndCheckLevelOrder) {
    RBTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    testing::internal::CaptureStdout();
    tree.levelOrder();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "20 30 10 ");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}