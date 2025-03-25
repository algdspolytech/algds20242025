#ifndef TREAP_H
#define TREAP_H

#include <stdbool.h>

typedef struct Node {
    int key;
    int priority;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int key);
Node* insert(Node* root, int key);
Node* deleteNode(Node* root, int key);
bool search(Node* root, int key);
void inorderTraversal(Node* root);
void freeTree(Node* root);

#endif // TREAP_H