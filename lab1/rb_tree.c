#include "rb_tree.h"
#include <stdlib.h>

Node NIL_SENTINEL = { 0, BLACK, &NIL_SENTINEL, &NIL_SENTINEL, &NIL_SENTINEL };
Node* NIL = &NIL_SENTINEL;

static Node* create_node(int key);
static void left_rotate(Node** root, Node* x);
static void right_rotate(Node** root, Node* x);
static void insert_fixup(Node** root, Node* z);
static void transplant(Node** root, Node* u, Node* v);
static Node* minimum(Node* x);
static void delete_fixup(Node** root, Node* x);

static Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = RED;
    node->left = NIL;
    node->right = NIL;
    node->parent = NIL;
    return node;
}

static void left_rotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

static void right_rotate(Node** root, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

static void insert_fixup(Node** root, Node* z) {
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
                    left_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(root, z->parent->parent);
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
                    right_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insert(Node** root, int key) {
    Node* z = create_node(key);
    Node* y = NIL;
    Node* x = *root;
    while (x != NIL) {
        y = x;
        x = (z->key < x->key) ? x->left : x->right;
    }
    z->parent = y;
    if (y == NIL) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    insert_fixup(root, z);
}

static void transplant(Node** root, Node* u, Node* v) {
    if (u->parent == NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

static Node* minimum(Node* x) {
    while (x->left != NIL) x = x->left;
    return x;
}

static void delete_fixup(Node** root, Node* x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(root, x->parent);
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
                    right_rotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(root, x->parent);
                x = *root;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(root, x->parent);
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
                    left_rotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

void delete(Node** root, int key) {
    Node* z = search(*root, key);
    if (z == NIL) return;

    Node* y = z;
    Node* x;
    Color y_original_color = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK)
        delete_fixup(root, x);
    free(z);
}

Node* search(Node* root, int key) {
    Node* x = root;
    while (x != NIL && key != x->key)
        x = (key < x->key) ? x->left : x->right;
    return x;
}

void free_tree(Node* root) {
    if (root == NIL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}