#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int minLeafHeight;
} Node;

Node* createNode(int value);
int calculateMinLeafHeight(Node* root);
int treeHeight(Node* root);
void fillTreeLevel(Node* root, char** lines, int level, int start, int end);
void printTreeToFilePyramid(Node* root, FILE* file);


