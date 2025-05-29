#pragma once
typedef struct Node {
    long long x;
    long long c;
    int priority;
    long long sum;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(long long x, long long c);
void updateSum(Node* node);
Node* merge(Node* left, Node* right);
void split(Node* root, long long key, Node** left, Node** right);
long long rangeSum(Node* root, long long x, long long y);
void insert(Node** root, long long x, long long c);
void freeTree(Node* root);