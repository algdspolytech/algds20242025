#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "struct.h"
#include "funcs.h"

void testSingleRoot_no1() {
    Node* root = createNode(10);
    assert(calculateMinLeafHeight(root, 0) == 0);
    freeTree(root);
}

void testRootWithOneChild_no2() {
    Node* root = createNode(10);
    root->left = createNode(5);
    assert(calculateMinLeafHeight(root, 0) == 1);
    freeTree(root);
}

void testFullBinaryTree_no3() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    assert(calculateMinLeafHeight(root, 0) == 1);
    freeTree(root);
}

void testLeftHeavyTree_no4() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->left->left = createNode(2);
    assert(calculateMinLeafHeight(root, 0) == 2);
    freeTree(root);
}

void testRightHeavyTree_no5() {
    Node* root = createNode(10);
    root->right = createNode(20);
    root->right->right = createNode(30);
    assert(calculateMinLeafHeight(root, 0) == 2);
    freeTree(root);
}

void testTreeWithDifferentDepthLeaves_no6() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->right = createNode(3);
    root->right->left = createNode(18);
    assert(calculateMinLeafHeight(root, 0) == 2);
    freeTree(root);
}

void testDeepBalancedTree_no7() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(12);
    root->right->right = createNode(18);
    assert(calculateMinLeafHeight(root, 0) == 2);
    freeTree(root);
}

void testDeepLeftTree_no8() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->left->left = createNode(3);
    root->left->left->left = createNode(1);
    assert(calculateMinLeafHeight(root, 0) == 3);
    freeTree(root);
}

void testEmptyTree_no9() {
    assert(calculateMinLeafHeight(NULL, 0) == INT_MAX);
}

void testAllLeavesAtSameDepth_no10() {
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(12);
    root->right->right = createNode(18);
    assert(calculateMinLeafHeight(root, 0) == 2);
    freeTree(root);
}