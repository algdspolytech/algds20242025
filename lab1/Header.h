#pragma once
#include <stdio.h>
#include<stdlib.h>

// ��������� ��� ���� ����������� ������
typedef struct Node {
    char* data;
    struct Node* next;
    struct Node* prev;
} Node;

// ������� ��� �������� ������ ����
Node* createNode(const char* data);

// ������� ��� ���������� ������ �� ��� ��������
void split(Node* head, Node** firstHalf, Node** secondHalf);

// ������� ��� ������� ���� ��������������� �������
Node* merge(Node* first, Node* second);

// �������� ������� ���������� �� �������
Node* mergeSort(Node* head);

// ������� ��� ������ ������
void printList(Node* node);

// ������������ ������
void freeList(Node* node);

