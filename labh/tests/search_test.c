#include "../deps/criterion-2.4.2/include/criterion/criterion.h" // IWYU pragma: keep
#include "../include/rb_tree.h"
#include <stdlib.h>

void insert_nodes(rb_tree **root, int *keys, size_t size) {
    for (size_t i = 0; i < size; i++) {
        insert(root, keys[i]);
    }
}

Test(search_tests, search_existing_node) {
    rb_tree *root = NULL;
    int keys[] = {20, 10, 30, 25, 35};
    insert_nodes(&root, keys, sizeof(keys) / sizeof(keys[0]));

    rb_tree *result = search(root, 10);
    cr_assert_not_null(result, "Node with key 10 should exist.");
    cr_assert_eq(result->key, 10, "Expected key 10, but found %d.", result->key);
}

Test(search_tests, search_non_existing_node) {
    rb_tree *root = NULL;
    int keys[] = {20, 10, 30, 25, 35};
    insert_nodes(&root, keys, sizeof(keys) / sizeof(keys[0]));

    rb_tree *result = search(root, 15);
    cr_assert_null(result, "Node with key 15 should not exist.");
}

Test(search_tests, search_root_node) {
    rb_tree *root = NULL;
    int keys[] = {20};
    insert_nodes(&root, keys, sizeof(keys) / sizeof(keys[0]));

    rb_tree *result = search(root, 20);
    cr_assert_not_null(result, "Root node with key 20 should exist.");
    cr_assert_eq(result->key, 20, "Expected key 20, but found %d.", result->key);
}

Test(search_tests, search_empty_tree) {
    rb_tree *root = NULL;

    rb_tree *result = search(root, 10);
    cr_assert_null(result, "Search in an empty tree should return NULL.");
}

