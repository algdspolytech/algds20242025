#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

void check_sums(TreapNode* node) {
    if (!node) return;
    int expected = node->c;
    if (node->left) expected += node->left->sum;
    if (node->right) expected += node->right->sum;
    if (node->sum != expected) {
        printf("Sum mismatch at node %d: expected %d, got %d\n", node->x, expected, node->sum);
        exit(1);
    }
    check_sums(node->left);
    check_sums(node->right);
}

void TestInsertAndSum_no1() {
    TreapNode* root = NULL;
    insert(&root, 10, 5);
    int sum = sum_range(&root, 10, 11);
    check_sums(root);
    printf("TestInsertAndSum_no1: %s\n", sum == 5 ? "Passed" : "Failed");
    free_treap(root);
}

void TestSumEmptyTree_no2() {
    TreapNode* root = NULL;
    int sum = sum_range(&root, 0, 10);
    printf("TestSumEmptyTree_no2: %s\n", sum == 0 ? "Passed" : "Failed");
    free_treap(root);
}

void TestSumExactInterval_no3() {
    TreapNode* root = NULL;
    insert(&root, 1, 2);
    insert(&root, 3, 4);
    insert(&root, 5, 6);
    int sum = sum_range(&root, 1, 5);
    check_sums(root);
    printf("TestSumExactInterval_no3: %s\n", sum == 2+4 ? "Passed" : "Failed");
    free_treap(root);
}

void TestMultipleNodesSameX_no4() {
    TreapNode* root = NULL;
    insert(&root, 2, 1);
    insert(&root, 2, 2);
    insert(&root, 2, 3);
    int sum = sum_range(&root, 2, 3);
    check_sums(root);
    printf("TestMultipleNodesSameX_no4: %s\n", sum == 6 ? "Passed" : "Failed");
    free_treap(root);
}

void TestNonOverlappingInterval_no5() {
    TreapNode* root = NULL;
    insert(&root, 1, 10);
    insert(&root, 2, 20);
    int sum = sum_range(&root, 3, 5);
    check_sums(root);
    printf("TestNonOverlappingInterval_no5: %s\n", sum == 0 ? "Passed" : "Failed");
    free_treap(root);
}

void TestPartialOverlap_no6() {
    TreapNode* root = NULL;
    insert(&root, 0, 5);
    insert(&root, 4, 10);
    insert(&root, 6, 15);
    int sum = sum_range(&root, 3, 5);
    check_sums(root);
    printf("TestPartialOverlap_no6: %s\n", sum == 10 ? "Passed" : "Failed");
    free_treap(root);
}

void TestUpdateSumAfterInsert_no7() {
    TreapNode* root = NULL;
    insert(&root, 5, 3);
    insert(&root, 5, 2);
    check_sums(root);
    int sum = sum_range(&root, 5, 6);
    printf("TestUpdateSumAfterInsert_no7: %s\n", sum == 5 ? "Passed" : "Failed");
    free_treap(root);
}

void TestSumWholeTree_no8() {
    TreapNode* root = NULL;
    insert(&root, 10, 100);
    insert(&root, 20, 200);
    insert(&root, 30, 300);
    int sum = sum_range(&root, 10, 31);
    check_sums(root);
    printf("TestSumWholeTree_no8: %s\n", sum == 600 ? "Passed" : "Failed");
    free_treap(root);
}

void TestEmptyInterval_no9() {
    TreapNode* root = NULL;
    insert(&root, 5, 10);
    int sum = sum_range(&root, 5, 5);
    check_sums(root);
    printf("TestEmptyInterval_no9: %s\n", sum == 0 ? "Passed" : "Failed");
    free_treap(root);
}

void TestHigherPriorityNodes_no10() {
    TreapNode* root = NULL;
    insert(&root, 3, 5);
    insert(&root, 1, 10);
    insert(&root, 2, 15);
    int sum = sum_range(&root, 1, 3);
    check_sums(root);
    printf("TestHigherPriorityNodes_no10: %s\n", sum == 10+15 ? "Passed" : "Failed");
    free_treap(root);
}

int main() {
    TestInsertAndSum_no1();
    TestSumEmptyTree_no2();
    TestSumExactInterval_no3();
    TestMultipleNodesSameX_no4();
    TestNonOverlappingInterval_no5();
    TestPartialOverlap_no6();
    TestUpdateSumAfterInsert_no7();
    TestSumWholeTree_no8();
    TestEmptyInterval_no9();
    TestHigherPriorityNodes_no10();
    return 0;
}