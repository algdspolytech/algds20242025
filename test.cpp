#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include "..\bin_tree\bin_tree.h"
}

TEST(Lab_F_Test, insertToEmptyTree_SetAsRoot_no1) {
	Node* root = NULL;
	root = addNode(root, 1);
	ASSERT_EQ(root->left, (Node*)NULL);
	ASSERT_EQ(root->right, (Node*)NULL);
	ASSERT_EQ(root->occurence, 1);
	ASSERT_EQ(root->count, 1);
	ASSERT_EQ(root->data, 1);

	freeTree(root);
}

TEST(Lab_F_Test, insertMultiple_AddsToSubtreeWithLessNodes_no2) { // adds to a sub-tree with less elements
	Node* root = NULL;
	root = addNode(root, 1);
	root = addNode(root, 2);
	root = addNode(root, 3);
	root = addNode(root, 4);
	root = addNode(root, 5);
	root = addNode(root, 6);
	
	Node* node3 = findNode(root, 3);
	ASSERT_EQ(node3->left, findNode(root, 5));

	freeTree(root);
}

TEST(Lab_F_Test, deleteRoot_ReplacesWithLeafDataAndDeletesLeaf_no3) {
	Node* root = NULL;
	root = addNode(root, 1);
	root = addNode(root, 2);
	root = addNode(root, 3);
	root = addNode(root, 4);
	root = addNode(root, 5);
	root = addNode(root, 6);
	
	root = deleteNode(root, 1);
	
	ASSERT_EQ(root->data, 5);

	freeTree(root);
}

TEST(Lab_F_Test, deleteLeaf_ParentLosesTheirChild_no4) {
	Node* root = NULL;
	root = addNode(root, 1);
	root = addNode(root, 2);
	root = addNode(root, 3);
	root = addNode(root, 4);
	root = addNode(root, 5);
	root = addNode(root, 6);

	Node* node2 = findNode(root, 2);
	ASSERT_EQ(node2->right->data, 6);
	root = deleteNode(root, 6);
	ASSERT_EQ(node2->right, (Node*)NULL);

	freeTree(root);
}

TEST(Lab_F_Test, findNodeNonexistentKey_DisplayError_no5) {
	Node* root = NULL;
	root = addNode(root, 1);
	root = addNode(root, 2);
	root = addNode(root, 3);

	ASSERT_EQ(findNode(root, 87890), (Node*)NULL);
	freeTree(root);
}

TEST(Lab_F_Test, insertWithSameData_IncrementOccurenceForThatValue_no6) {
	Node* root = NULL;
	root = addNode(root, 1);
	root = addNode(root, 2);
	root = addNode(root, 2);
	root = addNode(root, 3);
	root = addNode(root, 2);
	root = addNode(root, 5);

	ASSERT_EQ(root->left->occurence, 3);
	freeTree(root);
}

TEST(Lab_F_Test, deleteNonexistentKey_DisplayError_no7) {
	Node* root = NULL;
	root = addNode(root, 1);
	root = addNode(root, 2);

	ASSERT_EQ(root, deleteNode(root, 6789));
	freeTree(root);
}

TEST(Lab_F_Test, deleteFromEmptyTree_DisplayError_no8) {
	Node* root = NULL;

	ASSERT_EQ(root, deleteNode(root, 6789));
	freeTree(root);
}

TEST(Lab_F_Test, inOrderTraversal_DisplayProperOrderOfNodes_no9) {
	Node* root = NULL;
	root = addNode(root, 1);
	root = addNode(root, 2);
	root = addNode(root, 3);
	root = addNode(root, 4);
	root = addNode(root, 5);

	printf("\norder must be: 4 2 1 5 3 (check manually)\n");
	printTreeInOrder(root);
	freeTree(root);
}

TEST(Lab_F_Test, deleteDuplicates_DecrementOccurence_no10) {
	Node* root = NULL;
	root = addNode(root, 1);
	root = addNode(root, 2);
	root = addNode(root, 2);

	root = deleteNode(root, 2);

	ASSERT_EQ(root->left->occurence, 1);
	freeTree(root);
}