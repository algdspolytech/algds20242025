#include "tests.h"

// ���� 1: ������ ������
void testEmptyTree_No1() {
    assert(computeWidth(NULL) == 0);
    printf("Test 1 passed\n");
}

// ���� 2: ������ � ����� �����
void testSingleNode_No2() {
    TreeNode* node1 = createNode("test");
    assert(computeWidth(node1) == 4);
    freeTree(node1);
    printf("Test 2 passed\n");
}

// ���� 3: ������ � ����� ��������
void testTwoLevelTree_No3() {
    TreeNode* root = createNode("root");
    root->left = createNode("left");
    root->right = createNode("right");
    assert(computeWidth(root) == 13);
    freeTree(root);
    printf("Test 3 passed\n");
}

// ���� 4: ������ � �������������� ����������
void testAsymmetricTree_No4() {
    TreeNode* root = createNode("root");
    root->left = createNode("left");
    root->left->left = createNode("child1");
    assert(computeWidth(root) == 14);
    freeTree(root);
    printf("Test 4 passed\n");
}

// ���� 5: �������� ������ ��� �����
void testNodeWidths_No5() {
    TreeNode* root = createNode("root");
    root->left = createNode("left");
    root->right = createNode("right");
    computeWidth(root);
    assert(root->width == 13);
    assert(root->left->width == 4);
    assert(root->right->width == 5);
    freeTree(root);
    printf("Test 5 passed\n");
}

// ���� 6: ������ � �������� �������
void testLongWords_No6() {
    TreeNode* root = createNode("root");
    root->left = createNode("superlongword");
    root->right = createNode("tiny");
    assert(computeWidth(root) == 21);
    freeTree(root);
    printf("Test 6 passed\n");
}

// ���� 7: ������ �� ������ �������� �����
void testSingleLongWord_No7() {
    TreeNode* node1 = createNode("supercalifragilisticexpialidocious");
    assert(computeWidth(node1) == strlen("supercalifragilisticexpialidocious"));
    freeTree(node1);
    printf("Test 7 passed\n");
}

// ���� 8: ������ � ����� ����������
void testSingleSubtree_No8() {
    TreeNode* root = createNode("root");
    root->left = createNode("child1");
    assert(computeWidth(root) == 10);
    freeTree(root);
    printf("Test 8 passed\n");
}

// ���� 9: ������� ������
void testLargeTree_No9() {
    TreeNode* root = createNode("root");
    root->left = createNode("left");
    root->right = createNode("right");
    root->left->left = createNode("child1");
    root->left->right = createNode("child2");
    root->right->right = createNode("child3");
    assert(computeWidth(root) == 31);
    freeTree(root);
    printf("Test 9 passed\n");
}

// ���� 10: ������ �����
void testEmptyWord_No10() {
    TreeNode* node1 = createNode("");
    assert(computeWidth(node1) == 0);
    freeTree(node1);
    printf("Test 10 passed\n");
}