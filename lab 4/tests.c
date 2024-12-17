#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib.h"
#include "tests.h"


void createNode_init_nodeCreated_no1() {
    Node *node = createNode("test");
    assert(node != NULL);
    assert(strcmp(node->data, "test") == 0);
    assert(node->left == NULL);
    assert(node->right == NULL);
    freeTree(node);
}

void insert_emptyTree_treeWithOneElem_no2() {
    Node *root = NULL;
    root = insert(root, "test");
    assert(root != NULL);
    assert(strcmp(root->data, "test") == 0);
    freeTree(root);
}

void insert_oneElement_returnVaildVal_no3() {
    Node *root = createNode("test");
    root = insert(root, "apple");
    assert(strcmp(root->left->data, "apple") == 0);
    freeTree(root);
}

void insert_multipleElements_returnValidVal_no4() {
    Node *root = createNode("banana");
    root = insert(root, "apple");
    root = insert(root, "cherry");
    assert(strcmp(root->left->data, "apple") == 0);
    assert(strcmp(root->right->data, "cherry") == 0);
    freeTree(root);
}

void printInOrder_printing_noErrors_no5() {
    Node *root = createNode("banana");
    insert(root, "apple");
    insert(root, "cherry");
    freeTree(root);
}

void freeTree_freeing_noErrors_no6() {
    Node *root = createNode("test");
    root = insert(root, "apple");
    root = insert(root, "banana");
    freeTree(root);
}

void insert_duplicates_returnValidVal_no7() {
    Node *root = createNode("test");
    root = insert(root, "test"); 
    assert(strcmp(root->data, "test") == 0);
    freeTree(root);
}

void insert_rightBranch_returnValidVal_no8() {
    Node *root = createNode("banana");
    insert(root, "cherry");
    assert(root->right != NULL);
    assert(strcmp(root->right->data, "cherry") == 0);
    freeTree(root);
}

void insert_leftBranch_retuenValidVal_no9() {
    Node *root = createNode("banana");
    insert(root, "apple");
    assert(root->left != NULL);
    assert(strcmp(root->left->data, "apple") == 0);
    freeTree(root);
}

void free_nodeWithData_returnValidVal_no10() {
    Node *root = createNode("test");
    assert(root != NULL);
    freeTree(root);
}


void runAllTests() {
    createNode_init_nodeCreated_no1();
    insert_emptyTree_treeWithOneElem_no2();
    insert_oneElement_returnVaildVal_no3();
    insert_multipleElements_returnValidVal_no4();
    printInOrder_printing_noErrors_no5();
    freeTree_freeing_noErrors_no6();
    insert_duplicates_returnValidVal_no7();
    insert_rightBranch_returnValidVal_no8();
    insert_leftBranch_retuenValidVal_no9();
    free_nodeWithData_returnValidVal_no10();

    
    printf("All tests ran well!\n");
}
