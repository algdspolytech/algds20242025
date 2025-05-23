#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

RBTree* createTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->TNULL = makeNode(0); // Технический узел
    tree->TNULL->color = BLACK;
    tree->root = tree->TNULL;
    return tree;
}

Node* makeNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED; // Новый узел всегда красный
    node->left = node->right = node->parent = NULL;
    return node;
}

void rotateRight(RBTree* tree, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != tree->TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void balanceAfterAdd(RBTree* tree, Node* k) {
    Node* u;
    while (k != tree->root && k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(tree, k->parent->parent);
            }
        }
        else {
            u = k->parent->parent->right;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    rotateLeft(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateRight(tree, k->parent->parent);
            }
        }
        if (k == tree->root) break;
    }
    tree->root->color = BLACK;
}

void rotateLeft(RBTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void transplant(RBTree* tree, Node* u, Node* v) {
    if (u->parent == NULL) {
        tree->root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void addNode(RBTree* tree, int key) {
    Node* node = makeNode(key);
    Node* y = NULL;
    Node* x = tree->root;

    while (x != tree->TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == NULL) {
        tree->root = node;
    }
    else if (node->data < y->data) {
        y->left = node;
    }
    else {
        y->right = node;
    }
    node->left = node->right = tree->TNULL;
    balanceAfterAdd(tree, node);
}

Node* findNode(RBTree* tree, int key) {
    Node* current = tree->root;
    while (current != tree->TNULL && current->data != key) {
        if (key < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return current;
}

void balanceAfterDelete(RBTree* tree, Node* x) {
    Node* w;
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(tree, x->parent);
                x = tree->root;
            }
        }
        else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

Node* getMinimum(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void removeNode(RBTree* tree, Node* z) {
    Node* y = z;
    Node* x;
    int originalColor = y->color;

    if (z->left == tree->TNULL) {
        x = z->right;
        transplant(tree, z, z->right);
    }
    else if (z->right == tree->TNULL) {
        x = z->left;
        transplant(tree, z, z->left);
    }
    else {
        y = getMinimum(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (originalColor == BLACK) {
        balanceAfterDelete(tree, x);
    }
}

void displayTree(Node* node, Node* TNULL, int space) {
    if (node == TNULL) return;

    space += 10;
    displayTree(node->right, TNULL, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d(%s)\n", node->data, node->color == RED ? "R" : "B");

    displayTree(node->left, TNULL, space);
}