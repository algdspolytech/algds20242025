#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


typedef struct TreeNode {
    int value;
    int min_leaf_height;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


TreeNode* createNode(int value);
int calculateMinLeafHeight(TreeNode* node);
void visualizeTree(TreeNode* node);
TreeNode* createHeightTree(TreeNode* node);