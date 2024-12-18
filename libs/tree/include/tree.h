#ifndef TREE_H
#define TREE_H
#include<stdio.h>

typedef struct Node {
    int data;
    int reqCnt;

    struct Node *parent;
    struct Node *left;
    struct Node *right;
} TREE_Node_t;


TREE_Node_t* TREE_CreateTreeFromFile(FILE* file);
void TREE_DeleteTree(TREE_Node_t* root);

#endif //TREE_H
