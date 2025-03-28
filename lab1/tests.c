#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "struct.h"
#include "funcs.h"

void testÑreateNode_no1() {
    Node* node = createNode(10);
    assert(node != NULL);
    assert(node->data == 10);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free(node);
}

void testInsert_no2() {
    Node* root = NULL;
    root = insert(root, 10);
    assert(root->data == 10);
    root = insert(root, 5);
    assert(root->left->data == 5);
    root = insert(root, 15);
    assert(root->right->data == 15);
    free(root);
}

void testFindKthSmallestBasic_no3() {
    Node* root = NULL;
    int values[] = { 20, 10, 30, 5, 15, 25, 35 };
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    Node* kth = findKthSmallest(root, 3);
    assert(kth != NULL);
    assert(kth->data == 15);  

    free(root);
}

void testFindKthSmallestEdge_no4() {
    Node* root = NULL;
    int values[] = { 20, 10, 30, 5, 15, 25, 35 };
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    Node* kth = findKthSmallest(root, 1);
    assert(kth != NULL);
    assert(kth->data == 5); 

    kth = findKthSmallest(root, 7);
    assert(kth != NULL);
    assert(kth->data == 35);  

    free(root);
}

void testFindKthSmallestOutOfBounds_no5() {
    Node* root = NULL;
    int values[] = { 20, 10, 30, 5, 15, 25, 35 };
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    Node* kth = findKthSmallest(root, 10);
    assert(kth == NULL);  

    free(root);
}

void testFindKthSmallestSingleElement_no6() {
    Node* root = createNode(42);
    Node* kth = findKthSmallest(root, 1);
    assert(kth != NULL);
    assert(kth->data == 42);
    free(root);
}

void testFindKthSmallestTwoElements_no7() {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);

    Node* kth = findKthSmallest(root, 1);
    assert(kth != NULL);
    assert(kth->data == 30);  

    kth = findKthSmallest(root, 2);
    assert(kth != NULL);
    assert(kth->data == 50); 

    free(root);
}

void testFindKthSmallestLargeTree_no8() {
    Node* root = NULL;
    for (int i = 1; i <= 100; i++) {
        root = insert(root, i);
    }

    Node* kth = findKthSmallest(root, 50);
    assert(kth != NULL);
    assert(kth->data == 50);

    free(root);
}

void testFindKthSmallestRepeatedValues_no9() {
    Node* root = NULL;
    int values[] = { 10, 20, 10, 30, 10, 40, 10 };
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    Node* kth = findKthSmallest(root, 3);
    assert(kth != NULL);
    assert(kth->data == 10);  

    free(root);
}

void testFindKthSmallestRightSkewedTree_no10() {
    Node* root = NULL;
    for (int i = 1; i <= 10; i++) {
        root = insert(root, i);
    }

    Node* kth = findKthSmallest(root, 5);
    assert(kth != NULL);
    assert(kth->data == 5);

    free(root);
}