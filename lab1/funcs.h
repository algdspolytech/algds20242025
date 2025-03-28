#ifndef funcs_h
#define funcs_h

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

Node* createNode(int data);
Node* insert(Node* root, int data);
Node* findKthSmallest(Node* root, int k);
void printElementsLessThanK(Node* root, int k, int* count);
void processKthSmallest(Node* root, int k);

#endif