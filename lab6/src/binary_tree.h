#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct TreeNode {
    int value;
    int node_count;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

TreeNode* create_node(int value, TreeNode* parent);

TreeNode* add_node(TreeNode** root, int value);

void remove_node(TreeNode** root, int value);

#endif
