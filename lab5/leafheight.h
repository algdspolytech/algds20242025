#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Branch {
    int value;          
    struct Branch* left;  
    struct Branch* right; 
} Branch;

Branch* createBranch(int value);

void clearTree(Branch* root);

int minLeafHeight(Branch* root);

void updateMinLeafHeights(Branch* root);

void printTreeToFile(Branch* root, int space, FILE* file);