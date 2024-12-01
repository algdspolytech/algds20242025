#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab_E.h"

void TestCreateNode_CreateValidNode_no1() {
    Node* node = createNode(10);

    printf("TestCreateNode_CreateValidNode_no1 = %d\n",
        node != NULL && node->value == 10 && node->left == NULL && node->right == NULL);

    free(node);
}

void TestCalculateMinLeafHeight_EmptyTree_no2() {
    int height = calculateMinLeafHeight(NULL);

    printf("TestCalculateMinLeafHeight_EmptyTree_no2 = %d\n", height == INT_MAX);
}

void TestCalculateMinLeafHeight_SingleNodeTree_no3() {
    Node* root = createNode(10);
    int height = calculateMinLeafHeight(root);

    printf("TestCalculateMinLeafHeight_SingleNodeTree_no3 = %d\n", height == 0);

    free(root);
}

void TestCalculateMinLeafHeight_BalancedTree_no4() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);

    int height = calculateMinLeafHeight(root);

    printf("TestCalculateMinLeafHeight_BalancedTree_no4 = %d\n", height == 1);

    free(root->left);
    free(root->right);
    free(root);
}

void TestTreeHeight_BalancedTree_no5() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->right->right = createNode(5);

    int height = treeHeight(root);

    printf("TestTreeHeight_BalancedTree_no5 = %d\n", height == 3);

    free(root->left->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);
}

void TestTreeHeight_SingleNodeTree_no6() {
    Node* root = createNode(1);

    int height = treeHeight(root);

    printf("TestTreeHeight_SingleNodeTree_no6 = %d\n", height == 1);

    free(root);
}

void TestPrintTreeToFilePyramid_EmptyTree_no7() {
    FILE* file = fopen("test_output.txt", "w");
    printTreeToFilePyramid(NULL, file);
    fclose(file);

    printf("TestPrintTreeToFilePyramid_EmptyTree_no7 = %d\n", 1);
}

void TestPrintTreeToFilePyramid_SingleNodeTree_no8() {
    Node* root = createNode(1);
    calculateMinLeafHeight(root);

    FILE* file = fopen("test_output.txt", "w");
    printTreeToFilePyramid(root, file);
    fclose(file);

    printf("TestPrintTreeToFilePyramid_SingleNodeTree_no8 = %d\n", 1);

    free(root);
}

void TestCalculateMinLeafHeight_LeftSkewedTree_no9() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->left->left = createNode(3);

    int height = calculateMinLeafHeight(root);

    printf("TestCalculateMinLeafHeight_LeftSkewedTree_no9 = %d\n", height == 2);

    free(root->left->left);
    free(root->left);
    free(root);
}

void TestTreeHeight_RightSkewedTree_no10() {
    Node* root = createNode(1);
    root->right = createNode(2);
    root->right->right = createNode(3);

    int height = treeHeight(root);

    printf("TestTreeHeight_RightSkewedTree_no10 = %d\n", height == 3);

    free(root->right->right);
    free(root->right);
    free(root);
}

void TestPrintTreeToFilePyramid_BalancedTree_no11() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    calculateMinLeafHeight(root);

    FILE* file = fopen("test_output_balanced.txt", "w");
    printTreeToFilePyramid(root, file);
    fclose(file);

    printf("TestPrintTreeToFilePyramid_BalancedTree_no11 = %d\n", 1);

    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);
}

void TestTreeHeight_FullTree_no12() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int height = treeHeight(root);

    printf("TestTreeHeight_FullTree_no12 = %d\n", height == 3);

    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);
}

int TestMainFunctionality_no13() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);

    calculateMinLeafHeight(root);

    FILE* file;
    errno_t err = fopen_s(&file, "tree_output.txt", "w");
    if (err != 0) {
        perror("Error opening file");
        return 1;
    }

    printTreeToFilePyramid(root, file);

    fclose(file);

    free(root->left->left);
    free(root->left->right);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

void runAllTests() {
    TestCreateNode_CreateValidNode_no1();
    TestCalculateMinLeafHeight_EmptyTree_no2();
    TestCalculateMinLeafHeight_SingleNodeTree_no3();
    TestCalculateMinLeafHeight_BalancedTree_no4();
    TestTreeHeight_BalancedTree_no5();
    TestTreeHeight_SingleNodeTree_no6();
    TestPrintTreeToFilePyramid_EmptyTree_no7();
    TestPrintTreeToFilePyramid_SingleNodeTree_no8();
    TestCalculateMinLeafHeight_LeftSkewedTree_no9();
    TestTreeHeight_RightSkewedTree_no10();
    TestPrintTreeToFilePyramid_BalancedTree_no11();
    TestTreeHeight_FullTree_no12();
    TestMainFunctionality_no13();
}

int main() {
    runAllTests();
    return 0;
}
