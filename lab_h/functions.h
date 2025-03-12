#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

Node* insertAVL(Node* node, int key);
Node* deleteAVL(Node* root, int key);
Node* search(Node* root, int key);
int getBalance(Node* node);
int height(Node* node);
Node* minValueNode(Node* node);

#endif
