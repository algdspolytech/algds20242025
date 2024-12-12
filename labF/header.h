#pragma once
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int count;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->count = 1;
    return node;
}

Node* insert(Node* root, int data) {
    if (root == NULL)
        return newNode(data);

    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    root->count = 1 + ((root->left) ? root->left->count : 0) +
        ((root->right) ? root->right->count : 0);
    return root;
}

Node* findKthSmallest(Node* root, int k) {
    if (root == NULL)
        return NULL;

    int leftCount = (root->left) ? root->left->count : 0;

    if (k <= leftCount) {
        return findKthSmallest(root->left, k);
    }
    else if (k == leftCount + 1) {
        return root;
    }
    else {
        return findKthSmallest(root->right, k - leftCount - 1);
    }
}

int KIsEven(Node* kthSmallestNode) {
    if (kthSmallestNode->data % 2 == 0) {
        printf("Elements with number less than K: ");
        return 1;
    }
    else {
        return 0;
    }
}
void printLessThanK(Node* root, int K) {
    if (root == NULL) {
        return;
    }

    printLessThanK(root->left, K);

    if (root->data < K) {
        printf("%d ", root->data);
    }

    printLessThanK(root->right, K);
}