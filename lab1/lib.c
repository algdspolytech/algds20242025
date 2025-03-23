#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include "lib.h"

RBTree* createRBTree();
Node* createNode(int data);
void leftRotate(RBTree *tree, Node *x);
void rightRotate(RBTree *tree, Node *y);
void insert(RBTree *tree, int data);
void insertFix(RBTree *tree, Node *k);
Node* search(RBTree *tree, int data);
void deleteNode(RBTree *tree, int data);
void deleteFix(RBTree *tree, Node *x);
void inorderHelper(Node *node);

// Function implementations
RBTree* createRBTree() {
    RBTree *tree = (RBTree*)malloc(sizeof(RBTree));
    tree->TNULL = createNode(0);
    tree->TNULL->color = BLACK;
    tree->root = tree->TNULL;
    return tree;
}

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    newNode->color = RED;
    return newNode;
}

// Left rotation
void leftRotate(RBTree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != tree->TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


void rightRotate(RBTree *tree, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != tree->TNULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        tree->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void insert(RBTree *tree, int data) {
    Node *node = createNode(data);
    Node *y = NULL;
    Node *x = tree->root;

    while (x != tree->TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == NULL) {
        tree->root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }
    node->left = node->right = tree->TNULL;
    insertFix(tree, node);
}

void insertFix(RBTree *tree, Node *k) {
    Node *u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            u = k->parent->parent->right;
            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(tree, k->parent->parent);
            }
        } else {
            u = k->parent->parent->left;
            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(tree, k->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

Node* search(RBTree *tree, int data) {
    Node *current = tree->root;
    while (current != tree->TNULL) {
        if (data == current->data) {
            return current;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void deleteNode(RBTree *tree, int data) {
    Node *z = tree->root;
    Node *x, *y;
    
    while (z != tree->TNULL) {
        if (z->data == data) {
            break;
        } else if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    if (z == tree->TNULL) {
        printf("Node not found in the tree.\n");
        return;
    }

    y = z;
    int yOriginalColor = y->color;

    if (z->left == tree->TNULL) {
        x = z->right;
        if (x != tree->TNULL) {
            x->parent = z->parent;
        }
        if (z->parent == NULL) {
            tree->root = x;
        } else if (z == z->parent->left) {
            z->parent->left = x;
        } else {
            z->parent->right = x;
        }
    } else if (z->right == tree->TNULL) {
        x = z->left;
        if (x != tree->TNULL) {
            x->parent = z->parent;
        }
        if (z->parent == NULL) {
            tree->root = x;
        } else if (z == z->parent->left) {
            z->parent->left = x;
        } else {
            z->parent->right = x;
        }
    } else {
        y = z->right;
        while (y->left != tree->TNULL) {
            y = y->left;
        }
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            if (x != tree->TNULL) {
                x->parent = y->parent;
            }
            y->parent->left = x;
            y->right = z->right;
            y->right->parent = y;
        }
        if (z->parent == NULL) {
            tree->root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->parent = z->parent;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == BLACK) {
        deleteFix(tree, x);
    }
}


void inorderHelper(Node *node) {
    if (node != NULL) {
        inorderHelper(node->left);
        printf("%d ", node->data);
        inorderHelper(node->right);
    }
}

void inorder(RBTree *tree) {
    inorderHelper(tree->root);
}

