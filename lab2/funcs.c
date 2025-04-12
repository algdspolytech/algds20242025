#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key) {
        if (root->left == NULL) return root;

        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }

    else {
        if (root->right == NULL) return root;

        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

Node* search(Node* root, int key) {
    return splay(root, key);
}

Node* insert(Node* root, int key) {
    if (root == NULL) return newNode(key);

    root = splay(root, key);

    if (root->key == key) return root; 

    Node* new_node = newNode(key);
    if (key < root->key) {
        new_node->right = root;
        new_node->left = root->left;
        root->left = NULL;
    }
    else {
        new_node->left = root;
        new_node->right = root->right;
        root->right = NULL;
    }
    return new_node;
}

Node* delete(Node* root, int key) {
    if (root == NULL) return NULL;

    root = splay(root, key);

    if (root->key != key) return root; 

    Node* newRoot;
    if (root->left == NULL)
        newRoot = root->right;
    else {
        newRoot = splay(root->left, key);
        newRoot->right = root->right;
    }
    free(root);
    return newRoot;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}