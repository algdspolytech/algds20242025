#ifndef funcs_h
#define funcs_h

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"


Node* newNode(int key);
Node* rightRotate(Node* x);
Node* leftRotate(Node* x);
Node* splay(Node* root, int key);
Node* search(Node* root, int key);
Node* insert(Node* root, int key);
Node* delete(Node* root, int key);
void inorder(Node* root);

#endif