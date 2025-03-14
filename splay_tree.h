#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;


Node* splay(Node* root, int data);
Node* insert(Node* root, int data);
Node* deleteNode(Node* root, int data);
bool search(Node* root, int data);


Node* createNode(int data);
void inorder(Node* root);

#endif // SPLAY_TREE_H