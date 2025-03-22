#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include "..\labH\RandomizedBinaryTree.h"
}

TEST(RBST_tests, insertOneToEmptyTree_no1) { 
	Node* root = (Node*)NULL;
	root = RBST_insert(root, 1);
	ASSERT_EQ(root->key, 1);
	ASSERT_EQ(root->left,(Node*)NULL);
	ASSERT_EQ(root->right, (Node*)NULL);
	ASSERT_GT(root->priority, 0);
	RBST_freeTree(root);
}

TEST(RBST_tests, insertManyToEmptyTree_no2) {
	Node* root = (Node*)NULL;
	root = RBST_insert(root, 1);
	root = RBST_insert(root, 2);
	root = RBST_insert(root, 3);
	int rootArr[3];
	int i_rootArr = 0;
	RBST_arrayInOrder(root, rootArr, &i_rootArr);
	int exArr[3] = { 1, 2, 3 };

	ASSERT_EQ(rootArr[0], exArr[0]);
	ASSERT_EQ(rootArr[1], exArr[1]);
	ASSERT_EQ(rootArr[2], exArr[2]);
	RBST_freeTree(root);
}

TEST(RBST_tests, insertNodeWithExistingKey_no3) {
	Node* root = (Node*)NULL;
	root = RBST_insert(root, 1);
	root = RBST_insert(root, 1);

	ASSERT_EQ(root->key, 1); 
	ASSERT_EQ(root->left, (Node*)NULL);
	ASSERT_EQ(root->right, (Node*)NULL);
	ASSERT_GT(root->priority, 0);
	RBST_freeTree(root);
}

TEST(RBST_tests, removeNonExistentNode_no4) {
	Node* root = (Node*)NULL;
	root = RBST_insert(root, 1);
	root = RBST_remove(root, 2);

	ASSERT_EQ(root->key, 1);
	ASSERT_EQ(root->left, (Node*)NULL);
	ASSERT_EQ(root->right, (Node*)NULL);
	ASSERT_GT(root->priority, 0);
	RBST_freeTree(root);
}

TEST(RBST_tests, removeNodeWith1Child_no5) {
	Node* root = (Node*)NULL;
	root = RBST_insert(root, 4);
	root = RBST_insert(root, 5);
	root = RBST_insert(root, 10);
	root = RBST_insert(root, 11);
	root = RBST_remove(root, 5);
	int rootArr[3];
	int i_rootArr = 0;
	RBST_arrayInOrder(root, rootArr, &i_rootArr);
	int exArr1[3] = { 4,10, 11 };

	ASSERT_EQ(rootArr[0], exArr1[0]);
	ASSERT_EQ(rootArr[1], exArr1[1]);
	ASSERT_EQ(rootArr[2], exArr1[2]);
	RBST_freeTree(root);
}

TEST(RBST_tests, removeNodeWith2Children_no6) {
	Node* root = NULL;
	root = RBST_insert(root, 2);
	root = RBST_insert(root, 3);
	root = RBST_insert(root, 4);
	root = RBST_remove(root, 3);

	ASSERT_TRUE(root->key == 2 || root->key == 4);

	RBST_freeTree(root);
}

TEST(RBST_tests, removeLeafNode_no7) {
	Node* root = NULL;
	root = RBST_insert(root, 10);
	root = RBST_insert(root, 5);

	root = RBST_remove(root, 5);

	ASSERT_EQ(root->key, 10);
	ASSERT_EQ(root->left, nullptr);

	RBST_freeTree(root);
}

TEST(RBST_tests, removeFromEmptyTree_no8) {
	Node* root = NULL;

	root = RBST_remove(root, 10);

	ASSERT_EQ(root, nullptr);

	RBST_freeTree(root);
}

TEST(RBST_tests, searchValidNode_no9) {
	Node* root = NULL;
	root = RBST_insert(root, 10);
	root = RBST_insert(root, 5);
	root = RBST_insert(root, 15);

	Node* foundNode = RBST_findNode(root, 5);

	ASSERT_NE(foundNode, nullptr);
	ASSERT_EQ(foundNode->key, 5);

	RBST_freeTree(root);
}

TEST(RBST_tests, searchInvalidNode_no10) {
	Node* root = NULL;
	root = RBST_insert(root, 10);
	root = RBST_insert(root, 5);
	root = RBST_insert(root, 15);

	Node* foundNode = RBST_findNode(root, 20);

	ASSERT_EQ(foundNode, nullptr);

	RBST_freeTree(root);
}