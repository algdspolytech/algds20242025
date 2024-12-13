#pragma once
#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������� ���� ��������� ������
typedef struct TreeNode {
    char* word;                // ����� � ����
    int width;                 // ������ ���������
    struct TreeNode* left;     // ����� �������
    struct TreeNode* right;    // ������ �������
} TreeNode;

TreeNode* createNode(const char* word);
int computeWidth(TreeNode* node);
void printTree(TreeNode* node, int depth);
void freeTree(TreeNode* node);


#endif
