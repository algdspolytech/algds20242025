#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int);
void split(Node*, int, Node**, Node**);
Node* insert(Node*, Node*);
Node* merge(Node*, Node*);
Node* delete(Node*, int);
Node* search(Node*, int);
void inOrder(Node*);
int height(Node*);
int countNodes(Node*);
int generateRandomKey();
