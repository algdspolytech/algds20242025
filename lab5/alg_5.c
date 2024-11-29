#include "Header.h"

// ������� ��� �������� ������ ����
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->minLeafHeight = 1;  // �������� �� ���������
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ������� ��� ���������� ����������� ������ ����� � ����������
int minLeafHeight(Node* root) {
    if (root == NULL)
        return -1;  // ������ ������ �� ����� ������

    // ���� ���� � ��� ����, ��� ������ ����� 0
    if (root->left == NULL && root->right == NULL)
        return 0;

    int leftHeight = minLeafHeight(root->left);
    int rightHeight = minLeafHeight(root->right);

    if (root->left == NULL) return rightHeight + 1;
    if (root->right == NULL) return leftHeight + 1;

    return (leftHeight < rightHeight ? leftHeight : rightHeight) + 1;
}

// ������� ��� ���������� ����������� ������ ������� � �����������
void updateMinLeafHeights(Node* root) {
    if (root == NULL)
        return;

    root->minLeafHeight = minLeafHeight(root);
    updateMinLeafHeights(root->left);
    updateMinLeafHeights(root->right);
}

// ������� ��� ������ ������ � ����
void printTreeToFile(Node* root, int space, FILE* file) {
    if (root == NULL)
        return;

    space += 5;
    printTreeToFile(root->right, space, file);

    fprintf(file, "\n");
    for (int i = 5; i < space; i++) {
        fprintf(file, " ");
    }
    fprintf(file, "%d\n", root->minLeafHeight);

    printTreeToFile(root->left, space, file);
}
