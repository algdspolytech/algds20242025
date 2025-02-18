#pragma once 

#include <stdbool.h>

typedef struct Node {
    int data;
    int count;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node* createNode(int data);
int getCount(Node* node);
void updateCount(Node* node);
Node* insertNode(Node* root, int data);
Node* findMin(Node* node);
Node* deleteNode(Node* root, int data);
void inorderTraversal(Node* root);
void freeTree(Node* root);