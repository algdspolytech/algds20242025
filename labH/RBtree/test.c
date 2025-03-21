#include "test.h"


void test_insert_SingleElement_returnValidVal() {
    RBTree* tree = createRBTree();
    insert(tree, 10);
    assert(tree->root->key == 10);
    assert(tree->root->color == BLACK);
}

void test_insert_MultipleElements_returnValidVal() {
    RBTree* tree = createRBTree();
    insert(tree, 10);
    insert(tree, 5);
    insert(tree, 15);
    assert(tree->root->key == 10);
    assert(tree->root->left->key == 5);
    assert(tree->root->right->key == 15);
}

void test_leftRotate_SimpleCase_returnValidVal() {
    RBTree* tree = createRBTree();
    insert(tree, 10);
    insert(tree, 20);
    leftRotate(tree, tree->root);
    assert(tree->root->key == 20);
    assert(tree->root->left->key == 10);
}

void test_rightRotate_SimpleCase_returnValidVal() {
    RBTree* tree = createRBTree();
    insert(tree, 20);
    insert(tree, 10);
    rightRotate(tree, tree->root);
    assert(tree->root->key == 10);
    assert(tree->root->right->key == 20);
}

void test_mergeTrees_TwoNonEmptyTrees_returnValidVal() {
    RBTree* t1 = createRBTree();
    RBTree* t2 = createRBTree();
    insert(t1, 10);
    insert(t2, 20);
    mergeTrees(t1, t2, 15);
    assert(t1->root->key == 15);
}

void test_insert_DuplicateValues_returnValidVal() {
    RBTree* tree = createRBTree();
    insert(tree, 10);
    insert(tree, 10);
    assert(tree->root->key == 10);
}

void test_mergeTrees_EmptyFirstTree_returnValidVal() {
    RBTree* t1 = createRBTree();
    RBTree* t2 = createRBTree();
    insert(t2, 10);
    insert(t2, 20);
    mergeTrees(t1, t2, 15);
    assert(t1->root->key == 15);
}

void test_mergeTrees_EmptySecondTree_returnValidVal() {
    RBTree* t1 = createRBTree();
    RBTree* t2 = createRBTree();
    insert(t1, 10);
    insert(t1, 5);
    mergeTrees(t1, t2, 15);
    assert(t1->root->key == 10);
}

void test_mergeTrees_BothEmptyTrees_returnValidVal() {
    RBTree* t1 = createRBTree();
    RBTree* t2 = createRBTree();
    mergeTrees(t1, t2, 15);
    assert(t1->root->key == 15);
}

void test_insert_RootColorAfterInsertion_returnBlack() {
    RBTree* tree = createRBTree();
    insert(tree, 10);
    assert(tree->root->color == BLACK);
}


void run_all_tests() {
    test_insert_SingleElement_returnValidVal();
    test_insert_MultipleElements_returnValidVal();
    test_leftRotate_SimpleCase_returnValidVal();
    test_rightRotate_SimpleCase_returnValidVal();
    test_mergeTrees_TwoNonEmptyTrees_returnValidVal();
    test_insert_DuplicateValues_returnValidVal();
    test_mergeTrees_EmptyFirstTree_returnValidVal();
    test_mergeTrees_EmptySecondTree_returnValidVal();
    test_mergeTrees_BothEmptyTrees_returnValidVal();
    test_insert_RootColorAfterInsertion_returnBlack();
	printf("All tests completed successfully.\n");
}