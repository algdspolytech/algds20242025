#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key, priority, size;
  struct Node *left, *right;
} Node;

#ifdef __cplusplus

extern "C" {
#endif
Node *create_node(int key);
void update_size(Node *node);
Node *merge(Node *left, Node *right);
void split(Node *node, int key, Node **left, Node **right);
Node *insert(Node *root, int key);
Node *erase(Node *root, int key);
void free_tree(Node *root);
#ifdef __cplusplus
}
#endif