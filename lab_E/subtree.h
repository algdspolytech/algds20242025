#pragma once


// tree structure
typedef struct TreeNode {
    char* word;
    struct TreeNode* left;
    struct TreeNode* right;
    int subtree_width;
} TreeNode;


TreeNode* create_node(const char* word);
int compute_subtree_width(TreeNode* node);
void print_tree(TreeNode* root, int depth);
void free_tree(TreeNode* root);