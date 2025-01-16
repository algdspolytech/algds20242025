#pragma once
#ifndef TREE_H
#define TREE_H

typedef struct Node {
    int value;
    int width;  // ������ ���������
    struct Node* left;
    struct Node* right;
} Node;

// ������� ��� ������ � �������
Node* createNode(int value);
void insertNode(Node** root, int value);
int calculateWidth(Node* root);
void printTree(Node* root, int level);
void freeTree(Node* root);

#endif // TREE_H