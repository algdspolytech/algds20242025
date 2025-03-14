#ifndef TREAP_H
#define TREAP_H

#include <stdbool.h>
#include <limits.h>

typedef struct Node {
    int key;
    int priority;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int key);
Node* search(Node* root, int key);
Node* insert(Node* root, int key);
Node* deleteNode(Node* root, int key);
bool isBST(Node* root);
bool isHeap(Node* root);
bool isTreap(Node* root);

#endif // TREAP_H
