#include "tree.h"
#include <assert.h>

void TestInsert_EmptyTree_ReturnValidNode_no1() {
    Node* root = insert(NULL, 10);
    assert(root != NULL && root->value == 10);
    freeTree(root);
}

void TestInsert_MultipleNodes_CorrectStructure_no2() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    assert(root->left && root->left->value == 5);
    assert(root->right && root->right->value == 15);
    freeTree(root);
}

void TestGetHeight_SingleNode_ReturnsOne_no3() {
    Node* root = createNode(10);
    assert(getHeight(root) == 1);
    freeTree(root);
}

void TestGetHeight_MultipleNodes_CorrectHeight_no4() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 2);
    assert(getHeight(root) == 3);
    freeTree(root);
}

void TestUpdateBalances_BalancedTree_ZeroBalance_no5() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    updateBalances(root);
    assert(root->balance == 0);
    freeTree(root);
}

void TestUpdateBalances_UnbalancedTree_CorrectBalance_no6() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 2);
    updateBalances(root);
    assert(root->balance == 2);
    freeTree(root);
}

void TestCreateNode_ValidValue_CorrectNode_no7() {
    Node* node = createNode(42);
    assert(node != NULL && node->value == 42);
    free(node);
}

void TestFreeTree_EmptyTree_NoCrash_no8() {
    freeTree(NULL);
}

void TestFreeTree_NonEmptyTree_NoLeak_no9() {
    Node* root = insert(NULL, 10);
    root = insert(root, 5);
    freeTree(root);
}

void TestInsert_DuplicateValues_CorrectStructure_no10() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 10);
    assert(root->left == NULL && root->right == NULL);
    freeTree(root);
}

int main() {
    TestInsert_EmptyTree_ReturnValidNode_no1();
    TestInsert_MultipleNodes_CorrectStructure_no2();
    TestGetHeight_SingleNode_ReturnsOne_no3();
    TestGetHeight_MultipleNodes_CorrectHeight_no4();
    TestUpdateBalances_BalancedTree_ZeroBalance_no5();
    TestUpdateBalances_UnbalancedTree_CorrectBalance_no6();
    TestCreateNode_ValidValue_CorrectNode_no7();
    TestFreeTree_EmptyTree_NoCrash_no8();
    TestFreeTree_NonEmptyTree_NoLeak_no9();
    TestInsert_DuplicateValues_CorrectStructure_no10();
    printf("All tests passed!\n");
    return 0;
}
