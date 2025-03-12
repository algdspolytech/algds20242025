#pragma once
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>

typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

int height(AVLNode* node);
int balanceFactor(AVLNode* node);
AVLNode* rotateRight(AVLNode* y);
AVLNode* rotateLeft(AVLNode* x);
AVLNode* insert(AVLNode* node, int key);
AVLNode* insert(AVLNode* node, int key);
AVLNode* search(AVLNode* root, int key);
AVLNode* minValueNode(AVLNode* node);
AVLNode* deleteNode(AVLNode* root, int key);
void freeTree(AVLNode* root);