#pragma once
#ifndef XOR_LIST_H
#define XOR_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// ��������� ���� XOR-�������� ������
typedef struct Node {
    char* data;           // ASCIIZ ������
    struct Node* np;      // XOR ���������: prev ^ next
} Node;

// ������� XOR ���� ����������
Node* XOR(Node* a, Node* b);

// �������� ������� � ����� ������
void add(Node** head, char* str);

// ����� ������� �� �����
Node* find(Node* head, char* key);

// ������� ������� �� �����
void deleteByKey(Node** head, char* key);

// ������� ������� �� ������
void deleteByAddress(Node** head, Node* node);

// �������� � ����� ���� ���������
void printList(Node* head);

// ������������ ������ ����� ������
void freeList(Node* head);

#endif // XOR_LIST_H