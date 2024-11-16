#pragma once

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* create_node(int value);

TreeNode* initialize_tree(int* elements, int size);

void print_tree(TreeNode* root, int depth);

void print_compact_tree(TreeNode* root);

void free_tree(TreeNode* root);