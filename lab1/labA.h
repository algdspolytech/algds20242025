#ifndef LABA_H
#define LABA_H

#include <stdbool.h>

typedef struct Node {
    char* data;          // ASCII-Z ������
    struct Node* np;     // XOR ���������
} Node;

typedef struct XORList {
    Node* head;          // ������ �������
    Node* tail;          // ��������� �������
} XORList;

// ������������� 
void init_list(XORList* list);

// �������� �������
bool add_element(XORList* list, const char* data);

// ������� ������� �� �����
bool remove_by_key(XORList* list, const char* key);

// ������� ������� �� ������
bool remove_by_address(XORList* list, Node* address);

// ������ ������� �� �����
Node* find_by_key(const XORList* list, const char* key);

// ����������� (���������� ��������� ����)
Node* iterate_list(Node* prev, Node* current);

#endif