#include "labH.h"
#include <assert.h>


void TestNewNode_Node_ReturnValidVal() {
    Node *root = NewNode(1, 10);
    assert(root != NULL);
    assert(root->x == 1);
    assert(root->c == 10);
}

void TestMerge_TwoNodes_ReturnValidVal() {
    Node *N1 = NewNode(1, 10);
    Node *N2 = NewNode(2, 20);
    Node *N3 = Merge(N1, N2);
    assert(N3 != NULL);
    assert(N3->left != NULL || N3->right != NULL);
}

void TestSplit_TwoNodes_ReturnValidVal() {
    Node *N1 = NewNode(1, 10);
    Node *N2 = NewNode(3, 30);
    Node *T = Merge(N1, N2);
    Node *N1_new = NULL;
    Node *N2_new = NULL;
    Split(T, 2, &N1_new, &N2_new);
    assert(N1_new->x == N1->x);
    assert(N2_new->x == N2->x);
}

void TestInsert_NULLroot_ReturnValidVal() {
    Node *root = NULL;
    root = Insert(root, 1, 10);
    assert(root != NULL);
    assert(root->c == 10);
    assert(root->x == 1);
}

void TestInsert_Root_ReturnValidVal() {
    Node *root = NULL;
    root = Insert(root, 1, 10);
    root = Insert(root, 2, 20);
    assert(root != NULL);
    assert(root->left != NULL || root->right != NULL);
}

void TestInsert_DuplicateKeys_ReturnValidVal() {
    Node *root = NULL;
    root = Insert(root, 1, 10);
    root = Insert(root, 1, 20);
    assert(root->x == 1);
}

void TestFindMax_OneNode_ReturnValidVal() {
    Node *root = NULL;
    root = Insert(root, 2, 10);
    int c_max = FindMax(root, 2, 3);
    assert(c_max == 10);
}

void TestFindMax_EmptyTreap_ReturnINTMIN() {
    Node *root = NULL;
    int c_max = FindMax(root, 2, 3);
    assert(c_max == INT_MIN);
}


void TestFindMax_ManyNods_ReturnValidVal() {
    Node *root = NULL;
    root = Insert(root, 5, 50);
    root = Insert(root, -10, 100);
    root = Insert(root, 15, 666);
    root = Insert(root, -5, 120);
    int c_max = FindMax(root, -10, 10);
    assert(c_max == 120);
}

void TestGetSize_Nodes_ReturnValidMax() {
    Node *root = NULL;
    root = Insert(root, 1, 5);
    root = Insert(root, 2, 15);
    root = Insert(root, 3, 10);
    int size = GetSize(root);
    assert(size == 3);
}

void TestFindMax_NoKeysInRange_ReturnINTMIN() {
    struct Node *root = NULL;
    root = Insert(root, 2, 10);
    root = Insert(root, 4, 20);
    int c_max = FindMax(root, 5, 6);
    assert(c_max == INT_MIN);
}


int test() {
    TestNewNode_Node_ReturnValidVal();
    TestMerge_TwoNodes_ReturnValidVal();
    TestSplit_TwoNodes_ReturnValidVal();
    TestInsert_NULLroot_ReturnValidVal();
    TestInsert_Root_ReturnValidVal();
    TestInsert_DuplicateKeys_ReturnValidVal();
    TestFindMax_OneNode_ReturnValidVal();
    TestFindMax_EmptyTreap_ReturnINTMIN();
    TestFindMax_ManyNods_ReturnValidVal();
    TestGetSize_Nodes_ReturnValidMax();
    TestFindMax_NoKeysInRange_ReturnINTMIN();

    printf("\nthe test was successful\n");
    return 0;
}