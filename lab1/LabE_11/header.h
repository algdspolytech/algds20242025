#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


typedef struct TreeNode {
    char data[100];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

