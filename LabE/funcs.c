#include "funcs.h"

TreeNode *create_node(int value) {
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  node->value = value;
  node->width = 0;
  node->left = NULL;
  node->right = NULL;
  return node;
}

int calculate_subtree_width(TreeNode *node) {
  if (!node) {
    return 0;
  }

  char buffer[20];
  sprintf_s(buffer, sizeof(buffer), "%d", node->value);
  int node_width = strlen(buffer);

  int left_width = calculate_subtree_width(node->left);
  int right_width = calculate_subtree_width(node->right);

  node->width = node_width + left_width + right_width;

  return node->width;
}

void print_tree_with_width(TreeNode *node, int level) {
  if (!node) {
    return;
  }

  for (int i = 0; i < level; i++) {
    printf("  ");
  }
  printf("%d\n", node->value);

  for (int i = 0; i < level; i++) {
    printf("  ");
  }
  printf("(%d)\n", node->width);

  print_tree_with_width(node->left, level + 1);
  print_tree_with_width(node->right, level + 1);
}

void free_tree(TreeNode *node) {
  if (!node) {
    return;
  }
  free_tree(node->left);
  free_tree(node->right);
  free(node);
}