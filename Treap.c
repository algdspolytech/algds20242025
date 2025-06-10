#include "Treap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Node* create_node(int key) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}

	node->key = key;
	node->priority = rand();
	node->left = NULL;
	node->right = NULL;
	return node;
}

void split(Node* root, int key, Node** left, Node** right) {
	if (!root) {
		*left = *right = NULL;
	}
	else if (root->key <= key) {
		split(root->right, key, &root->right, right);
		*left = root;
	}
	else {
		split(root->left, key, left, &root->left);
		*right = root;
	}
}

Node* search(Node* root, int key) {
	if (root == NULL || root->key == key) {
		return root;
	}

	if (key < root->key) {
		return search(root->left, key);
	}
	else {
		return search(root->right, key);
	}
}

Node* insert(Node* root, int key) {
	if (search(root, key) != NULL)
		return root;

	if (!root)
		return create_node(key);

	Node* new_node = create_node(key);
	if (new_node->priority > root->priority) {
		split(root, key, &new_node->left, &new_node->right);
		return new_node;
	}

	if (key < root->key) {
		root->left = insert(root->left, key);
	}
	else {
		root->right = insert(root->right, key);
	}
	return root;
}

Node* merge(Node* left, Node* right) {
	if (left == NULL) return right;
	if (right == NULL) return left;

	if (left->priority > right->priority) {
		left->right = merge(left->right, right);
		return left;
	}
	else {
		right->left = merge(left, right->left);
		return right;
	}
}

Node* deleteNode(Node* root, int key) {
	if (!root) return NULL;
	if (key < root->key) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->key) {
		root->right = deleteNode(root->right, key);
	}
	else {
		Node* temp = merge(root->left, root->right);
		free(root);
		return temp;
	}
	return root;
}

void free_tree(Node* root) {
	if (root != NULL) {
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}