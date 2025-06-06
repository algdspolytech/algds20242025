#pragma once


typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct {
    Node* root; // ������ ������
    Node* nil;  // ������ �������
} RBTree;

// ������������� ������
void init_rbtree(RBTree* tree);

// ����� ��������
Node* search(const RBTree* tree, int data);

// ������� ��������
void insert(RBTree* tree, int data);

// �������� ��������
void delete(RBTree* tree, int data);

// ������������ ������
void free_tree(RBTree* tree);

void print_tree(const RBTree* tree);

