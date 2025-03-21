#include "code.h"


Node* createNode(int key, Color color, Node* nil) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = color;
    node->left = node->right = node->parent = nil;
    return node;
}

RBTree* createRBTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = createNode(0, BLACK, NULL);
    tree->root = tree->nil;
    return tree;
}

void leftRotate(RBTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil) {
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

void rightRotate(RBTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->nil) {
        tree->root = x;
    }
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void insertFixup(RBTree* tree, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
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
            if (y->color == RED) {
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

void insert(RBTree* tree, int key) {
    Node* z = createNode(key, RED, tree->nil);
    Node* y = tree->nil;
    Node* x = tree->root;
    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == tree->nil) {
        tree->root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    insertFixup(tree, z);
}

void mergeTrees(RBTree* t1, RBTree* t2, int x) {
    insert(t1, x);
    Node* node = t2->root;
    while (node != t2->nil) {
        insert(t1, node->key);
        node = node->right;
    }
    free(t2);
}

void inorder(Node* node, Node* nil) {
    if (node != nil) {
        inorder(node->left, nil);
        printf("%d ", node->key);
        inorder(node->right, nil);
    }
}


