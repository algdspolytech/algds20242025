#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct BSTNode {
    int key;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode* newBSTNode(int key);

BSTNode* BSTInsert(BSTNode* node, int key);

BSTNode* BSTDelete(BSTNode* root, int key);

int BSTSearch(BSTNode* root, int key);