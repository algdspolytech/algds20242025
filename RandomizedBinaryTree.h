#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <crtdbg.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

typedef struct Node {
	int key; // for BST properties
	int priority; // for heap properties (min-heap or max-heap)
	struct Node* left;
	struct Node* right;
}Node;

void initialize_random();

Node* RBST_createNode(int keyValue);

Node* RBST_rightRotate(Node* y);

Node* RBST_leftRotate(Node* x);

Node* RBST_insert(Node* rootNode, int keyValue); 

Node* RBST_remove(Node* rootNode, int keyValue);

Node* RBST_findNode(Node* rootNode, int keyValue);

void RBST_freeTree(Node* rootNode);

void RBST_printInOrder(Node* rootNode);

void RBST_arrayInOrder(Node* rootNode, int array[], int* i);