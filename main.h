#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdio.h> 

typedef struct TreeNode {
    int data;
    int subtree_width;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Объявление функций
TreeNode* createNode(int data);
int calculateWidth(int number);
int calculateSubtreeWidth(TreeNode* node);
int calculateTreeHeight(TreeNode* node); 
char digitToChar(int digit);
void writeNumberToMatrix(char** matrix, int rows, int cols, int x, int y, int number);
void buildTextRepresentation(TreeNode* node, char** matrix, int rows, int cols, int x, int y);
void printTreeVisual(TreeNode* root);
#endif 