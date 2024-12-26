#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <assert.h>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define _CRTDBG_MAP_ALLOC

typedef struct Node {
    char* word;            // ����� � ����
    struct Node* left;    // ����� �������� ����
    struct Node* right;   // ������ �������� ����
    int subtree_width;    // ������ ���������
} Node;

// ������� ��� �������� ������ ����
Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->word = strdup(word); // �������� �����
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->subtree_width = 0;   // �������������� ������ ���������
    return newNode;
}

// ������� ��� ���������� ������ �����������
int calculateSubtreeWidth(Node* node) {
    if (node == NULL) {
        return 0;
    }

    int leftWidth = calculateSubtreeWidth(node->left);
    int rightWidth = calculateSubtreeWidth(node->right);

    // ������ ��������� = ����� ����� + ������ ������ ��������� + ������ ������� ���������
    node->subtree_width = strlen(node->word) + leftWidth + rightWidth;

    return node->subtree_width; // ���������� ������ �������� ���������
}

// ������� ��� ������ ������ � ������� �����������
void printTree(Node* node) {
    if (node == NULL) {
        return;
    }

    printTree(node->left);

    printf("�����: %s, ������ ���������: %d\n", node->word, node->subtree_width);

    printTree(node->right);
}

// ������� ��� ������������ ������
void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }

    freeTree(node->left);
    freeTree(node->right);
    free(node->word);
    free(node);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // ������ �������� ��������� ������
    Node* root = createNode("hello");
    root->left = createNode("world");
    root->right = createNode("!");
    root->left->left = createNode("good");
    root->left->right = createNode("morning");

    // ��������� ������ �����������
    calculateSubtreeWidth(root);

    // �������� ������ � ������� �����������
    printTree(root);

    // ����������� ������
    freeTree(root);

    return 0;
}

//�����
void Test_EmptyTree_no1() {
    Node* root = NULL;
    printf("���� 1: ������ ������\n");
    calculateSubtreeWidth(root);
    printTree(root);
}

void Test_SingleNode_no2() {
    Node* root = createNode("A");
    printf("���� 2: ���� �����\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_TwoNodes_no3() {
    Node* root = createNode("A");
    root->left = createNode("B");
    printf("���� 3: ��� ����, ���� �����\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_TwoNodes_Right_no4() {
    Node* root = createNode("A");
    root->right = createNode("C");
    printf("���� 4: ��� ����, ���� ������\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_ThreeNodes_Left_no5() {
    Node* root = createNode("A");
    root->left = createNode("B");
    root->left->left = createNode("D");
    printf("���� 5: ��� ����, ��� �����\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_ThreeNodes_Right_no6() {
    Node* root = createNode("A");
    root->right = createNode("C");
    root->right->right = createNode("E");
    printf("���� 6: ��� ����, ��� ������\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_BalancedTree_no7() {
    Node* root = createNode("A");
    root->left = createNode("B");
    root->right = createNode("C");
    printf("���� 7: ���������������� ������\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_ComplexTree_no8() {
    Node* root = createNode("A");
    root->left = createNode("B");
    root->right = createNode("C");
    root->left->left = createNode("D");
    root->left->right = createNode("E");

    printf("���� 8: ������� ������\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_LongWords_no9() {
    Node* root = createNode("HelloWorld!");
    root->left = createNode("Goodbye!");

    printf("���� 9: ������� �����\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Test_EmptyLeftSubtree_no10() {
    Node* root = createNode("A");
    root->right = createNode("B");

    printf("���� 10: ������ ����� ���������\n");
    calculateSubtreeWidth(root);
    printTree(root);
    freeTree(root);
}

void Run_tests() {
    Test_EmptyTree_no1();
    Test_SingleNode_no2();
    Test_TwoNodes_no3();
    Test_TwoNodes_Right_no4();
    Test_ThreeNodes_Left_no5();
    Test_ThreeNodes_Right_no6();
    Test_BalancedTree_no7();
    Test_ComplexTree_no8();
    Test_LongWords_no9();
    Test_EmptyLeftSubtree_no10();
    printf("Success!");
}