#include "btree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void _killNode(B_node *node) {
  if (node == NULL)
    return;
  if (node->is_leaf == false) {
    for (int i = 0; i <= node->keys_count; i++) {
      _killNode(node->children[i]);
    }
  }
  free(node);
}

void Free(B_tree *tree) {
  if (tree == NULL)
    return;
  if (tree->root == NULL)
    return;
  _killNode(tree->root);
  tree->root = NULL;
}

B_node *_createNode(bool isleaf, B_node *parent) {
  B_node *node = (B_node *)malloc(sizeof(B_node));
  node->is_leaf = isleaf;
  node->keys_count = 0;
  node->parent = parent;
  memset(node->children, 0, sizeof(node->children));
  return node;
}

B_search_result Search(B_tree *tree, int data) {

  B_node *node = tree->root;

  while (node != NULL) {
    int i = 0;
    while (node->keys_count > i && node->keys[i] < data) {
      i++;
    }

    if (i < node->keys_count && data == node->keys[i]) {
      return EXISTS;
    }

    if (node->is_leaf) {
      return MISSING;
    } else {
      node = node->children[i];
    }
  }

  return MISSING;
}

void Insert(B_tree *tree, int data) {

  if (!SplitFPtr) {
    SplitFPtr = (split_t const *)(void *)&split;
  }
  if (!InsertNotFullPtr) {
    InsertNotFullPtr = (insertNotFull_t const *)(void *)&insertNotFull;
  }

  if (Search(tree, data) == EXISTS) {
    return;
  }

  if (tree->root == NULL) {
    tree->root = _createNode(true, NULL);
    tree->root->keys[0] = data;
    tree->root->keys_count = 1;
    return;
  }

  B_node *root = tree->root;

  if (root->keys_count >= MAX_KEYS) {
    B_node *new_root = _createNode(false, NULL);
    new_root->children[0] = root;
    root->parent = new_root;
    tree->root = new_root;

    (*SplitFPtr)(new_root, 0);
    (*InsertNotFullPtr)(new_root, data);
  } else {
    (*InsertNotFullPtr)(root, data);
  }
}

void insertNotFull(B_node *node, int data) {
  int index = node->keys_count - 1;

  if (node->is_leaf == true) {
    while (index >= 0 && data < node->keys[index]) {
      node->keys[index + 1] = node->keys[index];
      index--;
    }
    node->keys[index + 1] = data;
    node->keys_count++;
  } else {
    while (index >= 0 && data < node->keys[index]) {
      index--;
    }
    index++;

    if (node->children[index]->keys_count == MAX_KEYS) {
      (*SplitFPtr)(node, index);
      if (data > node->keys[index]) {
        index++;
      }
    }
    (*InsertNotFullPtr)(node->children[index], data);
  }
}

void split(B_node *parent_of_splited, int split_at_index) {
  B_node *old_child = parent_of_splited->children[split_at_index];
  B_node *new_child = _createNode(old_child->is_leaf, parent_of_splited);

  new_child->keys_count = MIN_CHILDREN;

  for (size_t i = 0; i < MIN_CHILDREN; i++) {
    new_child->keys[i] = old_child->keys[i + T];
  }

  if (old_child->is_leaf == false) {
    for (size_t i = 0; i <= MIN_CHILDREN; i++) {
      new_child->children[i] = old_child->children[i + T];
      if (new_child->children[i]) {
        new_child->children[i]->parent = new_child;
      }
    }
  }

  for (int i = parent_of_splited->keys_count; i > split_at_index; i--) {
    parent_of_splited->children[i + 1] = parent_of_splited->children[i];
  }
  parent_of_splited->children[split_at_index + 1] = new_child;

  for (int i = parent_of_splited->keys_count - 1; i >= split_at_index; i--) {
    parent_of_splited->keys[i + 1] = parent_of_splited->keys[i];
  }
  parent_of_splited->keys[split_at_index] = old_child->keys[MIN_CHILDREN];
  parent_of_splited->keys_count++;

  old_child->keys_count = MIN_CHILDREN;
}

B_tree_iterator IteratorBegin(B_tree *tree) {
  B_tree_iterator iterator = {NULL, -1};
  if (tree == NULL || tree->root == NULL || tree->root->keys_count == 0) {
    return iterator;
  }

  B_node *cur = tree->root;
  while (!cur->is_leaf) {
    if (cur->children[0] == NULL)
      break;
    cur = cur->children[0];
  }

  iterator.node = cur;
  iterator.position = -1;
  return iterator;
}

int Next(B_tree_iterator *iter) {

  if (iter->node == NULL)
    return 0;

  B_node *node = iter->node;
  int pos = iter->position;

  if (node->is_leaf == true) {
    if (pos + 1 < node->keys_count) {
      iter->position = pos + 1;
      return 1;
    }

  } else {

    if (pos + 1 <= node->keys_count && node->children[pos + 1]) {
      B_node *cur = node->children[pos + 1];
      while (!cur->is_leaf) {
        cur = cur->children[0];
      }
      iter->node = cur;
      iter->position = 0;
      return 1;
    }
  }

  B_node *cur = node;
  while (cur->parent) {
    B_node *pointer = cur->parent;

    int i = 0;
    while (i <= pointer->keys_count && pointer->children[i] != cur) {
      i++;
    }

    if (i < pointer->keys_count) {
      iter->node = pointer;
      iter->position = i;
      return 1;
    }

    cur = pointer;
  }

  iter->node = NULL;
  return 0;
}

int Key(B_tree_iterator *iter) { return iter->node->keys[iter->position]; }