#pragma once
#ifndef BST_H
#define BST_H

// ��������� ���� ������
typedef struct Node {
    int key;              // �������� �����
    int size;             // ������ ���������, ������� ���� ����
    struct Node* left;    // ����� �������
    struct Node* right;   // ������ �������
} Node;

// ��������� �������
Node* insert(Node* root, int key);
Node* find(Node* root, int key);
Node* find_kth_predecessor(Node* root, int key, int k);
void free_tree(Node* root);

#endif // BST_H