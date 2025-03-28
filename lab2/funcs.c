#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->minLeafHeight = -1; 
    node->left = node->right = NULL;
    return node;
}

void printTree(Node* root) {
    if (root != NULL) {
        printf("Node %d -> MinLeafHeight: %d\n", root->data, root->minLeafHeight);
        printTree(root->left);
        printTree(root->right);
    }
}

int calculateMinLeafHeight(Node* root) {
    if (root == NULL) return INT_MAX; 
    if (root->left == NULL && root->right == NULL) {
        root->minLeafHeight = 0;
        return 0;  
    }

    int leftHeight = calculateMinLeafHeight(root->left);
    int rightHeight = calculateMinLeafHeight(root->right);

    root->minLeafHeight = 1 + (leftHeight < rightHeight ? leftHeight : rightHeight);
    return root->minLeafHeight;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}