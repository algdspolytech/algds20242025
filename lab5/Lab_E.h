#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// Structure for a binary tree Tree
// Structure for a binary tree node
typedef struct Node {
    int value;        // Value of the node
    struct Node* left;   // Pointer to the left subtree
    struct Node* right;  // Pointer to the right subtree
} Node;

// Function to create a new tree Tree
Node* createTree(int value, Node* left, Node* right);
// Function to free the memory occupied by the tree
void freeTree(Node* node);
// Function to read a tree from a file
Node* readTree(FILE* file);
// Function to display the tree in usual way (to file)
void displayTree1(FILE* out, Node* Tree);
// Function to display tree (int file) in the form of: Tree [left subtree] [right subtree]
void displayTree2(FILE* out, Node* Tree);
// Function that displays data from file
void displayFile(FILE* file);