#pragma once

#define BINARY_TREE_H
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data);
TreeNode* insertNode(TreeNode* root, int data);
TreeNode* loadTreeFromFile(const char* filename);
int saveTreeToFile(TreeNode* root, const char* filename);
void printTreePreOrder(TreeNode* root, FILE* stream);
void printTreeInOrder(TreeNode* root, FILE* stream);
void printTreePostOrder(TreeNode* root, FILE* stream);
void freeTree(TreeNode* root);