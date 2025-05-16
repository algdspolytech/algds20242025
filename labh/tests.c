//
//  tests.c
//  LabH
//
//  Created by Фёдор Филь on 22.03.2025.
//

#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structs.h"
#include "funcs.h"

void test_newNode_key_value_no1(void) {
    Node* node = newNode(42, 12345L);
    assert(node != NULL);
    assert(node->key == 42);
    assert(node->value == 12345L);
    free(node);
}

void test_newNode_left_right_null_no2(void) {
    Node* node = newNode(17, 54321L);
    assert(node != NULL);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node);
}

void test_newNode_negative_values_no3(void) {
    Node* node = newNode(-100, -987654321L);
    assert(node != NULL);
    assert(node->key == -100);
    assert(node->value == -987654321L);
    free(node);
}

void test_insert_first_element_no4(void) {
    Node* root = NULL;
    root = insert(root, 10, 100);
    
    assert(root != NULL);
    assert(root->key == 10);
    assert(root->value == 100);
    assert(root->sum == 100);
    assert(root->left == NULL);
    assert(root->right == NULL);
}

void test_insert_left_child_no5(void) {
    Node* root = newNode(20, 200);
    root = insert(root, 10, 100);
    
    assert(root != NULL);
    assert(root->key == 20);
    assert(root->value == 200);
    assert(root->sum == 300);
    assert(root->left != NULL);
    assert(root->left->key == 10);
    assert(root->left->value == 100);
    assert(root->left->sum == 100);
    assert(root->right == NULL);
}

void test_insert_right_child_no6(void) {
    Node* root = newNode(10, 100);
    root = insert(root, 20, 200);
    
    assert(root != NULL);
    assert(root->key == 10);
    assert(root->value == 100);
    assert(root->sum == 300);
    assert(root->left == NULL);
    assert(root->right != NULL);
    assert(root->right->key == 20);
    assert(root->right->value == 200);
    assert(root->right->sum == 200);
}

void test_rangeSum_empty_tree_no7(void) {
    Node* root = NULL;
    long result = rangeSum(root, 1, 10);
    assert(result == 0);
}

void test_rangeSum_single_node_inside_range_no8(void) {
    Node* root = newNode(5, 100);
    long result = rangeSum(root, 1, 10);
    assert(result == 100);
}

void test_rangeSum_multiple_nodes_inside_range_no9(void) {
    Node* root = newNode(10, 100);
    root = insert(root, 5, 50);
    root = insert(root, 15, 150);
    root = insert(root, 20, 200);
    
    long result = rangeSum(root, 8, 18);
    assert(result == 250);  
}

void test_rangeSum_out_of_range_no10(void) {
    Node* root = newNode(5, 100);
    root = insert(root, 8, 150);
    root = insert(root, 3, 50);
    long result = rangeSum(root, 10, 20);
    assert(result == 0);
}
