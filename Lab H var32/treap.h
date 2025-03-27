#pragma once

typedef struct treapnode{
	int x;
	int c;
	struct treapnode* left, * right;
}treapnode;

void swap(int** pairs, int i, int j);

void qsortpair(int** pairs, int a, int b);

int** createpairs(int size, int* x, int* c);

treapnode* createtreapnode(int x, int c);

void split(treapnode* root, int key, treapnode** pleft, treapnode** pright);

treapnode* inserttreapnode(treapnode* root, treapnode* newnode);

treapnode* createtreap(int* x, int* c, int size);

void addtreap(treapnode* root, int* sum, int a, int b);

int sumtreap(treapnode* root, int a, int b);

void printreap(treapnode* root);

