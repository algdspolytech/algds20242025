#include <stdio.h>
#pragma once

#ifndef MAIN_H
#define MAIN_H
#define MAX_STRING_LENGTH 256

typedef struct Node {
    char data[MAX_STRING_LENGTH];
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(const char* data);
void addNode(Node* root);
void saveTree(FILE* file, Node* root);
Node* loadTree(FILE* file);
void printTree(Node* root, int level);
void freeTree(Node* root);

#endif