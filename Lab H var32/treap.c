#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "treap.h"


void swap(int** pairs, int i, int j) {
	for (int k = 0; k < 2; k++) {
		int buff = pairs[j][k];
		pairs[j][k] = pairs[i][k];
		pairs[i][k] = buff;
	}
}

void qsortpair(int** pairs, int a, int b) {
	if (a >= b) {
		return;
	}
	int pivot = pairs[(a + b) / 2][1];
	int m = a;
	for (int i = a; i <= b; i++) {
		if (pairs[i][1] > pivot) {
			swap(pairs, m, i);
			m++;
		}
	}
	qsortpair(pairs, a, m-1);
	for (int i = a; i <= b; i++) {
		if (pairs[i][1] == pivot) {
			swap(pairs, m, i);
			m++;
		}
	}
	qsortpair(pairs, m, b);
}

int** createpairs(int size, int* x, int* c) {
	int** pairs = malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		pairs[i] = malloc(2 * sizeof(int));
		pairs[i][0] = x[i];
		pairs[i][1] = c[i];
	}
	return pairs;
}

treapnode* createtreapnode(int x, int c) {
	treapnode* res = malloc(sizeof(treapnode));
	res->x = x;
	res->c = c;
	res->left = NULL;
	res->right = NULL;
	return res;
}

void split(treapnode* root, int key, treapnode** pleft, treapnode** pright) {
	if (!root) {
		return;
	}
	if (root->x <= key) {
		treapnode* rtreap = NULL;
		split(root->right, key, &rtreap, pright);
		root->right = rtreap;
		*pleft = root;
	}
	else {
		treapnode* ltreap = NULL;
		split(root->left, key, pleft, &ltreap);
		root->left = ltreap;
		*pright = root;
	}
}

treapnode* inserttreapnode(treapnode* root, treapnode* newnode){
	if (!root) 
		return newnode;

	if (newnode->c > root->c) {
		split(root, newnode->x, &newnode->left, &newnode->right);
		return newnode;
	}

	if (newnode->x <= root->x)
		root->left = inserttreapnode(root->left, newnode);
	else
		root->right = inserttreapnode(root->right, newnode);

	return root;
}


treapnode* createtreap(int* x, int* c, int size) {
	if (x == NULL || c == NULL) {
		return NULL;
	}
	int** pairs = createpairs(size, x, c);

	qsortpair(pairs, 0, size - 1);


	treapnode* root = createtreapnode(pairs[0][0], pairs[0][1]);
	treapnode* newnode;
	for (int i = 1; i < size; i++) {
		newnode = createtreapnode(pairs[i][0], pairs[i][1]);
		inserttreapnode(root, newnode);
	}
	return root;
}

void addtreap(treapnode* root, int* sum, int a, int b) {
	if (root == NULL) {
		return;
	}
	if (a <= root->x && b > root->x)
		*sum += root->c;
	addtreap(root->left, sum, a, b);
	addtreap(root->right, sum, a, b);
}
int sumtreap(treapnode* root, int a, int b) {
	int sum = 0;
	addtreap(root, &sum, a, b);
	return sum;
}


void printreap(treapnode* root) {
	if (root == NULL) {
		return;
	}
	printf("%i %i \n", root->x, root->c);

	printreap(root->left);
	printreap(root->right);
}


