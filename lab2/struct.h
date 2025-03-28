#ifndef struct_h
#define struct_h

#include <stdio.h>

typedef struct Node {
    int data;
    int minLeafHeight;
    struct Node* left, * right;
} Node;

#endif