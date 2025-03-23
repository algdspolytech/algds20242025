#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"


void test_newNode_ValidValue_returnValidVal_no1() {
    Node *node = newNode(10);
    assert(node != NULL);
    assert(node->data == 10);
    assert(node->color == RED);
    free(node);
}

void test_createRBTree_EmptyTree_returnValidVal_no2() {
    RBTree *tree = createRBTree();
    assert(tree != NULL);
    assert(tree->root == tree->TNULL);
    assert(tree->TNULL->color == BLACK);
    freeRBTree(tree);
}

void test_insert_SingleNode_TreeRootSet_no3() {
    RBTree *tree = createRBTree();
    insert(tree, 15);
    assert(tree->root->data == 15);
    assert(tree->root->color == BLACK);
    freeRBTree(tree);
}

void test_insert_MultipleNodes_TreeStructureValid_no4() {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 15);
    assert(tree->root->data == 10);
    assert(tree->root->right->data == 20);
    assert(tree->root->right->left->data == 15);
    freeRBTree(tree);
}

void test_search_ExistingElement_returnValidNode_no5() {
    RBTree *tree = createRBTree();
    insert(tree, 25);
    insert(tree, 30);
    Node *found = search(tree, 25);
    assert(found != NULL);
    assert(found->data == 25);
    freeRBTree(tree);
}

void test_search_NonExistingElement_returnNull_no6() {
    RBTree *tree = createRBTree();
    insert(tree, 35);
    Node *found = search(tree, 40);
    assert(found == NULL);
    freeRBTree(tree);
}

void test_insert_DuplicateElement_TreeStructureUnchanged_no7() {
    RBTree *tree = createRBTree();
    insert(tree, 50);
    insert(tree, 50);
    assert(tree->root->data == 50);
    assert(tree->root->left == tree->TNULL);
    assert(tree->root->right == tree->TNULL);
    freeRBTree(tree);
}

void test_fixViolation_ColorsAdjustedAfterInsert_no8() {
    RBTree *tree = createRBTree();
    insert(tree, 30);
    insert(tree, 20);
    insert(tree, 10);
    assert(tree->root->color == BLACK);
    assert(tree->root->left->color == RED);
    assert(tree->root->left->left->color == BLACK);
    freeRBTree(tree);
}

void test_leftRotate_ValidLeftRotation_no9() {
    RBTree *tree = createRBTree();
    insert(tree, 10);
    insert(tree, 20);
    Node *node = tree->root; // 10
    leftRotate(tree, node);
    assert(tree->root->data == 20);
    assert(tree->root->left->data == 10);
    freeRBTree(tree);
}

void test_rightRotate_ValidRightRotation_no10() {
    RBTree *tree = createRBTree();
    insert(tree, 20);
    insert(tree, 10);
    Node *node = tree->root->right;
    rightRotate(tree, node);
    assert(tree->root->data == 10);
    assert(tree->root->right->data == 20);
    freeRBTree(tree);
}

void test_search_EmptyTree_returnNull_11() {
    RBTree *tree = createRBTree();
    Node *found = search(tree, 1);
    assert(found == NULL);
    freeRBTree(tree);
}


int main() {
    test_newNode_ValidValue_returnValidVal_no1();
    test_createRBTree_EmptyTree_returnValidVal_no2();
    test_insert_SingleNode_TreeRootSet_no3();
    test_insert_MultipleNodes_TreeStructureValid_no4();
    test_search_ExistingElement_returnValidNode_no5();
    test_search_NonExistingElement_returnNull_no6();
    test_insert_DuplicateElement_TreeStructureUnchanged_no7();
    test_fixViolation_ColorsAdjustedAfterInsert_no8();
    test_leftRotate_ValidLeftRotation_no9();
    test_rightRotate_ValidRightRotation_no10();
    test_search_EmptyTree_returnNull_no11();

    printf("All tests ran fine!\n");
    return 0;
}
