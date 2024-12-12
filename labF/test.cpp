#include "pch.h"
#include <iostream>
#include <sstream>
extern "C" {
#include "../algosi4/header.h"
}

class NewNodeTest : public ::testing::Test {
protected:
	void SetUp() override {}

	void TearDown() override {}
};

TEST_F(NewNodeTest, CreateNode_ValidData_no1) {
	int data = 5;
	Node* node = newNode(data);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->data, data);
	EXPECT_EQ(node->left, nullptr);
	EXPECT_EQ(node->right, nullptr);
	EXPECT_EQ(node->count, 1);

	free(node);
}

TEST_F(NewNodeTest, CreateMultipleNodes_no2) {
	Node* node1 = newNode(1);
	Node* node2 = newNode(2);

	ASSERT_NE(node1, nullptr);
	ASSERT_NE(node2, nullptr);

	EXPECT_EQ(node1->data, 1);
	EXPECT_EQ(node2->data, 2);

	free(node1);
	free(node2);
}

TEST_F(NewNodeTest, MemoryAllocation_no3) {
	Node* node = newNode(INT_MAX);
	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->data, INT_MAX);
	EXPECT_EQ(node->count, 1);

	free(node);
}

class BSTTest : public ::testing::Test {
protected:
	Node* root;

	void SetUp() override { root = nullptr; }

	void TearDown() override {}
};

TEST_F(BSTTest, InsertSingleNode_no4) {
	root = insert(root, 10);
	ASSERT_NE(root, nullptr);
	ASSERT_EQ(root->data, 10);
	ASSERT_EQ(root->count, 1);
}

TEST_F(BSTTest, InsertMultipleNodes_no5) {
	root = insert(root, 10);
	root = insert(root, 5);
	root = insert(root, 15);

	ASSERT_EQ(root->data, 10);
	ASSERT_EQ(root->count, 3);
	ASSERT_NE(root->left, nullptr);
	ASSERT_NE(root->right, nullptr);
	ASSERT_EQ(root->left->data, 5);
	ASSERT_EQ(root->right->data, 15);
	ASSERT_EQ(root->left->count, 1);
	ASSERT_EQ(root->right->count, 1);
}

TEST_F(BSTTest, InsertDuplicateNodes_no6) {
	root = insert(root, 10);
	root = insert(root, 10);

	ASSERT_EQ(root->count, 2);
}

TEST_F(BSTTest, InsertOrderedNodes_no7) {
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);

	ASSERT_EQ(root->data, 10);
	ASSERT_EQ(root->count, 3);
	ASSERT_NE(root->right, nullptr);
	ASSERT_EQ(root->right->data, 20);
	ASSERT_NE(root->right->right, nullptr);
	ASSERT_EQ(root->right->right->data, 30);
}

class FKSETest : public ::testing::Test {
protected:
	void SetUp() override {}

	void TearDown() override {}
};

TEST_F(FKSETest, FindMinimumElement_no8) {
	Node* root = nullptr;
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 2);
	root = insert(root, 4);
	root = insert(root, 5);
	EXPECT_EQ(findKthSmallest(root, 1)->data, 1);
}

TEST_F(FKSETest, FindRoot_no9) {
	Node* root = nullptr;
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 2);
	root = insert(root, 4);
	root = insert(root, 5);
	EXPECT_EQ(findKthSmallest(root, 3)->data, 3);
}

TEST_F(FKSETest, FindNull_no10) { EXPECT_EQ(findKthSmallest(nullptr, 1), nullptr); }

TEST_F(FKSETest, FindKMoreThanN_no11) {
	Node* root = nullptr;
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 2);
	EXPECT_EQ(findKthSmallest(root, 6), nullptr);
}

TEST(KIsEvenTest, EvenNumber_no12) {
	Node* node = newNode(4);
	EXPECT_EQ(KIsEven(node), 1);
}

TEST(KIsEvenTest, OddNumber_no13) {
	Node* node = newNode(5);

	EXPECT_EQ(KIsEven(node), 0);
}