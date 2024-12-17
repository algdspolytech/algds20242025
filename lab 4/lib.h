#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char *data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(const char *data);


Node* insert(Node *root, const char *data);

void printInOrder(Node *root);

void saveToFile(Node *root, FILE *file);

Node* loadFromFile(FILE *file);


void freeTree(Node *root);



#endif