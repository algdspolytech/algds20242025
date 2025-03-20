#define _CRT_SECURE_NO_WARNINGS

#include "funcs.h"
#include "structs.h"

Node* createNode(int data, Color color, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = color;
    node->left = node->right = NULL;
    node->parent = parent;
    return node;
}

void leftRotate(RBTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTree* tree, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) tree->root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void insertFixup(RBTree* tree, Node* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(RBTree* tree, int data) {
    Node* y = NULL;
    Node* x = tree->root;

    // ѕоиск места дл€ вставки и проверка на дубликат
    while (x) {
        y = x;
        if (data < x->data) {
            x = x->left;
        }
        else if (data > x->data) {
            x = x->right;
        }
        else {
            // Ќайден дубликат, не вставл€ем узел
            return;
        }
    }

    Node* z = createNode(data, RED, y);
    if (!y) {
        tree->root = z;
    }
    else if (data < y->data) {
        y->left = z;
    }
    else {
        y->right = z;
    }

    insertFixup(tree, z);
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void mergeTrees(RBTree* tree, Node* root) {
    if (!root) return;
    mergeTrees(tree, root->left);
    insert(tree, root->data);
    mergeTrees(tree, root->right);
}

RBTree* unionRBTree(RBTree* S1, int x, RBTree* S2) {
    RBTree* newTree = (RBTree*)malloc(sizeof(RBTree));
    newTree->root = NULL;
    mergeTrees(newTree, S1->root);
    insert(newTree, x);
    mergeTrees(newTree, S2->root);
    return newTree;
}