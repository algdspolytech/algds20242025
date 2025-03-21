#include <gtest/gtest.h>

extern "C"
{
    #include "AVLTree.h"
}

class AVLTreeTest : public ::testing::Test {
protected:
    struct Node* root = nullptr;
    
    void SetUp() override {
        root = nullptr;
    }
    
    void TearDown() override {
        freeTree(root);
        root = nullptr;
    }
    
    void freeTree(struct Node* node) {
        if (node != nullptr) {
            freeTree(node->left);
            freeTree(node->right);
            free(node);
        }
    }
    
    bool isBalanced(struct Node* node) {
        if (node == nullptr) return true;
        int balance = getBalance(node);
        return abs(balance) <= 1 && 
               isBalanced(node->left) && 
               isBalanced(node->right);
    }
};

TEST_F(AVLTreeTest, EmptyTree) {
    ASSERT_EQ(search(root, 10), nullptr);
}

TEST_F(AVLTreeTest, InsertSingleElement) {
    root = insert(root, 42);
    ASSERT_NE(search(root, 42), nullptr);
    ASSERT_TRUE(isBalanced(root));
}

TEST_F(AVLTreeTest, InsertDuplicates) {
    root = insert(root, 10);
    root = insert(root, 10); 
    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->right, nullptr);
}

TEST_F(AVLTreeTest, DeleteFromEmpty) {
    root = deleteNode(root, 10);
    ASSERT_EQ(root, nullptr);
}

TEST_F(AVLTreeTest, CheckBalanceAfterInsert) {
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    
    ASSERT_EQ(root->key, 20);
    ASSERT_TRUE(isBalanced(root));
}

TEST_F(AVLTreeTest, DeleteNodeWithTwoChildren) {
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 25);
    
    root = deleteNode(root, 20);
    ASSERT_EQ(root->key, 25);
    ASSERT_TRUE(isBalanced(root));
}

TEST_F(AVLTreeTest, SearchNonExisting) {
    root = insert(root, 100);
    root = insert(root, 200);
    ASSERT_EQ(search(root, 300), nullptr);
}

TEST_F(AVLTreeTest, ComplexDeleteTest) {
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) root = insert(root, v);
    
    for (int v : {20, 30, 50, 70}) {
        root = deleteNode(root, v);
        ASSERT_TRUE(isBalanced(root));
    }
    
    ASSERT_EQ(search(root, 40)->key, 40);
}

TEST_F(AVLTreeTest, CheckTreeHeight) {
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    
    ASSERT_EQ(root->height, 3);
}

TEST_F(AVLTreeTest, CheckAllRotations) {
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    
    root = insert(root, 5);
    root = insert(root, 2);
    
    root = insert(root, 15);
    root = insert(root, 12);
    
    root = insert(root, 35);
    root = insert(root, 33);
    
    ASSERT_TRUE(isBalanced(root));
}
