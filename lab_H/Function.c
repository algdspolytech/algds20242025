#include <stdlib.h>
#include "Header.h"

Node* createNode(long long x, long long c) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->x = x;
    node->c = c;
    node->priority = rand();
    node->sum = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void updateSum(Node* node) {
    if (!node) return;
    node->sum = node->c;
    if (node->left) node->sum += node->left->sum;
    if (node->right) node->sum += node->right->sum;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        updateSum(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        updateSum(right);
        return right;
    }
}

void split(Node* root, long long key, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }

    if (root->x < key) {
        *left = root;
        split(root->right, key, &(root->right), right);
        updateSum(*left);
    }
    else {
        *right = root;
        split(root->left, key, left, &(root->left));
        updateSum(*right);
    }
}

long long rangeSum(Node* root, long long x, long long y) {
    Node* left, * middle, * right;
    split(root, x, &left, &middle);
    split(middle, y, &middle, &right);

    long long result = middle ? middle->sum : 0;

    root = merge(merge(left, middle), right);
    return result;
}

void insert(Node** root, long long x, long long c) {
    Node* newNode = createNode(x, c);
    Node* left, * right;
    split(*root, x, &left, &right);
    *root = merge(merge(left, newNode), right);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}