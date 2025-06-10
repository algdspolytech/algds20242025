#include "btree.h"
#include <stdbool.h>
#include <stdlib.h>

// Вспомогательная функция для создания нового узла
static B_node *create_node(bool is_leaf) {
  B_node *node = (B_node *)malloc(sizeof(B_node));
  if (!node)
    return NULL;

  node->keys_count = 0;
  node->is_leaf = is_leaf;
  node->parent = NULL;

  for (int i = 0; i < MAX_CHILDREN; i++) {
    node->children[i] = NULL;
  }

  return node;
}

void split(B_node *parent_of_splited, int split_at_index) {
  B_node *child = parent_of_splited->children[split_at_index];
  B_node *new_node = create_node(child->is_leaf);
  new_node->parent = parent_of_splited;

  // Копируем правую половину ключей из child в new_node
  new_node->keys_count = MIN_CHILDREN;
  for (int i = 0; i < MIN_CHILDREN; i++) {
    new_node->keys[i] = child->keys[T + i];
  }

  // Если не лист, копируем и детей
  if (!child->is_leaf) {
    for (int i = 0; i <= MIN_CHILDREN; i++) {
      new_node->children[i] = child->children[T + i];
      if (new_node->children[i]) {
        new_node->children[i]->parent = new_node;
      }
    }
  }

  child->keys_count = MIN_CHILDREN;

  // Сдвигаем детей родителя, чтобы освободить место для new_node
  for (int i = parent_of_splited->keys_count; i > split_at_index; i--) {
    parent_of_splited->children[i + 1] = parent_of_splited->children[i];
  }
  parent_of_splited->children[split_at_index + 1] = new_node;

  // Сдвигаем ключи родителя и вставляем средний ключ из child
  for (int i = parent_of_splited->keys_count - 1; i >= split_at_index; i--) {
    parent_of_splited->keys[i + 1] = parent_of_splited->keys[i];
  }
  parent_of_splited->keys[split_at_index] = child->keys[MIN_CHILDREN];
  parent_of_splited->keys_count++;
}

void insertNotFull(B_node *node, int data) {
  int i = node->keys_count - 1;

  if (node->is_leaf) {
    // Вставка в лист
    while (i >= 0 && data < node->keys[i]) {
      node->keys[i + 1] = node->keys[i];
      i--;
    }
    node->keys[i + 1] = data;
    node->keys_count++;
  } else {
    // Находим подходящего ребенка для вставки
    while (i >= 0 && data < node->keys[i]) {
      i--;
    }
    i++;

    // Если ребенок полный, разделяем его
    if (node->children[i]->keys_count == MAX_KEYS) {
      (*SplitFPtr)(node, i);
      if (data > node->keys[i]) {
        i++;
      }
    }

    (*InsertNotFullPtr)(node->children[i], data);
  }
}

void Insert(B_tree *tree, int data) {
  if (!tree->root) {
    tree->root = create_node(true);
    tree->root->keys[0] = data;
    tree->root->keys_count = 1;
    return;
  }

  if (Search(tree, data) == EXISTS) {
    return;
  }

  // Если корень полный, разделяем его
  if (tree->root->keys_count == MAX_KEYS) {
    B_node *new_root = create_node(false);
    new_root->children[0] = tree->root;
    tree->root->parent = new_root;
    tree->root = new_root;
    (*SplitFPtr)(new_root, 0);
  }

  (*InsertNotFullPtr)(tree->root, data);
}

B_search_result Search(B_tree *tree, int data) {
  B_node *node = tree->root;

  while (node != NULL) {
    int i = 0;
    while (i < node->keys_count && data > node->keys[i]) {
      ++i;
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

static void free_node_recursive(B_node *node) {
  if (!node)
    return;

  if (!node->is_leaf) {
    for (int i = 0; i <= node->keys_count; i++) {
      free_node_recursive(node->children[i]);
    }
  }

  free(node);
}

void Free(B_tree *tree) {
  free_node_recursive(tree->root);
  tree->root = NULL;
}

B_tree_iterator IteratorBegin(B_tree *tree) {
  B_tree_iterator iter = {0};

  if (!tree->root) {
    iter.node = NULL;
    iter.position = -1;
    return iter;
  }

  B_node *cur = tree->root;
  while (!cur->is_leaf) {
    cur = cur->children[0];
  }
  iter.node = cur;
  iter.position = -1;
  return iter;
}

int Next(B_tree_iterator *iter) {

  if (!iter->node)
    return 0;

  B_node *node = iter->node;
  int pos = iter->position;

  if (node->is_leaf) {
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

  // Идем вверх по дереву
  B_node *cur = node;
  while (cur->parent) {
    B_node *p = cur->parent;

    int i = 0;
    while (i <= p->keys_count && p->children[i] != cur) {
      i++;
    }

    if (i < p->keys_count) {
      iter->node = p;
      iter->position = i;
      return 1;
    }

    cur = p;
  }

  // Достигли корня и прошли все ключи
  iter->node = NULL;
  return 0;
}

int Key(B_tree_iterator *iter) { return iter->node->keys[iter->position]; }