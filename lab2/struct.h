#ifndef structs_h
#define structs_h

#include <stdio.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

#endif