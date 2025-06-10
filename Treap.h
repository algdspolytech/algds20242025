#pragma once

typedef struct Node {
	int key;
	int priority;
	struct Node* left;
	struct Node* right;
}Node;

Node* create_node(int key);
void split(Node* root, int key, Node** left, Node** right);
Node* search(Node* root, int key);
Node* insert(Node* root, int key);
Node* merge(Node* left, Node* right);
Node* deleteNode(Node* root, int key);
void free_tree(Node* root);