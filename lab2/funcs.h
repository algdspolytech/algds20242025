#ifndef funcs_h
#define funcs_h

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void freeTree(Node* root);
Node* createNode(int data);
void printTree(Node* root);
int calculateMinLeafHeight(Node* root);

#endif