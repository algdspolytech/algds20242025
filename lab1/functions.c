#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define COUNT 5  // Used for tree indentation in printTree function

// Function to create a new tree node
TreeNode* createNode(const char* word) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->word = _strdup(word);
    newNode->width = strlen(word);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert words into the binary tree (for testing purposes, we'll insert to left or right based on length)
void insert(TreeNode** root, const char* word) {
    if (*root == NULL) {
        *root = createNode(word);
    }
    else {
        if (strlen(word) <= strlen((*root)->word)) {
            insert(&((*root)->left), word);
        }
        else {
            insert(&((*root)->right), word);
        }
    }
}

// Function to calculate the widths of subtrees and store them in the nodes
int calculateWidths(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftWidth = calculateWidths(root->left);
    int rightWidth = calculateWidths(root->right);
    root->width = strlen(root->word) + leftWidth + rightWidth;
    return root->width;
}

// Function to print the tree with computed widths
void printTree(TreeNode* root, int space) {
    if (root == NULL) {
        return;
    }
    space += COUNT;
    printTree(root->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%s\n", root->word);
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->width);
    printTree(root->left, space);
}

// Function to free the allocated memory of the tree
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root->word);
    free(root);
}