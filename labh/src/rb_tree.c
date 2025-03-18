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

rb_tree *tree_minimum(rb_tree *node) {
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

rb_tree *tree_next(rb_tree *node) {
  if (node->right != NULL) {
    return tree_minimum(node);
  }
  rb_tree *node_parent = node->parent;
  while (node_parent != NULL && node == node_parent->right) {
    node = node_parent;
    node_parent = node_parent->parent;
  }
  return node_parent;
}

color get_color(rb_tree *node) {
  if (node == NULL) {
    return BLACK;
  } else {
    return node->c;
  }
}

void fix_after_del(rb_tree **root, rb_tree *node) {
  while (node != *root && get_color(node) == BLACK) {
    if (node == node->parent->left) {
      rb_tree *node_tmp = node->parent->right;
      if (get_color(node_tmp) == RED) {
        node_tmp->c = BLACK;
        node_tmp->parent->c = RED;
        left_rotate(root, node->parent);
        node_tmp = node->parent->right;
      }
      if (get_color(node_tmp->left) == BLACK &&
          get_color(node_tmp->right) == BLACK) {
        node_tmp->c = RED;
        node_tmp = node_tmp->parent;
      } else {
        if (get_color(node_tmp->right) == BLACK) {
          node_tmp->left->c = BLACK;
          node_tmp->c = RED;
          right_rotate(root, node_tmp);
          node_tmp = node->parent->right;
        }
        node_tmp->c = get_color(node->parent);
        node->parent->c = BLACK;
        node_tmp->right->c = BLACK;
        left_rotate(root, node->parent);
        node = *root;
      }
    } else {
      rb_tree *node_tmp = node->parent->left;
      if (get_color(node_tmp) == RED) {
        node_tmp->c = BLACK;
        node_tmp->parent->c = RED;
        right_rotate(root, node->parent);
        node_tmp = node->parent->left;
      }
      if (get_color(node_tmp->right) == BLACK &&
          get_color(node_tmp->left) == BLACK) {
        node_tmp->c = RED;
        node_tmp = node_tmp->parent;
      } else {
        if (get_color(node_tmp->left) == BLACK) {
          node_tmp->right->c = BLACK;
          node_tmp->c = RED;
          left_rotate(root, node_tmp);
          node_tmp = node->parent->left;
        }
        node_tmp->c = get_color(node->parent);
        node->parent->c = BLACK;
        node_tmp->left->c = BLACK;
        right_rotate(root, node->parent);
        node = *root;
      }
    }
  }
  node->c = BLACK;
}

void delete(rb_tree **root, rb_tree *node) {
  if (node == NULL)
    return;

  rb_tree *node_parent = node;
  rb_tree *node_tmp = NULL;
  rb_tree *dummy = NULL;

  if (node->left != NULL && node->right != NULL) {
    rb_tree *successor = tree_minimum(node->right);
    node->key = successor->key;
    node_parent = successor;
  }

  node_tmp =
      (node_parent->left != NULL) ? node_parent->left : node_parent->right;

  if (node_tmp == NULL) {
    dummy = create_node(0, BLACK);
    dummy->parent = node_parent->parent;
    node_tmp = dummy;
  } else {
    node_tmp->parent = node_parent->parent;
  }

  if (node_parent->parent == NULL) {
    *root = node_tmp;
  } else if (node_parent == node_parent->parent->left) {
    node_parent->parent->left = node_tmp;
  } else {
    node_parent->parent->right = node_tmp;
  }

  if (get_color(node_parent) == BLACK) {
    fix_after_del(root, node_tmp);
  }

  if (dummy != NULL) {
    if (dummy->parent != NULL) {
      if (dummy->parent->left == dummy) {
        dummy->parent->left = NULL;
      } else {
        dummy->parent->right = NULL;
      }
    }
    if (*root == dummy) {
      *root = NULL;
    }
    free(dummy);
  }

  free(node_parent);

  if (*root != NULL) {
    (*root)->c = BLACK;
  }
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
