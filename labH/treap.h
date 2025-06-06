#include <stdlib.h>


#ifndef TREAP_H
#define TREAP_H

typedef struct Node {
    int key;
    int priority;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int key, int priority);
Node* right_rotate(Node* y);
Node* left_rotate(Node* x);
Node* insert(Node* root, int key, int priority);
Node* remove(Node* root, int key);
void split(Node* root, int key, Node** left, Node** right);
Node* merge(Node* left, Node* right);
void free_tree(Node* root);





#endif