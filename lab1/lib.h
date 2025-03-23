#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree {
    Node *root;
    Node *TNULL;
} RBTree;


RBTree* createRBTree();
Node* createNode(int data);
void leftRotate(RBTree *tree, Node *x);
void rightRotate(RBTree *tree, Node *y);
void insert(RBTree *tree, int data);
void insertFix(RBTree *tree, Node *k);
Node* search(RBTree *tree, int data);
void deleteNode(RBTree *tree, int data);
void deleteFix(RBTree *tree, Node *x);
void inorderHelper(Node *node);
void inorder(RBTree *tree);

#endif