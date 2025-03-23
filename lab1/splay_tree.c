#include "splay_tree.h"
#include <stdlib.h>

static Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

static Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node* root, int key) {
    if (root == NULL) return NULL;

    Node dummy = {0, NULL, NULL};
    Node* leftMax = &dummy;
    Node* rightMin = &dummy;
    Node* current = root;

    while (1) {
        if (key < current->key) {
            if (current->left == NULL) break;
            if (key < current->left->key) {
                Node* child = current->left;
                current->left = child->right;
                child->right = current;
                current = child;
                if (current->left == NULL) break;
            }
            rightMin->left = current;
            rightMin = current;
            current = current->left;
        } else if (key > current->key) {
            if (current->right == NULL) break;
            if (key > current->right->key) {
                Node* child = current->right;
                current->right = child->left;
                child->left = current;
                current = child;
                if (current->right == NULL) break;
            }
            leftMax->right = current;
            leftMax = current;
            current = current->right;
        } else {
            break;
        }
    }

    leftMax->right = current->left;
    rightMin->left = current->right;
    current->left = dummy.right;
    current->right = dummy.left;

    return current;
}

Node* insert(Node* root, int key) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    root = splay(root, key);

    if (root->key == key) {
        return root;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;

    if (key < root->key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }

    return newNode;
}

Node* delete(Node* root, int key) {
    if (root == NULL) return NULL;

    root = splay(root, key);

    if (root->key != key) {
        return root;
    }

    Node* leftSubtree = root->left;
    Node* rightSubtree = root->right;
    free(root);

    if (leftSubtree == NULL) {
        return rightSubtree;
    }

    Node* newRoot = leftSubtree;
    while (newRoot->right != NULL) {
        newRoot = newRoot->right;
    }
    leftSubtree = splay(leftSubtree, newRoot->key);
    leftSubtree->right = rightSubtree;

    return leftSubtree;
}

Node* search(Node* root, int key, int* found) {
    if (root == NULL) {
        *found = 0;
        return NULL;
    }

    root = splay(root, key);
    *found = (root->key == key) ? 1 : 0;
    return root;
}

void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}