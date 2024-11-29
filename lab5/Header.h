#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// ��������� ���� ��������� ������
typedef struct Node {
    int value;          // �������� � ����
    int minLeafHeight;  // ����������� ������ ����� � ����������
    struct Node* left;  // ��������� �� ����� ����������
    struct Node* right; // ��������� �� ������ ����������
} Node;

// ������� ��� �������� ������ ����
Node* createNode(int value);

// ������� ��� ���������� ����������� ������ ����� � ����������
int minLeafHeight(Node* root);

// ������� ��� ���������� ����������� ������ ������� � �����������
void updateMinLeafHeights(Node* root);

// ������� ��� ������ ������ � ����
void printTreeToFile(Node* root, int space, FILE* file);

