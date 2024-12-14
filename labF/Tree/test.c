#include "test.h"

void findKthSmallest_OneElementTree_returnValidVal() {
	Node* root = NULL;
	int K = 1; 
	root = insert(root, 1);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result==1);
}


void findKthSmallest_FirstOfTwoEqualElements_returnValidVal() {
	Node* root = NULL;
	int K = 1;
	root = insert(root, 1);
	root = insert(root, 1);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 1);
}


void findKthSmallest_SecondOfTwoEqualElements_returnValidVal() {
	Node* root = NULL;
	int K = 2;
	root = insert(root, 1);
	root = insert(root, 1);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 1);
}


void findKthSmallest_FirstOfTwoDifferentElements_returnValidVal() {
	Node* root = NULL;
	int K = 1;
	root = insert(root, 1);
	root = insert(root, 2);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 1);
}


void findKthSmallest_SecondOfTwoDifferentElements_returnValidVal() {
	Node* root = NULL;
	int K = 2;
	root = insert(root, 1);
	root = insert(root, 2);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 2);
}


void findKthSmallest_ManyElements_returnValidVal() {
	Node* root = NULL;
	int K = 4;
	root = insert(root, 1);
	root = insert(root, 2);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 4);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 3);
}


void findKthSmallest_TooBigK_returnNull() {
	Node* root = NULL;
	int K = 3;
	root = insert(root, 1);
	root = insert(root, 2);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 0);
}


void findKthSmallest_KIsNull_returnNull() {
	Node* root = NULL;
	int K = 0;
	root = insert(root, 1);
	root = insert(root, 2);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 0);
}


void findKthSmallest_ManyEqualElements_returnValidVal() {
	Node* root = NULL;
	int K = 2;
	root = insert(root, 1);
	root = insert(root, 1);
	root = insert(root, 1);
	root = insert(root, 1);
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 1);
}


void findKthSmallest_EmptyTree_returnNull() {
	Node* root = NULL;
	int K = 0;
	int count = 0;
	int result = 0;

	findKthSmallest(root, &count, K, &result);

	assert(result == 0);
}

void run_all_tests() {
	findKthSmallest_OneElementTree_returnValidVal();
	findKthSmallest_FirstOfTwoEqualElements_returnValidVal();
	findKthSmallest_SecondOfTwoEqualElements_returnValidVal();
	findKthSmallest_FirstOfTwoDifferentElements_returnValidVal();
	findKthSmallest_SecondOfTwoDifferentElements_returnValidVal();
	findKthSmallest_ManyElements_returnValidVal();
	findKthSmallest_TooBigK_returnNull();
	findKthSmallest_KIsNull_returnNull();
	findKthSmallest_ManyEqualElements_returnValidVal();
	findKthSmallest_EmptyTree_returnNull();
	printf("All tests completed successfully.\n");
}