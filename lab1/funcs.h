#pragma once
#ifndef FUNCS_H
#define FUNCS_H

#include "structs.h"

Node* createNode(int data, Color color, Node* parent);
void leftRotate(RBTree* tree, Node* x);
void rightRotate(RBTree* tree, Node* x);
void insertFixup(RBTree* tree, Node* z);
void insert(RBTree* tree, int data);
void inorder(Node* root);
void mergeTrees(RBTree* tree, Node* root);
RBTree* unionRBTree(RBTree* S1, int x, RBTree* S2);


#endif