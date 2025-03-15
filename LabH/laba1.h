#pragma once

typedef struct Node
{
	int key;
	int priority;
	struct Node* left;
	struct Node* right;
} Node;

Node* Create_node(int key);
Node* Merge(Node* A, Node* B);
void Split(Node* n, int key, Node* A, Node* B);
Node* Insert(int key, Node* root);
Node* Erase(int key, Node* root);
bool contains(Node* root, int key);
void RunTests();


