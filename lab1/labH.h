#ifndef LABF_H
#define LABF_H

typedef struct SplayNode {
    int key;
    struct SplayNode *left;
    struct SplayNode *right;
} SplayNode;

SplayNode *newNode(int key);

SplayNode *rightRotate(SplayNode *y);

SplayNode *leftRotate(SplayNode *x);

SplayNode *splay(SplayNode *root, int key);

SplayNode *search(SplayNode *root, int key);

SplayNode *insert(SplayNode *root, int key);

SplayNode *deleteNode(SplayNode *root, int key);

void inorder(SplayNode *root);

void freeTree(SplayNode *root);

#endif
