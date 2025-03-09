#include "treap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_empty_tree() {
    Node* root = NULL;
    assert(get_sum(root, 0, 10) == 0);
}

void test_single_node() {
    Node* node = create_node(5, 100);
    Node* root = insert(NULL, node);
    assert(get_sum(root, 0, 10) == 100);
    assert(get_sum(root, 6, 10) == 0);
    free_tree(root);
}

void test_multiple_nodes() {
    Node* root = NULL;
    root = insert(root, create_node(1, 10));
    root = insert(root, create_node(3, 20));
    root = insert(root, create_node(5, 30));
    assert(get_sum(root, 2, 4) == 20);
    free_tree(root);
}

void test_edge_cases() {
    Node* node = create_node(5, 50);
    Node* root = insert(NULL, node);
    assert(get_sum(root, 5, 5) == 0);
    assert(get_sum(root, 5, 6) == 50);
    free_tree(root);
}

void test_invalid_range() {
    Node* root = NULL;
    root = insert(root, create_node(2, 2));
    root = insert(root, create_node(4, 4));
    assert(get_sum(root, 5, 1) == 0);
    free_tree(root);
}

void test_full_coverage() {
    Node* root = NULL;
    for (int i = 1; i <= 5; i++)
        root = insert(root, create_node(i, i * 10));
    assert(get_sum(root, 0, 10) == 150);
    free_tree(root);
}

void test_same_priority() {
    Node* root = NULL;
    root = insert(root, create_node(1, 10));
    root = insert(root, create_node(3, 20));
    root = insert(root, create_node(5, 30));
    assert(get_sum(root, 2, 4) == 20);
    free_tree(root);
}

void test_partial_overlap() {
    Node* root = NULL;
    root = insert(root, create_node(2, 2));
    root = insert(root, create_node(4, 4));
    root = insert(root, create_node(6, 6));
    assert(get_sum(root, 3, 7) == 4 + 6);
    free_tree(root);
}

void test_max_element() {
    Node* root = insert(NULL, create_node(10, 100));
    assert(get_sum(root, 10, 11) == 100);
    free_tree(root);
}

void test_duplicate_keys() {
    Node* root = NULL;
    root = insert(root, create_node(2, 5));
    root = insert(root, create_node(2, 10));
    assert(get_sum(root, 2, 3) == 15);
    free_tree(root);
}

int main() {
    test_empty_tree();
    test_single_node();
    test_multiple_nodes();
    test_edge_cases();
    test_invalid_range();
    test_full_coverage();
    test_same_priority();
    test_partial_overlap();
    test_max_element();
    test_duplicate_keys();
    printf("All 10 tests passed!\n");
    return 0;
}