#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TreeNode {
    char* word;
    int subtree_width;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(const char* word);
void freeTree(TreeNode* root);
TreeNode* insert(TreeNode* root, const char* word);
int computeSubtreeWidth(TreeNode* root);
void printTree(TreeNode* root);

#ifdef __cplusplus
}
#endif

#endif // FUNCTIONS_H