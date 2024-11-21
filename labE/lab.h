#pragma once

typedef struct tree {
    int data;
    struct tree *left;
    struct tree *right;
    unsigned width;
} tree;

unsigned get_num_width(int a);
unsigned count_widths(tree *root);
tree *create_tree_node(int value);
void printTree(tree *root, int space);
void delete_tree(tree *root);
