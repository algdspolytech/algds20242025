#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int value;
    int width;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

#ifdef __cplusplus

extern "C" {
#endif
    TreeNode* create_node(int value);
    int calculate_subtree_width(TreeNode* node);
    void print_tree_with_width(TreeNode* node, int level);
    void free_tree(TreeNode* node);
#ifdef __cplusplus
}
#endif