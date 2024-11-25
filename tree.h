#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    char* word;
    struct TreeNode* left;
    struct TreeNode* right;
    int width;
} TreeNode;

TreeNode* createNode(const char* word);
TreeNode* insert(TreeNode* root, const char* word);
int calculateWidth(TreeNode* node);
void printTree(TreeNode* node, FILE* out);
void freeTree(TreeNode* node);

#endif // TREE_H
