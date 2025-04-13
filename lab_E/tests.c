#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subtree.h"





// tests
void test_empty_tree() {
    TreeNode* root = NULL;
    assert(compute_subtree_width(root) == 0);
}

void test_single_node() {
    TreeNode* root = create_node("test");
    compute_subtree_width(root);
    assert(root->subtree_width == 4);
    free_tree(root);
}

void test_root_with_left_child() {
    TreeNode* root = create_node("A");
    root->left = create_node("BB");
    compute_subtree_width(root);
    assert(root->subtree_width == 3);
    assert(root->left->subtree_width == 2);
    free_tree(root);
}

void test_root_with_right_child() {
    TreeNode* root = create_node("A");
    root->right = create_node("CCC");
    compute_subtree_width(root);
    assert(root->subtree_width == 4);
    assert(root->right->subtree_width == 3);
    free_tree(root);
}

void test_both_children() {
    TreeNode* root = create_node("A");
    root->left = create_node("BB");
    root->right = create_node("CCC");
    compute_subtree_width(root);
    assert(root->subtree_width == 6);
    assert(root->left->subtree_width == 2);
    assert(root->right->subtree_width == 3);
    free_tree(root);
}

void test_two_level_left_subtree() {
    TreeNode* root = create_node("R");
    root->left = create_node("L1");
    root->left->left = create_node("L2");
    compute_subtree_width(root);
    assert(root->subtree_width == 5);
    assert(root->left->subtree_width == 4);
    assert(root->left->left->subtree_width == 2);
    free_tree(root);
}

void test_two_level_right_subtree() {
    TreeNode* root = create_node("R");
    root->right = create_node("R1");
    root->right->right = create_node("R2");
    compute_subtree_width(root);
    assert(root->subtree_width == 5);
    assert(root->right->subtree_width == 4);
    assert(root->right->right->subtree_width == 2);
    free_tree(root);
}

void test_nodes_with_empty_strings() {
    TreeNode* root = create_node("");
    root->left = create_node("");
    root->right = create_node("a");
    compute_subtree_width(root);
    assert(root->subtree_width == 1);
    assert(root->left->subtree_width == 0);
    assert(root->right->subtree_width == 1);
    free_tree(root);
}

void test_mixed_children() {
    TreeNode* root = create_node("R");
    root->left = create_node("L");
    root->left->left = create_node("LL");
    root->left->right = create_node("LRR");
    root->right = create_node("R");
    root->right->right = create_node("RR");
    compute_subtree_width(root);
    assert(root->subtree_width == 10);
    assert(root->left->subtree_width == 6);
    assert(root->left->left->subtree_width == 2);
    assert(root->left->right->subtree_width == 3);
    assert(root->right->subtree_width == 3);
    assert(root->right->right->subtree_width == 2);
    free_tree(root);
}

void test_complex_tree() {
    TreeNode* root = create_node("A");
    root->left = create_node("B");
    root->left->right = create_node("C");
    root->left->right->left = create_node("D");
    root->left->right->right = create_node("E");
    root->right = create_node("F");
    root->right->left = create_node("G");
    root->right->left->left = create_node("H");
    root->right->left->right = create_node("I");
    compute_subtree_width(root);
    assert(root->subtree_width == 9);
    assert(root->left->subtree_width == 4);
    assert(root->left->right->subtree_width == 3);
    assert(root->right->subtree_width == 4);
    assert(root->right->left->subtree_width == 3);
    free_tree(root);
}

void test_deeper_tree() {
    TreeNode* root = create_node("R");
    root->left = create_node("L1");
    root->left->left = create_node("L2");
    root->left->left->left = create_node("L3");
    root->right = create_node("R1");
    root->right->right = create_node("R2");
    root->right->right->right = create_node("R3");
    compute_subtree_width(root);
    assert(root->subtree_width == 13);
    assert(root->left->subtree_width == 6);
    assert(root->left->left->subtree_width == 4);
    assert(root->left->left->left->subtree_width == 2);
    assert(root->right->subtree_width == 6);
    assert(root->right->right->subtree_width == 4);
    assert(root->right->right->right->subtree_width == 2);
    free_tree(root);
}

void test_more_complex_tree() {
    TreeNode* root = create_node("Root");
    root->left = create_node("L");
    root->left->left = create_node("LL");
    root->left->right = create_node("LR");
    root->left->right->right = create_node("LRR");
    root->right = create_node("R");
    root->right->left = create_node("RL");
    root->right->right = create_node("RR");
    root->right->right->left = create_node("RRL");
    compute_subtree_width(root);
    assert(root->subtree_width == 20);
    assert(root->left->subtree_width == 8);
    assert(root->left->left->subtree_width == 2);
    assert(root->left->right->subtree_width == 5);
    assert(root->left->right->right->subtree_width == 3);
    assert(root->right->subtree_width == 8);
    assert(root->right->left->subtree_width == 2);
    assert(root->right->right->subtree_width == 5);
    assert(root->right->right->left->subtree_width == 3);
    free_tree(root);
}

int main() {
    test_empty_tree();
    test_single_node();
    test_root_with_left_child();
    test_root_with_right_child();
    test_both_children();
    test_two_level_left_subtree();
    test_two_level_right_subtree();
    test_nodes_with_empty_strings();
    test_mixed_children();
    test_complex_tree();
    test_deeper_tree();
    test_more_complex_tree();

    printf("All tests passed!\n");
    return 0;
}