#include "../include/rb_tree.h"
#include <stdlib.h>

rb_tree *create_node(int key, color c) {
  rb_tree *node = malloc(sizeof(rb_tree));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  node->c = c;
  return node;
}

static void _insert(rb_tree **root, rb_tree *node) {
  rb_tree *node_tmp = *root;
  rb_tree *node_parent = NULL;

  while (node_tmp != NULL) {
    node_parent = node_tmp;
    if (node->key < node_tmp->key) {
      node_tmp = node_tmp->left;
    } else {
      node_tmp = node_tmp->right;
    }
  }

  node->parent = node_parent;
  if (node_parent == NULL) {
    *root = node;
  } else {
    if (node->key < node_parent->key) {
      node_parent->left = node;
    } else {
      node_parent->right = node;
    }
  }
}

static void left_rotate(rb_tree **root, rb_tree *node) {
  rb_tree *node_tmp = node->right;
  node->right = node_tmp->left;

  if (node_tmp->left != NULL) {
    node_tmp->left->parent = node;
  }
  node_tmp->parent = node->parent;

  if (node->parent == NULL) {
    *root = node_tmp;
  } else if (node == node->parent->left) {
    node->parent->left = node_tmp;
  } else {
    node->parent->right = node_tmp;
  }
  node_tmp->left = node;
  node->parent = node_tmp;
}

static void right_rotate(rb_tree **root, rb_tree *node) {
  rb_tree *node_tmp = node->left;
  node->left = node_tmp->right;

  if (node_tmp->right != NULL) {
    node_tmp->right->parent = node;
  }
  node_tmp->parent = node->parent;

  if (node->parent == NULL) {
    *root = node_tmp;
  } else if (node == node->parent->right) {
    node->parent->right = node_tmp;
  } else {
    node->parent->left = node_tmp;
  }
  node_tmp->right = node;
  node->parent = node_tmp;
}

void insert(rb_tree **root, int key) {
  rb_tree *node = create_node(key, RED);
  _insert(root, node);

  while (node != *root && node->parent->c == RED) {
    if (node->parent == node->parent->parent->left) {
      rb_tree *node_tmp = node->parent->parent->right;
      if (node_tmp != NULL && node_tmp->c == RED) {
        node->parent->c = BLACK;
        node_tmp->c = BLACK;
        node->parent->parent->c = RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          left_rotate(root, node);
        }
        node->parent->c = BLACK;
        node->parent->parent->c = RED;
        right_rotate(root, node->parent->parent);
      }
    } else {
      rb_tree *node_tmp = node->parent->parent->left;
      if (node_tmp != NULL && node_tmp->c == RED) {
        node->parent->c = BLACK;
        node_tmp->c = BLACK;
        node->parent->parent->c = RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          right_rotate(root, node);
        }
        node->parent->c = BLACK;
        node->parent->parent->c = RED;
        left_rotate(root, node->parent->parent);
      }
    }
  }
  (*root)->c = BLACK;
}

rb_tree *search(rb_tree *root, int key) {
  rb_tree *node = root;
  while (node != NULL && node->key != key) {
    if (node->key > key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}
