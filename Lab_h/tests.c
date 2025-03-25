#include "treap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void testInsertToEmptyTree_no1() {
    Node* root = NULL;
    root = insert(root, 10);
    assert(search(root, 10) == true);
    freeTree(root);
}

void testInsertMultipleElements_no2() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    assert(search(root, 10) == true);
    assert(search(root, 20) == true);
    assert(search(root, 5) == true);
    freeTree(root);
}

void testdeleteElement_no3() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = deleteNode(root, 10);
    assert(search(root, 10) == false);
    assert(search(root, 20) == true);
    freeTree(root);
}

void testdeleteNonExistentElement_no4() {
    Node* root = NULL;
    root = insert(root, 10);
    root = deleteNode(root, 20);
    assert(search(root, 10) == true);
    assert(search(root, 20) == false);
    freeTree(root);
}

void testSearchInEmptyTree_no5() {
    Node* root = NULL;
    assert(search(root, 10) == false);
}

void testSearchNonExistentElement_no6() {
    Node* root = NULL;
    root = insert(root, 10);
    assert(search(root, 20) == false);
    freeTree(root);
}

void testInsertDuplicateElement_no7() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 10);
    assert(search(root, 10) == true);
    freeTree(root);
}

void testdeleteFromEmptyTree_no8() {
    Node* root = NULL;
    root = deleteNode(root, 10);
    assert(root == NULL);
}

void testInsertAnddeleteAllElements_no9() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = deleteNode(root, 10);
    root = deleteNode(root, 20);
    assert(root == NULL);
}

void testInsertAnddeleteRandomOrder_no10() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = deleteNode(root, 20);
    root = deleteNode(root, 5);
    assert(search(root, 10) == true);
    assert(search(root, 20) == false);
    assert(search(root, 5) == false);
    freeTree(root);
}

int main() {
    srand(time(NULL));

    testInsertToEmptyTree_no1();
    testInsertMultipleElements_no2();
    testdeleteElement_no3();
    testdeleteNonExistentElement_no4();
    testSearchInEmptyTree_no5();
    testSearchNonExistentElement_no6();
    testInsertDuplicateElement_no7();
    testdeleteFromEmptyTree_no8();
    testInsertAnddeleteAllElements_no9();
    testInsertAnddeleteRandomOrder_no10();

    printf("All tests passed!\n");
    return 0;
}