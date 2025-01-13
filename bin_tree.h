#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

typedef struct Node {
	struct Node* left;
	struct Node* right;
	int count;
	int data;
	int occurence;
} Node;

Node* getParentNode(Node* binary_tree, Node* child_node);

Node* findNode(Node* binary_tree, int key);

Node* addNode(Node* binary_tree, int node_data);

Node* deleteNode(Node* binary_tree, int key);

void freeTree(Node* binary_tree);

void printTreeInOrder(Node* binary_tree);