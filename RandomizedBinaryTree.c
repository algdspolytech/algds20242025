#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RandomizedBinaryTree.h"

static int random_initialized = 0;

void initialize_random() {
	if (!random_initialized) {
		srand(time(NULL));
		random_initialized = 1;
	}
}


Node* RBST_createNode(int keyValue) {
	initialize_random();
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		fprintf(stderr, "Memory allocation failed!\n");
		return NULL;
	}
	newNode->key = keyValue;
	newNode->priority = rand() % 100;
	newNode->left = (Node*)NULL;
	newNode->right = (Node*)NULL;
	return newNode;
}


Node* RBST_rightRotate(Node* y) {
	Node* x = y->left;
	y->left = x->right;
	x->right = y;
	return x;
}


Node* RBST_leftRotate(Node* x) {
	Node* y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}


Node* RBST_insert(Node* rootNode, int keyValue) {
	if (rootNode == NULL) {
		return RBST_createNode(keyValue);
	}

	if (keyValue == rootNode->key) {
		printf("Duplicate key %d not inserted.\n", keyValue);
		return rootNode; 
	}

	if (keyValue < rootNode->key) {
		rootNode->left = RBST_insert(rootNode->left, keyValue);
		if (rootNode->left->priority > rootNode->priority) { 
			rootNode = RBST_rightRotate(rootNode); 
		}
	}

	else {
		rootNode->right = RBST_insert(rootNode->right, keyValue);
		if (rootNode->right->priority > rootNode->priority) {
			rootNode = RBST_leftRotate(rootNode);
		}
	}

	return rootNode;
}


Node* RBST_remove(Node* rootNode, int keyValue) {
	if (rootNode == NULL) return NULL;

	if (keyValue < rootNode->key) {
		rootNode->left = RBST_remove(rootNode->left, keyValue);
	}
	else if (keyValue > rootNode->key) {
		rootNode->right = RBST_remove(rootNode->right, keyValue);
	}
	else {
		// 1 child or no child
		if (rootNode->left == NULL) {
			Node* temp = rootNode->right;
			free(rootNode);
			return temp;
		}
		else if (rootNode->right == NULL) {
			Node* temp = rootNode->left;
			free(rootNode);
			return temp;
		}

		// 2 children
		if (rootNode->left->priority > rootNode->right->priority) {
			rootNode = RBST_rightRotate(rootNode); 
			rootNode->right = RBST_remove(rootNode->right, keyValue);
		}
		else {
			rootNode = RBST_leftRotate(rootNode);
			rootNode->left = RBST_remove(rootNode->left, keyValue);
		}
	}


	return rootNode;
}


Node* RBST_findNode(Node* rootNode, int keyValue) {
	if (rootNode == NULL) return NULL;

	if (rootNode->key == keyValue) {
		return rootNode;
	}
	else if (keyValue < rootNode->key) {
		return RBST_findNode(rootNode->left, keyValue);
	}
	else {
		return RBST_findNode(rootNode->right, keyValue);
	}
}


void RBST_freeTree(Node* rootNode) {
	if (rootNode == NULL)
		return;

	Node** queue = (Node**)malloc(sizeof(Node*) * 100);
	if (!queue) {
		fprintf(stderr, "Memory allocation failed!\n");
		exit(-1);
	}
	int front = 0, rear = 0;

	queue[rear++] = rootNode;

	while (front < rear) {
		Node* node = queue[front++];

		if (node->left != NULL)
			queue[rear++] = node->left;

		if (node->right != NULL)
			queue[rear++] = node->right;

		free(node);
	}

	free(queue);
}


void RBST_printInOrder(Node* rootNode) {
	if (rootNode != NULL) {
		RBST_printInOrder(rootNode->left);
		printf("%d ", rootNode->key);
		RBST_printInOrder(rootNode->right);
	}
}

void RBST_arrayInOrder(Node* rootNode, int array[], int* i) {
	if (rootNode != NULL) {
		RBST_arrayInOrder(rootNode->left, array, i);
		array[*i] = rootNode->key;
		(*i)++;
		RBST_arrayInOrder(rootNode->right, array, i);
	}
}