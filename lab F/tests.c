#include <stdio.h>
#include <assert.h>
#include "tests.h"

void create_node_withPositiveValue_returnValidVal() {
    Node* node = create_node(10, NULL);
    assert(node != NULL);
    assert(node->value == 10);
    assert(node->subtree_size == 1);
    assert(node->parent == NULL);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node);
}

void create_node_withNegativeValue_returnValidVal() {
    Node* node = create_node(-5, NULL);
    assert(node != NULL);
    assert(node->value == -5);
    assert(node->subtree_size == 1);
    assert(node->parent == NULL);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node);
}

void create_node_withNullParent_returnValidVal() {
    Node* node = create_node(0, NULL);
    assert(node != NULL);
    assert(node->value == 0);
    assert(node->subtree_size == 1);
    assert(node->parent == NULL);
    free(node);
}

void add_node_toEmptyTree_returnValidVal() {
    Node* root = NULL;
    add_node(&root, 10);
    assert(root != NULL);
    assert(root->value == 10);
    assert(root->subtree_size == 1);
    free_tree(root);
}

void add_node_toTreeWithMultipleNodes_returnValidVal() {
    Node* root = NULL;
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 15);
    assert(root->subtree_size == 3);
    assert(root->left->value == 5);
    assert(root->right->value == 15);
    free_tree(root);
}

void add_node_toTreeWithDuplicateValues_returnValidVal() {
    Node* root = NULL;
    add_node(&root, 10);
    add_node(&root, 10);
    assert(root->subtree_size == 2);
    assert(root->left->value == 10);
    free_tree(root);
}

void delete_node_withLeaf_returnTrue() {
    Node* root = NULL;
    add_node(&root, 10);
    add_node(&root, 5);
    delete_node(&root, 5);
    assert(root->left == NULL);
    assert(root->subtree_size == 1);
    free_tree(root);
}

void delete_node_withRootAndSingleChild_returnTrue() {
    Node* root = NULL;
    add_node(&root, 10);
    add_node(&root, 15);
    delete_node(&root, 10);
    assert(root->value == 15);
    assert(root->subtree_size == 1);
    free_tree(root);
}

void delete_node_withTwoChildren_returnTrue() {
    Node* root = NULL;
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 15);
    delete_node(&root, 10);
    assert(root->value == 15);
    assert(root->subtree_size == 2);
    assert(root->left->value == 5);
    assert(root->left->subtree_size == 1);
    free_tree(root);
}


void inorder_traversal_withEmptyTree_returnTrue() {
    Node* root = NULL;
    inorder_traversal(root);
}

void inorder_traversal_withSingleNode_returnValidVal() {
    Node* root = NULL;
    add_node(&root, 10);
    inorder_traversal(root);
    free_tree(root);
}

void inorder_traversal_withMultipleNodes_returnValidVal() {
    Node* root = NULL;
    add_node(&root, 10);
    add_node(&root, 5);
    add_node(&root, 15);
    inorder_traversal(root);
    free_tree(root);
}

void TESTS() {
    create_node_withPositiveValue_returnValidVal();
    create_node_withNegativeValue_returnValidVal();
    create_node_withNullParent_returnValidVal();

    add_node_toEmptyTree_returnValidVal();
    add_node_toTreeWithMultipleNodes_returnValidVal();
    add_node_toTreeWithDuplicateValues_returnValidVal();

    delete_node_withLeaf_returnTrue();
    delete_node_withRootAndSingleChild_returnTrue();
    delete_node_withTwoChildren_returnTrue();

    inorder_traversal_withEmptyTree_returnTrue();
    inorder_traversal_withSingleNode_returnValidVal();
    inorder_traversal_withMultipleNodes_returnValidVal();

    printf("All tests passed!\n");
}

