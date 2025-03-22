#include "bstree.h"
#include <stdlib.h>

void initBSTree(BSTree* tree) {
    tree->root = NULL;
}

void insertBSTreeHelper(BSTreeNode** node, int data) {
    if (*node == NULL) {
        *node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
        (*node)->data = data;
        (*node)->left = (*node)->right = NULL;
    }
    else if (data < (*node)->data) {
        insertBSTreeHelper(&(*node)->left, data);
    }
    else {
        insertBSTreeHelper(&(*node)->right, data);
    }
}

void insertBSTree(BSTree* tree, int data) {
    insertBSTreeHelper(&tree->root, data);
}

BSTreeNode* searchBSTreeHelper(BSTreeNode* node, int data) {
    if (node == NULL || node->data == data) {
        return node;
    }
    if (data < node->data) {
        return searchBSTreeHelper(node->left, data);
    }
    else {
        return searchBSTreeHelper(node->right, data);
    }
}

BSTreeNode* searchBSTree(BSTree* tree, int data) {
    return searchBSTreeHelper(tree->root, data);
}

void freeBSTreeHelper(BSTreeNode* node) {
    if (node != NULL) {
        freeBSTreeHelper(node->left);
        freeBSTreeHelper(node->right);
        free(node);
    }
}

void freeBSTree(BSTree* tree) {
    freeBSTreeHelper(tree->root);
}