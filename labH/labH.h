#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct Node {
    int x, c, pr, size;  // x - ключ, c - значение, pr - приоритет, size - размер поддерева
    struct Node *left;
    struct Node *right;
} Node;

int GetSize(Node *node);

void UpdateSize(Node *node);

Node *NewNode(int x, int c);

Node *Merge(Node *left, Node *right);

void Split(Node* root, int x, Node** left, Node** right);

Node *Insert(Node *root, int x, int c);

int FindMax(Node *root, int x, int y);

