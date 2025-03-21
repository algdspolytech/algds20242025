#include "funcs.h"

Node *create_node(int key) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (!node) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  node->key = key;
  node->priority = rand();
  node->size = 1;

  if (key == -1)
    node->left = node->right = NULL;
  else
    node->left = node->right = NULL;

  return node;
}

void update_size(Node *node) {
  if (node && node->key != -1) {
    node->size = 1;
    if (node->left && node->left->key != -1)
      node->size += node->left->size;
    if (node->right && node->right->key != -1)
      node->size += node->right->size;
  }
}

Node *merge(Node *left, Node *right) {
  if (!left)
    return right;
  if (!right)
    return left;

  if (left->key == -1)
    return right;
  if (right->key == -1)
    return left;

  if (left->priority > right->priority) {
    left->right = merge(left->right, right);
    update_size(left);
    return left;
  } else {
    right->left = merge(left, right->left);
    update_size(right);
    return right;
  }
}

void split(Node *node, int key, Node **left, Node **right) {
  if (!node || node->key == -1) {
    *left = NULL;
    *right = NULL;
    return;
  }

  if (key >= node->key) {
    split(node->right, key, &node->right, right);
    *left = node;
  } else {
    split(node->left, key, left, &node->left);
    *right = node;
  }

  update_size(node);
}

Node *insert(Node *root, int key) {
  Node *new_node = create_node(key);

  if (!root || root->key == -1) {
    free_tree(root);
    return new_node;
  }

  Node *left = NULL;
  Node *right = NULL;

  split(root, key, &left, &right);
  return merge(merge(left, new_node), right);
}

Node *erase(Node *root, int key) {
  if (!root || root->key == -1)
    return root;

  if (root->key == key) {
    Node *temp = merge(root->left, root->right);
    free(root);
    return temp;
  }

  if (key < root->key)
    root->left = erase(root->left, key);
  else
    root->right = erase(root->right, key);

  update_size(root);
  return root;
}

void free_tree(Node *root) {
  if (!root)
    return;

  if (root->key != -1) {
    free_tree(root->left);
    free_tree(root->right);
  }

  free(root);
}