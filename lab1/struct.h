#ifndef struct_h
#define struct_h

#include <stdio.h>

typedef struct Node {
    int data;          
    int subtree_size;    
    struct Node* left;    
    struct Node* right;  
} Node;

#endif