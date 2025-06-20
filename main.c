#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "labH.h"

// ---------- insert_OneNode_returnValidVal_no1 ----------
void insert_OneNode_returnValidVal_no1() {
    Node* root = NULL;
    root = insert(root, 10, 100);
    assert(root != NULL);
    free_tree(root);
}

// ---------- insert_DuplicateKeys_returnValidVal_no2 ----------
void insert_DuplicateKeys_returnValidVal_no2() {
    Node* root = NULL;
    root = insert(root, 5, 10);
    root = insert(root, 5, 20);
    assert(root != NULL);
    free_tree(root);
}

// ---------- range_sum_EmptyTree_returnZero_no3 ----------
void range_sum_EmptyTree_returnZero_no3() {
    Node* root = NULL;
    int result = range_sum(root, 0, 10);
    assert(result == 0);
}

// ---------- range_sum_SingleInRange_returnValidVal_no4 ----------
void range_sum_SingleInRange_returnValidVal_no4() {
    Node* root = NULL;
    root = insert(root, 7, 30);
    int result = range_sum(root, 7, 8);
    assert(result == 30);
    free_tree(root);
}

// ---------- range_sum_FullRange_returnValidVal_no5 ----------
void range_sum_FullRange_returnValidVal_no5() {
    Node* root = NULL;
    root = insert(root, 1, 5);
    root = insert(root, 3, 10);
    root = insert(root, 7, 15);
    int result = range_sum(root, 0, 10);
    assert(result == 30);
    free_tree(root);
}

// ---------- range_sum_LowerBoundExclusive_returnZero_no6 ----------
void range_sum_LowerBoundExclusive_returnZero_no6() {
    Node* root = NULL;
    root = insert(root, 5, 20);
    int result = range_sum(root, 6, 10);
    assert(result == 0);
    free_tree(root);
}

// ---------- insert_ManyNodes_returnValidVal_no7 ----------
void insert_ManyNodes_returnValidVal_no7() {
    Node* root = NULL;
    root = insert(root, 1, 1);
    root = insert(root, 2, 2);
    root = insert(root, 3, 3);
    root = insert(root, 4, 4);
    root = insert(root, 5, 5);
    assert(root != NULL);
    free_tree(root);
}

// ---------- range_sum_UpperBoundEqual_returnValidVal_no8 ----------
void range_sum_UpperBoundEqual_returnValidVal_no8() {
    Node* root = NULL;
    root = insert(root, 2, 10);
    root = insert(root, 4, 20);
    int result = range_sum(root, 2, 4); // includes 2, excludes 4
    assert(result == 10);
    free_tree(root);
}

// ---------- free_tree_EmptyTree_returnNull_no9 ----------
void free_tree_EmptyTree_returnNull_no9() {
    Node* root = NULL;
    free_tree(root);
    assert(1);
}

// ---------- insert_NegativeKey_returnValidVal_no10 ----------
void insert_NegativeKey_returnValidVal_no10() {
    Node* root = NULL;
    root = insert(root, -10, 99);
    assert(root != NULL);
    free_tree(root);
}

int main() {

    insert_OneNode_returnValidVal_no1();
    insert_DuplicateKeys_returnValidVal_no2();
    range_sum_EmptyTree_returnZero_no3();
    range_sum_SingleInRange_returnValidVal_no4();
    range_sum_FullRange_returnValidVal_no5();
    range_sum_LowerBoundExclusive_returnZero_no6();
    insert_ManyNodes_returnValidVal_no7();
    range_sum_UpperBoundEqual_returnValidVal_no8();
    free_tree_EmptyTree_returnNull_no9();
    insert_NegativeKey_returnValidVal_no10();

    printf("Test Passed Successfully");

    return 0;
}
