#include "pch.h"
#include <iostream>
#include <sstream>
extern "C" {
#include "../Algosi4/main.h"
}
TEST(NodeTest, CreateNodeTest_no1) {
    int testData = 42;
    Node* node = createNode(testData);

    ASSERT_NE(node, nullptr);

    EXPECT_EQ(node->data, testData);
    EXPECT_EQ(node->count, 1);
    EXPECT_EQ(node->left, nullptr);
    EXPECT_EQ(node->right, nullptr);
    EXPECT_EQ(node->parent, nullptr);

    free(node);
}
TEST(TreeTest, CreateTree_no2) {

    Tree* tree = createTree();

    ASSERT_NE(tree, nullptr);

    ASSERT_EQ(tree->root, nullptr);

    free(tree);
}
class UpdateCountTest : public ::testing::Test {
protected:
    Node* root;
    Node* leftChild;
    Node* rightChild;

    void SetUp() override {
        root = new Node{ 0, 0, nullptr, nullptr, nullptr };
        leftChild = new Node{ 1, 0, nullptr, nullptr, root };
        rightChild = new Node{ 2, 0, nullptr, nullptr, root };

        root->left = leftChild;
        root->right = rightChild;
    }

    void TearDown() override {
        delete leftChild;
        delete rightChild;
        delete root;
    }
};

TEST_F(UpdateCountTest, UpdateCount_OneChild_no3) {
    leftChild->count = 1;
    updateCount(leftChild);
    EXPECT_EQ(root->count, 2);
    EXPECT_EQ(leftChild->count, 1);
}

TEST_F(UpdateCountTest, UpdateCount_TwoChildren_no4) {
    leftChild->count = 1;
    rightChild->count = 2;

    updateCount(root);

    EXPECT_EQ(root->count, 4);
    EXPECT_EQ(leftChild->count, 1);
    EXPECT_EQ(rightChild->count, 2);
}

TEST_F(UpdateCountTest, UpdateCount_NoChildren_no5) {
    Node* singleNode = new Node{ 3, 0, nullptr, nullptr, nullptr };

    updateCount(singleNode);

    EXPECT_EQ(singleNode->count, 1);
    delete singleNode;
}

class BinaryTreeTest : public ::testing::Test {
protected:
    Tree tree;

    void SetUp() override { tree.root = NULL; }

    void TearDown() override {}
};

TEST_F(BinaryTreeTest, InsertIntoEmptyTree_no6) {
    insert(&tree, 10);
    ASSERT_NE(tree.root, nullptr);
    ASSERT_EQ(tree.root->data, 10);
    ASSERT_EQ(tree.root->count, 1);
    ASSERT_EQ(tree.root->left, nullptr);
    ASSERT_EQ(tree.root->right, nullptr);
    ASSERT_EQ(tree.root->parent, nullptr);
}

TEST_F(BinaryTreeTest, InsertMultipleElements_no7) {
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);

    ASSERT_NE(tree.root, nullptr);
    ASSERT_EQ(tree.root->data, 10);
    ASSERT_NE(tree.root->left, nullptr);
    ASSERT_NE(tree.root->right, nullptr);
    ASSERT_EQ(tree.root->left->data, 20);
    ASSERT_EQ(tree.root->right->data, 5);
    ASSERT_EQ(tree.root->left->parent, tree.root);
    ASSERT_EQ(tree.root->right->parent, tree.root);
}

TEST_F(BinaryTreeTest, CheckCountsAfterInsertions_no8) {
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);

    updateCount(tree.root);

    ASSERT_EQ(tree.root->count, 3);
    ASSERT_EQ(tree.root->left->count, 1);
    ASSERT_EQ(tree.root->right->count, 1);
}

TEST_F(BinaryTreeTest, InsertElementIntoSmallerSubtree_no9) {
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);
    insert(&tree, 15);
    insert(&tree, 52);
    ASSERT_EQ(tree.root->right->left->data, 52);
    ASSERT_EQ(tree.root->left->count, 2);
    ASSERT_EQ(tree.root->right->count, 2);
}

class DeleteTest : public ::testing::Test {
protected:
    Tree* tree;

    void SetUp() override {
        tree = new Tree();
        tree->root = nullptr;
    }

    void TearDown() override { delete tree; }
};

TEST_F(DeleteTest, DeleteLonelyLeafNode_no10) {
    tree->root = new Node{ 10, 1, nullptr, nullptr, nullptr };
    tree->root->left = new Node{ 5, 1, nullptr, nullptr, tree->root };
    tree->root->right = new Node{ 15, 1, nullptr, nullptr, tree->root };
    tree->root->left->left = new Node{ 3, 1, nullptr, nullptr, tree->root->left };

    deleteNode(tree);

    ASSERT_NE(tree->root->left->left, nullptr);
}

TEST_F(DeleteTest, DeleteRightLeafNode_no11) {
    tree->root = new Node{ 10, 1, nullptr, nullptr, nullptr };
    tree->root->left = new Node{ 5, 1, nullptr, nullptr, tree->root };
    tree->root->right = new Node{ 15, 1, nullptr, nullptr, tree->root };

    deleteNode(tree);
    ASSERT_EQ(tree->root->left->count, 1);
    ASSERT_EQ(tree->root->count, 2);
}