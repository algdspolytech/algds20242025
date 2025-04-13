#ifndef CODE_H
#define CODE_H

#include <stdio.h>

// ��������� ���� ������
typedef struct Node {
    int value;            // �������� ����
    struct Node* left;    // ��������� �� ����� ���������
    struct Node* right;   // ��������� �� ������ ���������
} Node;

// ������� ��� ������ � �������
Node* create(int value);
void free(Node* node);
Node* read(FILE* file);
void Tree1(FILE* out, const Node* tree);
void Tree2(FILE* out, const Node* tree);

#endif // CODE_H