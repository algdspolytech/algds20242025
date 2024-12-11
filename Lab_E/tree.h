#ifndef TREE_H
#define TREE_H

// ����������� ��������� ���� ������
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// ������� ��� �������� ������ ����
struct Node* createNode(int data);

// ������� ��� ������ ������ � ������� ����
void printTree(struct Node* root, int level);

// ������� ��� ������ ������ � �������: ���� (����� ���������) (������ ���������)
void printTreeFormatted(struct Node* root);

// ������� ��� ������������ ������, ������� �������
void freeTree(struct Node* root);

#endif // TREE_H



