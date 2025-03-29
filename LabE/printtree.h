#pragma once


typedef struct node {
    int x;      
    struct node* left;   
    struct node* right;
} node;

node* createnode(int x, node* left, node* right);

void freetree(node* node);

node* readtree(FILE* FILE);

void displaytree1(FILE* out, node* tree);

void displaytree2(FILE* out, node* tree);

void displayfile(FILE* FILE);