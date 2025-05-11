#pragma once

#include <stdio.h>
#include <stdlib.h>


typedef enum { BLACK, RED } Color;

typedef struct Node {
    int key;
    struct Node* left, * right, * parent;
    Color color;
} Node;

// Creating a node
Node* createNode(int key, Color color);

// Calculating the black height
int blackHeight(Node* node);

// Search for a node with a given black height in the right subtree
Node* findBlHeightRight(Node* root, int bh);

// Search for a node with a given black height in the left subtree
Node* findBlHeightLeft(Node* root, int bh);

// Left rotate
void leftRotate(Node** root, Node* x);

// Right rotate
void rightRotate(Node** root, Node* y);

// Balancing after insertion
void insertFixup(Node** root, Node* z);

// Checking for the key in the right subtree
Node* checkMatchRight(Node* T1, int x);

// Checking for the key in the left subtree
Node* checkMatchLeft(Node* T1, int x);

// Uniting two trees by the key x
Node* rbUnion(Node** root, Node* T1, Node* T2, int x);

// Traversing the tree in ascending order
void inorderTraversal(Node* root);

// Output of the tree to the console
void printTree(Node* root, int level);

// Insert element into tree by key
void insert(Node** root, int key);
