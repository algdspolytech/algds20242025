#ifndef TREE_H
#define TREE_H

// ����������� ��������� ���� ��������� ������
struct Node {
    int data;          // ������ ����
    struct Node* left; // ����� �������
    struct Node* right; // ������ �������
};

// ������� ��� �������� ������ ����
struct Node* createNode(int data);

// ������� ��� ���������� ������ ���������
int height(struct Node* node);

// ������� ��� ������ ��������� ����� � ������ ����
void updateHeightDifference(struct Node* node);

// ������� ��� ������������� ������ ������ � ������ �������� � ������
void printTreeInOrder(struct Node* node);

#endif // TREE_H
