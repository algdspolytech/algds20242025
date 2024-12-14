#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->count = 1;
    return node;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }

    root->count = 1 + (root->left ? root->left->count : 0) + (root->right ? root->right->count : 0);
    
    return root;
}

int kthSmallest(Node* root, int K, int* count) {
    if (root == NULL) {
        return -1;
    }

    int leftCount = (root->left ? root->left->count : 0);
    if (K <= leftCount) {
        return kthSmallest(root->left, K, count);
    } else if (K == leftCount + 1) {
        return root->data;
    } else {
        return kthSmallest(root->right, K - leftCount - 1, count);
    }
}

void printElementsLessThanK(Node* root, int K) {
    if (root == NULL || K <= 0) {
        return;
    }

    static int index = 0;

    printElementsLessThanK(root->left, K);

    if (index < K) {
        printf("%d ", root->data);
        index++;
    }

    printElementsLessThanK(root->right, K);
}