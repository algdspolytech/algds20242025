#include "treap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->priority = rand();
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void split(Node* root, int key, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }

    if (root->key <= key) {
        split(root->right, key, &root->right, right);
        *left = root;
    } else {
        split(root->left, key, left, &root->left);
        *right = root;
    }
}

Node* insert(Node* root, int key) {
    Node* newNode = createNode(key);
    Node* left = NULL;
    Node* right = NULL;
    split(root, key, &left, &right);
    return merge(merge(left, newNode), right);
}

Node* deleteNode(Node* root, int key) {
    Node* left = NULL;
    Node* right = NULL;
    Node* mid = NULL;
    split(root, key - 1, &left, &right);
    split(right, key, &mid, &right);
    if (mid) free(mid);
    return merge(left, right);
}

bool search(Node* root, int key) {
    if (!root) return false;
    if (root->key == key) return true;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}