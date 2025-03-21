#define _CRT_SECURE_NO_WARNINGS
#ifndef code_h
#define code_h
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node* left, * right, * parent;
} Node;

Node* createNode(int key, Color color, Node* nil);

typedef struct RBTree {
    Node* root;
    Node* nil;
} RBTree;

RBTree* createRBTree();

void leftRotate(RBTree* tree, Node* x);

void rightRotate(RBTree* tree, Node* y);

void insert(RBTree* tree, int key);

void mergeTrees(RBTree* t1, RBTree* t2, int x);


#endif