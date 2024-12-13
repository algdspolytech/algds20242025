#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include "funcs.h"


// �������� ������ ����
TreeNode* createNode(const char* word) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->word = strdup(word); // �������� �����
    node->width = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ���������� ������ ��������� ������� ����
int computeWidth(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }

    // ���������� ��������� ������ ������ � ������� �����������
    int leftWidth = computeWidth(node->left);
    int rightWidth = computeWidth(node->right);

    // ������ �������� ���� = ����� ��� ����� + ������ �����������
    node->width = strlen(node->word) + leftWidth + rightWidth;
    return node->width;
}

// ������ ������ � �������� ��� �������
void printTree(TreeNode* node, int depth) {
    if (node == NULL) {
        return;
    }

    // �������� ������ ���������
    printTree(node->right, depth + 1);

    // �������� ����� � ������
    for (int i = 0; i < depth; i++) {
        printf("   "); // ������ ��� ������ �������
    }
    printf("%s\n", node->word);
    for (int i = 0; i < depth; i++) {
        printf("   "); // ������ ��� ������ �������
    }
    printf("%*d\n", (int)(strlen(node->word) / 2 + 1), node->width);

    // �������� ����� ���������
    printTree(node->left, depth + 1);
}

// ������������ ������, ������� �������
void freeTree(TreeNode* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node->word);
    free(node);
}