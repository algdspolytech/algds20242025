#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value, priority;
  struct Node *left_child, *right_child;
} Node;

#ifdef __cplusplus

extern "C" {
#endif
Node *make_node(int value);
Node *combine_trees(Node *tree1, Node *tree2);
void divide_tree(Node *root, int value, Node **left_tree, Node **right_tree);
Node *add_value(Node *root, int value);
Node *remove_value(Node *root, int value);
void release_tree(Node *root);
#ifdef __cplusplus
}
#endif