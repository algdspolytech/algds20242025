#include "pch.h"
extern "C" {
#include "../AlgosiH/main.h"
}
TEST(NewNodeTest, CreatesMultipleNodes_no1) {
	Node* node1 = newNode(1, 100);
	Node* node2 = newNode(2, 200);

	ASSERT_NE(node1, nullptr);
	ASSERT_NE(node2, nullptr);

	EXPECT_NE(node1->priority, node2->priority);

	EXPECT_EQ(node1->x, 1);
	EXPECT_EQ(node1->c, 100);
	EXPECT_EQ(node2->x, 2);
	EXPECT_EQ(node2->c, 200);

	free(node1);
	free(node2);
}

TEST(UpdateMaxTest, LeafNode_no2) {
	Node* node = newNode(1, 10);
	updateMax(node);

	EXPECT_EQ(node->max_c, 10);

	free(node);
}

TEST(UpdateMaxTest, NodeWithBothChildren_no3) {
	Node* node = newNode(1, 10);
	node->left = newNode(2, 20);
	node->right = newNode(3, 30);

	updateMax(node);

	EXPECT_EQ(node->max_c, 30);

	free(node->left);
	free(node->right);
	free(node);
}

TEST(UpdateMaxTest, RightChildMaxLessThanLeftChildMax_no4) {
	Node* node = newNode(1, 10);
	node->left = newNode(2, 25);
	node->right = newNode(3, 20);

	updateMax(node);

	EXPECT_EQ(node->max_c, 25);

	free(node->left);
	free(node->right);
	free(node);
}

TEST(UpdateMaxTest, NodeMaxGreaterThanChildrenMax_no5) {
	Node* node = newNode(1, 50);
	node->left = newNode(2, 20);
	node->right = newNode(3, 30);

	updateMax(node);

	EXPECT_EQ(node->max_c, 50);

	free(node->left);
	free(node->right);
	free(node);
}

TEST(SplitTest, EmptyTree_no6) {
	Node* root = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	split(root, 5, &left, &right);

	EXPECT_EQ(left, nullptr);
	EXPECT_EQ(right, nullptr);
}

TEST(SplitTest, KeyLessThanRoot_no7) {
	Node* root = newNode(10, 100);
	root->left = newNode(5, 50);
	root->right = newNode(15, 150);

	Node* left = nullptr;
	Node* right = nullptr;

	split(root, 7, &left, &right);

	EXPECT_NE(left, nullptr);
	EXPECT_EQ(left->x, 5);

	EXPECT_NE(right, nullptr);
	EXPECT_EQ(right->x, 10);
	EXPECT_EQ(right->right->x, 15);

	free(left);
	free(right->left);
	free(right->right);
	free(right);
}

TEST(SplitTest, KeyGreaterThanRoot_no8) {
	Node* root = newNode(10, 100);
	root->left = newNode(5, 50);
	root->right = newNode(15, 150);

	Node* left = nullptr;
	Node* right = nullptr;

	split(root, 12, &left, &right);

	EXPECT_NE(left, nullptr);
	EXPECT_EQ(left->x, 10);
	EXPECT_EQ(left->left->x, 5);

	EXPECT_NE(right, nullptr);
	EXPECT_EQ(right->x, 15);

	free(left->left);
	free(left);
	free(right);
}

TEST(MergeTest, RightTreeEmpty_no9) {
	Node* left = newNode(5, 50);
	Node* right = nullptr;

	Node* result = merge(left, right);

	EXPECT_EQ(result, left);

	free(left);
}

TEST(MergeTest, LeftPriorityGreater_no10) {
	Node* left = newNode(5, 50);
	left->priority = 10;
	left->max_c = 50;

	Node* right = newNode(10, 100);
	right->priority = 5;
	right->max_c = 100;

	Node* result = merge(left, right);

	EXPECT_EQ(result, left);
	EXPECT_EQ(result->right, right);

	EXPECT_EQ(result->max_c, 100);

	free(left);
	free(right);
}

TEST(InsertTest, InsertIntoEmptyTree_no11) {
	Node* root = nullptr;
	root = insert(root, 10, 100);

	EXPECT_NE(root, nullptr);

	EXPECT_EQ(root->x, 10);
	EXPECT_EQ(root->c, 100);
	EXPECT_EQ(root->max_c, 100);

	free(root);
}

TEST(InsertTest, InsertIntoMultiNodeTree_no12) {
	Node* root = newNode(10, 100);
	root->left = newNode(5, 50);
	root->right = newNode(15, 150);

	root = insert(root, 12, 120);

	EXPECT_EQ(root->x, 12);

	EXPECT_EQ(root->max_c, 150);

	free(root->left);
	free(root->right->left);
	free(root->right);
	free(root);
}

TEST(FindMaxTest, EmptyTree_no13) {
	Node* root = nullptr;
	int max_c = findMax(root, 1, 10);

	EXPECT_EQ(max_c, -1);
}

TEST(FindMaxTest, IntervalContainsNoNodes_no14) {
	Node* root = newNode(10, 100);
	root->left = newNode(5, 50);
	root->right = newNode(15, 150);

	int max_c = findMax(root, 11, 14);

	EXPECT_EQ(max_c, -1);

	free(root->left);
	free(root->right);
	free(root);
}

TEST(FindMaxTest, IntervalPartiallyOverlapsTree_no15) {
	Node* root = newNode(10, 100);
	root->left = newNode(5, 50);
	root->right = newNode(15, 150);

	int max_c = findMax(root, 8, 12);

	EXPECT_EQ(max_c, 100);

	free(root->left);
	free(root->right);
	free(root);
}

TEST(FindMaxTest, IntervalCoversEntireTree_no16) {
	Node* root = newNode(10, 100);
	root->left = newNode(5, 50);
	root->right = newNode(15, 150);

	int max_c = findMax(root, 1, 20);

	EXPECT_EQ(max_c, 150);

	free(root->left);
	free(root->right);
	free(root);
}