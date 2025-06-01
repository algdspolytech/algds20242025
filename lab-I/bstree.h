#ifndef BSTREE_H
#define BSTREE_H

typedef struct BSTreeNode {
    int data;
    struct BSTreeNode* left, * right;
} BSTreeNode;

typedef struct {
    BSTreeNode* root;
} BSTree;

void initBSTree(BSTree* tree);
void insertBSTree(BSTree* tree, int data);
BSTreeNode* searchBSTree(BSTree* tree, int data);
void freeBSTree(BSTree* tree);

#endif // BSTREE_H