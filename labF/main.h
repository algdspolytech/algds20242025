#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int count;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct Tree {
    Node* root;
} Tree;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->count = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

Tree* createTree() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

void updateCount(Node* node) {
    while (node != NULL) {
        node->count = 1;
        if (node->left != NULL) {
            node->count += node->left->count;
        }
        if (node->right != NULL) {
            node->count += node->right->count;
        }
        node = node->parent;
    }
}

void insert(Tree* tree, int data) {
    Node* newNode = createNode(data);
    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    Node* current = tree->root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (current->left == NULL) {
            current = current->left;
        }
        else if (current->right == NULL) {
            current = current->right;
        }
        else if (current->left->count > current->right->count) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    newNode->parent = parent;
    if (parent->left == NULL) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    updateCount(parent);
}

void deleteNode(Tree* tree) {
    Node* current = tree->root;
    while (current->left != NULL || current->right != NULL) {
        if (current->left != NULL && current->left == NULL) {
            current = current->left;
        }
        else if (current->left == NULL && current->left != NULL) {
            current = current->right;
        }
        else {
            if (current->left->count > current->right->count) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
    }
    Node* parent = current->parent;
    if (parent->right == NULL) {
        parent->left = NULL;
    }
    else {
        parent->right = NULL;
    }
    updateCount(parent);
}

void inOrder(Node* node) {
    if (node != NULL) {
        inOrder(node->left);
        printf("%d ", node->data);
        inOrder(node->right);
    }
}