#ifndef BTREE_H
#define BTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct btree 
{
    char value;
    struct btree* left;
    struct btree* right;
    unsigned int leaf_count;
}; 

void pushBack(struct btree**, char);

unsigned int countLeafs(struct btree*);

unsigned int get_height(struct btree*);

int** getMatrix(struct btree*, unsigned int*, unsigned int*);

void deleteTree(struct btree*);

void printMatrix(int**, unsigned int, unsigned int);

#endif 
