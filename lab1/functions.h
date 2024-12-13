#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Definition of the tree node
typedef struct TreeNode {
    char* word;               // Word stored in the node
    int width;                // Width of the subtree rooted at this node
    struct TreeNode* left;    // Pointer to the left child
    struct TreeNode* right;   // Pointer to the right child
} TreeNode;

// Function prototypes
TreeNode* createNode(const char* word);
void insert(TreeNode** root, const char* word);
int calculateWidths(TreeNode* root);
void printTree(TreeNode* root, int space);
void freeTree(TreeNode* root);

#endif // FUNCTIONS_H