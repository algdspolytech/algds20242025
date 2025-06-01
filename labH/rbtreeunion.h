#pragma once

#include <stdio.h>
#include <stdlib.h>


typedef enum { BLACK, RED } Color;

typedef struct Node {
    int key;
    struct Node *left, *right, *parent;
    Color color;
} Node;

Node* createNode(int key, Color color);

int blackHeight(Node* node);
Node* findBlHeightRight(Node* root, int bh);


Node* findBlHeightLeft(Node* root, int bh);

void leftRotate(Node** root, Node* x);

void rightRotate(Node** root, Node* y);

void insertFixup(Node** root, Node* z);

Node* checkMatchRight(Node* T1, int x);

Node* checkMatchLeft(Node* T1, int x);

Node* rbUnion(Node** root, Node* T1, Node* T2, int x);

void inorderTraversal(Node* root);

void printTree(Node* root, int level);

void insert(Node** root, int key);