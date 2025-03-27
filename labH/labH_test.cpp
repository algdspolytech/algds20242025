#include <cstdio>
#include <cstdlib>
#include <locale.h>
#include "labH.h"

void TestGetHeight_NullNode_no1() {
    int h = getHeight(nullptr);
    int correct;
    if (h == 0) {
        correct = 1;
    }
    else {
        correct = 0;
    }
    printf("TestGetHeight_NullNode_no1 = %i\n", correct);
}

void TestGetHeight_SingleNode_no2() {
    ListNode* node = newNode(5);
    int h = getHeight(node);
    int correct;
    if (h == 1) {
        correct = 1;
    }
    else {
        correct = 0;
    }
    printf("TestGetHeight_SingleNode_no2 = %i\n", correct);
    freeTree(node);
}

void TestGetSize_NullNode_no3() {
    int s = getSize(nullptr);
    int correct;
    if (s == 0) {
        correct = 1;
    }
    else {
        correct = 0;
    }
    printf("TestGetSize_NullNode_no3 = %i\n", correct);
}

void TestGetSize_SingleNode_no4() {
    ListNode* node = newNode(10);
    int s = getSize(node);
    int correct;
    if (s == 1) {
        correct = 1;
    }
    else {
        correct = 0;
    }
    printf("TestGetSize_SingleNode_no4 = %i\n", correct);
    freeTree(node);
}

void TestInsertAt_EmptyTree_no5() {
    ListNode* tree = nullptr;
    tree = insertAtPosition(tree, 10, 0);
    int correct;
    if ((tree != nullptr) && (tree->value == 10)) {
        correct = 1;
    }
    else {
        correct = 0;
    }
    printf("TestInsertAt_EmptyTree_no5 = %i\n", correct);
    freeTree(tree);
}

void TestInsertAt_MultipleNodes_no6() {
    ListNode* tree = nullptr;
    tree = insertAtPosition(tree, 10, 0);
    tree = insertAtPosition(tree, 20, 1);
    tree = insertAtPosition(tree, 30, 2);
    tree = insertAtPosition(tree, 15, 1);

    int expected[4] = { 10, 15, 20, 30 };
    int result[4] = { 0, 0, 0, 0 };
    int index = 0;

    ListNode* stack[100];
    int stackIndex = 0;
    ListNode* current = tree;
    while (stackIndex > 0 || current != nullptr) {
        while (current != nullptr) {
            stack[stackIndex++] = current;
            current = current->left;
        }
        current = stack[--stackIndex];
        result[index++] = current->value;
        current = current->right;
    }

    int correct = 1;
    if (index != 4) {
        correct = 0;
    }
    else {
        for (int i = 0; i < 4; i++) {
            if (result[i] != expected[i]) {
                correct = 0;
                break;
            }
        }
    }
    printf("TestInsertAt_MultipleNodes_no6 = %i\n", correct);
    freeTree(tree);
}

void TestRemoveByValue_NodeNotExist_no7() {
    ListNode* tree = nullptr;
    tree = insertAtPosition(tree, 10, 0);
    tree = insertAtPosition(tree, 20, 1);
    tree = insertAtPosition(tree, 30, 2);
    ListNode* newTree = removeByValue(tree, 40);

    int expected[3] = { 10, 20, 30 };
    int result[3] = { 0, 0, 0 };
    int index = 0;

    ListNode* stack[100];
    int stackIndex = 0;
    ListNode* current = newTree;
    while (stackIndex > 0 || current != nullptr) {
        while (current != nullptr) {
            stack[stackIndex++] = current;
            current = current->left;
        }
        current = stack[--stackIndex];
        result[index++] = current->value;
        current = current->right;
    }

    int correct = 1;
    if (index != 3) {
        correct = 0;
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (result[i] != expected[i]) {
                correct = 0;
                break;
            }
        }
    }
    printf("TestRemoveByValue_NodeNotExist_no7 = %i\n", correct);
    freeTree(newTree);
}

void TestRemoveByValue_DeleteLeaf_no8() {
    ListNode* tree = nullptr;
    tree = insertAtPosition(tree, 10, 0);
    tree = insertAtPosition(tree, 20, 1);
    tree = insertAtPosition(tree, 30, 2);
    tree = removeByValue(tree, 30);

    int expected[2] = { 10, 20 };
    int result[2] = { 0, 0 };
    int index = 0;

    ListNode* stack[100];
    int stackIndex = 0;
    ListNode* current = tree;
    while (stackIndex > 0 || current != nullptr) {
        while (current != nullptr) {
            stack[stackIndex++] = current;
            current = current->left;
        }
        current = stack[--stackIndex];
        result[index++] = current->value;
        current = current->right;
    }

    int correct = 1;
    if (index != 2) {
        correct = 0;
    }
    else {
        for (int i = 0; i < 2; i++) {
            if (result[i] != expected[i]) {
                correct = 0;
                break;
            }
        }
    }
    printf("TestRemoveByValue_DeleteLeaf_no8 = %i\n", correct);
    freeTree(tree);
}

void TestGetNodeByIndex_ValidIndex_no9() {
    ListNode* tree = nullptr;
    tree = insertAtPosition(tree, 10, 0);
    tree = insertAtPosition(tree, 20, 1);
    tree = insertAtPosition(tree, 30, 2);
    ListNode* node = getNodeByIndex(tree, 1);

    int correct;
    if ((node != nullptr) && (node->value == 20)) {
        correct = 1;
    }
    else {
        correct = 0;
    }
    printf("TestGetNodeByIndex_ValidIndex_no9 = %i\n", correct);
    freeTree(tree);
}

void TestMergeTrees_TwoTrees_no10() {
    ListNode* tree1 = nullptr;
    tree1 = insertAtPosition(tree1, 10, 0);
    tree1 = insertAtPosition(tree1, 20, 1);
    ListNode* tree2 = nullptr;
    tree2 = insertAtPosition(tree2, 30, 0);
    tree2 = insertAtPosition(tree2, 40, 1);
    ListNode* merged = mergeTrees(tree1, tree2);

    int expected[4] = { 10, 20, 30, 40 };
    int result[4] = { 0, 0, 0, 0 };
    int index = 0;

    ListNode* stack[100];
    int stackIndex = 0;
    ListNode* current = merged;
    while (stackIndex > 0 || current != nullptr) {
        while (current != nullptr) {
            stack[stackIndex++] = current;
            current = current->left;
        }
        current = stack[--stackIndex];
        result[index++] = current->value;
        current = current->right;
    }

    int correct = 1;
    if (index != 4) {
        correct = 0;
    }
    else {
        for (int i = 0; i < 4; i++) {
            if (result[i] != expected[i]) {
                correct = 0;
                break;
            }
        }
    }
    printf("TestMergeTrees_TwoTrees_no10 = %i\n", correct);
    freeTree(merged);
}

void TestRebalance_RotationCase_no11() {
    ListNode* tree = nullptr;
    tree = insertAtPosition(tree, 1, 0);
    tree = insertAtPosition(tree, 2, 1);
    tree = insertAtPosition(tree, 3, 2);

    int correct = 1;
    if (tree == nullptr) {
        correct = 0;
    }
    else {
        if (tree->value == 1) {
            correct = 0;
        }
    }
    printf("TestRebalance_RotationCase_no11 = %i\n", correct);
    freeTree(tree);
}

void TestFindMinNode_no12() {
    ListNode* root = newNode(20);
    root->left = newNode(10);
    root->right = newNode(30);

    ListNode* minNode = findMinNode(root);
    int correct;
    if ((minNode != nullptr) && (minNode->value == 10)) {
        correct = 1;
    }
    else {
        correct = 0;
    }
    printf("TestFindMinNode_no12 = %i\n", correct);
    freeTree(root);
}

void TestRemoveByValue_DeleteNodeWithTwoChildren_no13() {
    ListNode* tree = nullptr;
    tree = insertAtPosition(tree, 20, 0);
    tree = insertAtPosition(tree, 10, 0);
    tree = insertAtPosition(tree, 30, 2);
    tree = insertAtPosition(tree, 25, 2);
    tree = insertAtPosition(tree, 35, 4);

    tree = removeByValue(tree, 20);

    int expected[4] = { 10, 25, 30, 35 };
    int result[4] = { 0, 0, 0, 0 };
    int index = 0;

    ListNode* stack[100];
    int stackIndex = 0;
    ListNode* current = tree;
    while (stackIndex > 0 || current != nullptr) {
        while (current != nullptr) {
            stack[stackIndex++] = current;
            current = current->left;
        }
        current = stack[--stackIndex];
        result[index++] = current->value;
        current = current->right;
    }
    int correct = 1;
    if (index != 4) {
        correct = 0;
    }
    else {
        for (int i = 0; i < 4; i++) {
            if (result[i] != expected[i]) {
                correct = 0;
                break;
            }
        }
    }
    printf("TestRemoveByValue_DeleteNodeWithTwoChildren_no13 = %i\n", correct);
    freeTree(tree);
}

void runAllTests() {
    TestGetHeight_NullNode_no1();
    TestGetHeight_SingleNode_no2();
    TestGetSize_NullNode_no3();
    TestGetSize_SingleNode_no4();
    TestInsertAt_EmptyTree_no5();
    TestInsertAt_MultipleNodes_no6();
    TestRemoveByValue_NodeNotExist_no7();
    TestRemoveByValue_DeleteLeaf_no8();
    TestGetNodeByIndex_ValidIndex_no9();
    TestMergeTrees_TwoTrees_no10();
    TestRebalance_RotationCase_no11();
    TestFindMinNode_no12();
    TestRemoveByValue_DeleteNodeWithTwoChildren_no13();
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    runAllTests();
    return 0;
}
