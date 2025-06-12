#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct Node {
    int data;
    int min_leaf_height;
    struct Node* left;
    struct Node* right;
} Node;
Node* createNode(int data);

int calculateAndSetMinLeafHeight(Node* node);
void printTreePreOrder(Node* node);
void freeTree(Node* node);
int min_t(int a, int b);

#endif