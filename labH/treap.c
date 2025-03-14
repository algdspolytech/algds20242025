#include "treap.h"
#include <stdlib.h>
#include <stdbool.h>

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->priority = rand();
    node->left = node->right = NULL;
    return node;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

Node* insert(Node* root, int key) {
    if (search(root, key) != NULL)
        return root;

    if (root == NULL)
        return newNode(key);

    if (key <= root->key) {
        root->left = insert(root->left, key);
        if (root->left->priority > root->priority) {
            Node* newRoot = root->left;
            root->left = newRoot->right;
            newRoot->right = root;
            root = newRoot;
        }
    } else {
        root->right = insert(root->right, key);
        if (root->right->priority > root->priority) {
            Node* newRoot = root->right;
            root->right = newRoot->left;
            newRoot->left = root;
            root = newRoot;
        }
    }
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            root = temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            root = temp;
        } else {
            if (root->left->priority > root->right->priority) {
                Node* newRoot = root->left;
                root->left = newRoot->right;
                newRoot->right = root;
                root = newRoot;
                root->right = deleteNode(root->right, key);
            } else {
                Node* newRoot = root->right;
                root->right = newRoot->left;
                newRoot->left = root;
                root = newRoot;
                root->left = deleteNode(root->left, key);
            }
        }
    }
    return root;
}

static bool isBSTUtil(Node* node, int min, int max) {
    if (node == NULL)
        return true;
    if (node->key < min || node->key > max)
        return false;
    return isBSTUtil(node->left, min, node->key) && 
           isBSTUtil(node->right, node->key + 1, max);
}

bool isBST(Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

static bool isHeapUtil(Node* node) {
    if (node == NULL)
        return true;
    bool valid = true;
    if (node->left)
        valid &= (node->priority >= node->left->priority);
    if (node->right)
        valid &= (node->priority >= node->right->priority);
    return valid && isHeapUtil(node->left) && isHeapUtil(node->right);
}

bool isHeap(Node* root) {
    return isHeapUtil(root);
}

bool isTreap(Node* root) {
    return isBST(root) && isHeap(root);
}