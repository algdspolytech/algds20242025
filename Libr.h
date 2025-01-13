#pragma once


// ���������� ��������� ����
typedef struct Node {
    char* data;              // ��������� �� ASCIIZ ������
    struct Node* next;       // ��������� �� ��������� ����
} Node;

Node* createNode(const char* data);
void append(Node** head, const char* data);
void split(Node* source, Node** fir, Node** sec);
Node* merge(Node* a, Node* b);
void mergeSort(Node** headRef);
void printList(Node* node);
void append_forward(Node** head, const char* data);