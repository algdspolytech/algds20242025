#include "../deps/criterion-2.4.2/include/criterion/criterion.h" // IWYU pragma: keep
#include "../include/rb_tree.h"
#include <stdio.h>

Test(delete_tests, delete_node_with_two_children) {
  rb_tree *root = NULL;
  insert(&root, 20);
  insert(&root, 10);
  insert(&root, 30);
  insert(&root, 25);
  insert(&root, 35);

  rb_tree *node_to_delete = search(root, 30);
  delete (&root, node_to_delete);

  cr_assert(root->key == 20);
  cr_assert(root->right->key == 35);
  cr_assert(root->right->left->key == 25);
}

Test(delete_tests, delete_node_with_one_child) {
  rb_tree *root = NULL;
  insert(&root, 20);
  insert(&root, 10);
  insert(&root, 30);
  insert(&root, 25);

  rb_tree *node_to_delete = search(root, 30);
  delete (&root, node_to_delete);

  cr_assert(root->key == 20);
  cr_assert(root->right->key == 25);
}

Test(delete_tests, delete_root) {
  rb_tree *root = NULL;
  insert(&root, 20);
  insert(&root, 10);
  insert(&root, 30);

  rb_tree *node_to_delete = search(root, 20);
  delete (&root, node_to_delete);

  cr_assert(root->key == 30);
  cr_assert(root->left->key == 10);
  cr_assert(root->c == BLACK);
}

Test(delete_tests, delete_non_existent_node) {
  rb_tree *root = NULL;
  insert(&root, 20);
  insert(&root, 10);
  insert(&root, 30);

  rb_tree *node_to_delete = search(root, 40);
  cr_assert(node_to_delete == NULL);
}

Test(delete_tests, delete_leaf_node) {
  rb_tree *root = NULL;
  insert(&root, 20);
  insert(&root, 10);
  insert(&root, 30);
  insert(&root, 25);

  rb_tree *node_to_delete = search(root, 10);
  delete (&root, node_to_delete);

  cr_assert(root->key == 25);
}

Test(delete_tests, delete_only_node) {
  rb_tree *root = NULL;
  insert(&root, 20);

  rb_tree *node_to_delete = search(root, 20);
  delete (&root, node_to_delete);

  cr_assert(root == NULL);
}
