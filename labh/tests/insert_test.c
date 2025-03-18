#include "../deps/criterion-2.4.2/include/criterion/criterion.h" // IWYU pragma: keep
#include <stdio.h>
#include "../include/rb_tree.h"

Test(insert_tests, empty_root) {
  rb_tree *root = NULL;
  insert(&root, 8);

  cr_assert(root->key == 8);
  cr_assert(root->c = BLACK);
}

Test(insert_tests, insert_into_non_empty_tree) {
    rb_tree *root = NULL;
    insert(&root, 8);
    insert(&root, 3);
    insert(&root, 10);
    
    cr_assert(root->key == 8);
    cr_assert(root->left->key == 3);
    cr_assert(root->right->key == 10);
    cr_assert(root->left->c == RED);
    cr_assert(root->right->c == RED);
    cr_assert(root->c == BLACK);
}

Test(insert_tests, insert_causing_rotation) {
    rb_tree *root = NULL;
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 15);

    cr_assert(root->key == 15);
    cr_assert(root->left->key == 10);
    cr_assert(root->right->key == 20);
    cr_assert(root->c == BLACK);
    cr_assert(root->left->c == RED);
    cr_assert(root->right->c == RED);
}

Test(insert_tests, insert_causing_color_change) {
    rb_tree *root = NULL;
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);

    cr_assert(root->key == 20);
    cr_assert(root->left->key == 10);
    cr_assert(root->right->key == 30);
    cr_assert(root->c == BLACK);
    cr_assert(root->left->c == RED);
    cr_assert(root->right->c == RED);
}
