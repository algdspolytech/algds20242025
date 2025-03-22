#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } NodeColor;

typedef struct Node {
    int data;
    NodeColor color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

Node* createNodeRBT(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

Node* grandparent(Node* n) {
    if ((n != NULL) && (n->parent != NULL))
        return n->parent->parent;
    else
        return NULL;
}

Node* uncle(Node* n) {
    Node* g = grandparent(n);
    if (g == NULL)
        return NULL;
    if (n->parent == g->left)
        return g->right;
    else
        return g->left;
}

Node* sibling(Node* n) {
    if (n == NULL || n->parent == NULL) {
        return NULL;
    }

    if (n == n->parent->left) {
        return n->parent->right;
    }

    return n->parent->left;
}

Node* findMin(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

void transplant(Node** root, Node* x, Node* y) {
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    if (y != NULL)
        y->parent = x->parent;
}

void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

void balanceInsert(Node** root, Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = uncle(z);
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                grandparent(z)->color = RED;
                z = grandparent(z);
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                grandparent(z)->color = RED;
                rightRotate(root, grandparent(z));
            }
        }
        else {
            Node* y = uncle(z);
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                grandparent(z)->color = RED;
                z = grandparent(z);
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                grandparent(z)->color = RED;
                leftRotate(root, grandparent(z));
            }
        }
    }
    (*root)->color = BLACK;
}

void insertRBT(Node** root, int data) {
    Node* z = createNodeRBT(data);
    Node* y = NULL;
    Node* x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    balanceInsert(root, z);
}

void balanceDelete(Node** root, Node* node) {
    while ((node->color == BLACK) && (node != *root)) {
        if (node == node->parent->left) {
            if (sibling(node)->color == RED) {
                sibling(node)->color = BLACK;
                node->parent->color = RED;
                leftRotate(root, node->parent);
            }
            if ((sibling(node)->left == NULL ||
                sibling(node)->left->color == BLACK) &&
                (sibling(node)->right == NULL ||
                    sibling(node)->right->color == BLACK)) {
                sibling(node)->color = RED;
                node = node->parent;
            }
            else {
                if (sibling(node)->right == NULL ||
                    sibling(node)->right->color == BLACK) {
                    if (sibling(node)->left != NULL)
                        sibling(node)->left->color = BLACK;
                    sibling(node)->color = RED;
                    rightRotate(root, sibling(node));
                }
                sibling(node)->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling(node)->right != NULL)
                    sibling(node)->right->color = BLACK;
                leftRotate(root, node->parent);
                node = *root;
            }
        }
        else {
            if (sibling(node)->color == RED) {
                sibling(node)->color = BLACK;
                node->parent->color = RED;
                rightRotate(root, node->parent);
            }
            if ((sibling(node)->right == NULL ||
                sibling(node)->right->color == BLACK) &&
                (sibling(node)->left == NULL ||
                    sibling(node)->left->color == BLACK)) {
                sibling(node)->color = RED;
                node = node->parent;
            }
            else {
                if (sibling(node)->left == NULL ||
                    sibling(node)->left->color == BLACK) {
                    if (sibling(node)->right != NULL)
                        sibling(node)->right->color = BLACK;
                    sibling(node)->color = RED;
                    leftRotate(root, sibling(node));
                }
                sibling(node)->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling(node)->left != NULL)
                    sibling(node)->left->color = BLACK;
                rightRotate(root, node->parent);
                node = *root;
            }
        }
    }

    if (node != NULL) {
        node->color = BLACK;
    }
}

void deleteRBT(Node** root, int data) {
    Node* node = *root;
    while (node != NULL) {
        if (node->data > data) {
            node = node->left;
        }
        else if (node->data < data) {
            node = node->right;
        }
        else
            break;
    }
    if (node == NULL)
        return;

    Node* x;
    Node* y = node;
    NodeColor yColor = y->color;

    if (node->left == NULL) {
        x = node->right;
        transplant(root, node, node->right);
    }
    else if (node->right == NULL) {
        x = node->left;
        transplant(root, node, node->left);
    }
    else {
        y = findMin(node->right);
        yColor = y->color;
        x = y->right;
        if (y->parent == node) {
            if (x != NULL)
                x->parent = y;
        }
        else {
            transplant(root, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(root, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    if (yColor == BLACK)
        balanceDelete(root, x);

    free(node);
}

Node* searchRBT(Node* root, int data) {
    Node* current = root;

    while (current != NULL && data != current->data) {
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    return current;
}

void free_tree(Node* root) {
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}