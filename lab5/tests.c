#define _CRT_SECURE_NO_WARNINGS
#include <locale.h> // ��� ��������� �������� �����
#include <assert.h>  // ��� ������������� assert
#include "tree.h"

// ���� 1: �������� ������� ������
void test_updateHeightDifference_empty() {
    struct Node* root = NULL;
    updateHeightDifference(root);  // ��� ������� ������ �� ������ ���� ���������
}

// ���� 2: �������� ������ � ����� �����
void test_updateHeightDifference_single_node() {
    struct Node* root = createNode(5);
    updateHeightDifference(root);
    assert(root->data == 0);  // ���� ��� ��������, ������� ����� = 0
}

// ���� 3: �������� ������ � ����� ����������
void test_updateHeightDifference_left_only() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    updateHeightDifference(root);
    assert(root->data == 1);  // ������� �����: 1 (������� ������ ������ ���������)
    assert(root->left->data == 0);  // ���� ��� ��������, ������� ����� = 0
}

// ���� 4: �������� ������ � ������ ����������
void test_updateHeightDifference_right_only() {
    struct Node* root = createNode(5);
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == -1);  // ������� �����: -1 (������� ������ ������� ���������)
    assert(root->right->data == 0);  // ���� ��� ��������, ������� ����� = 0
}

// ���� 5: �������� ������ � ����� ������ (����� � ������)
void test_updateHeightDifference_two_nodes() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == 0);  // ������� ����� ������ � ������� ��������� ����� 0
    assert(root->left->data == 0);  // ���� ��� ��������, ������� ����� = 0
    assert(root->right->data == 0);  // ���� ��� ��������, ������� ����� = 0
}

// ���� 6: �������� ������, ��� ���� ��������� ������
void test_updateHeightDifference_one_subtree_empty() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    updateHeightDifference(root);
    assert(root->data == 1);  // ������� ����� ����� ����� ���������� � ����������� �������
    assert(root->left->data == 0);  // ���� ��� ��������, ������� ����� = 0
}
// ���� 7: �������� ������, ��� ����� ��������� ������ �������
void test_updateHeightDifference_left_deeper() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->left->left = createNode(1);  // ����� ��������� ������
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == 1);  // ������� �����: ����� ��������� ������ �������
    assert(root->left->data == 1);  // ������� ����� � ����� ���������
    assert(root->right->data == 0);  // ������� ����� � ������� ���������
}


// ���� 8: �������� ������, ��� ������ ��������� ������ ������
void test_updateHeightDifference_right_deeper() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(8);
    root->right->right = createNode(9);  // ������ ��������� ������
    updateHeightDifference(root);
    assert(root->data== -1);  // ������� �����: ������ ��������� ������
    assert(root->left->data== 0);  // ������� ����� � ������ ���������
    assert(root->right->data == -1);  // ������� ����� � ������ ���������
}

// ���� 9: �������� ������������������� ������ � ����� ����������
void test_updateHeightDifference_unbalanced() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->left->left = createNode(1);
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == 1);  // ������� ����� ����� ����� (������) � ������ ����������
    assert(root->left->data == 1);  // ������� ����� � ����� ���������
    assert(root->right->data == 0);  // ������� ����� � ������� ���������
}



// ���� 10: �������� ������ � �������� ������ ����������
void test_updateHeightDifference_deep_right_subtree() {
    struct Node* root = createNode(10);
    root->right = createNode(20);
    root->right->right = createNode(30);
    root->right->right->right = createNode(40);  // �������� ������ ���������
    updateHeightDifference(root);
    assert(root->data == -3);  // ������� ����� ������� (������) ���������
    assert(root->right->data == -2);  // ������� ����� � ������ ���������
}

// ���� 11: �������� ����������������� ������
void test_updateHeightDifference_balanced() {
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(8);
    updateHeightDifference(root);
    assert(root->data == 0);  // ������� ����� ������ � ������� ��������� ����� 0
    assert(root->left->data == 0);  // ���� ��� ��������, ������� ����� = 0
    assert(root->right->data == 0);  // ���� ��� ��������, ������� ����� = 0
}

int main() {
    // ������������� ������ �� ������� ����
    setlocale(LC_ALL, "Russian");

    // ����� ���� ������
    test_updateHeightDifference_empty();
    test_updateHeightDifference_single_node();
    test_updateHeightDifference_left_only();
    test_updateHeightDifference_right_only();
    test_updateHeightDifference_two_nodes();
    test_updateHeightDifference_one_subtree_empty();
    test_updateHeightDifference_left_deeper();
    test_updateHeightDifference_right_deeper();
    test_updateHeightDifference_unbalanced();
    test_updateHeightDifference_deep_right_subtree();
    test_updateHeightDifference_balanced();
    return 0;
}
