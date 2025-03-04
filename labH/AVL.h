#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// ��������� ���� AVL-������, ��������������� �������� ������.
typedef struct Node {
    int key;         // �������� ��������.
    int height;      // ������ ���������.
    int size;        // ���������� ����� � ���������.
    struct Node* left, * right;
} Node;

// ������� �������� ������ ����.
Node* create_node(int key);

// ���������� ������ ���� (0, ���� ���� ����� NULL).
int getHeight(Node* node);

// ���������� ������ ��������� (0, ���� ���� ����� NULL).
int getSize(Node* node);

// ���������� ������ � ������� ���� �� ������ ��� ��������.
void update(Node* node);

// ������ ������� ������ ���� y.
Node* rightRotate(Node* y);

// ����� ������� ������ ���� x.
Node* leftRotate(Node* x);

// ��������� �������������� ������� ����.
int getBalance(Node* node);

// ������������ ���� AVL-������.
Node* balance(Node* node);

// ����� k-�� �������� � ������ (1-based ���������).
Node* find_kth(Node* root, int k);

// ����� �������� �� �������� key.
Node* search_by_key(Node* root, int key);

// ������� �������� �� ��������� key � ������� pos (0-based ������).
Node* insert_at(Node* root, int pos, int key);

// �������� ��������, ����������� ������� pos (0-based ������).
Node* delete_at(Node* root, int pos);

// ������� extract_max ��������� (�������) ������������ �������.
Node* extract_max(Node* root, Node** max_node);

// �������� ��������� ���� �������, �������������� AVL-���������.
Node* join_trees(Node* t1, Node* t2);

// ������� in-order ������ ��� ������ ��������� ������ � ���� ������.
void inorder_print(Node* root);

#endif // AVL_H