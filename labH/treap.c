#include "treap.h"


void free_tree(Node* root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

Node* create_node(int key, int priority) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->priority = priority;
    node->left = node->right = NULL;
    return node;
}

Node* right_rotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

Node* left_rotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* insert(Node* root, int key, int priority) {
    if (!root)
        return create_node(key, priority);
    if (key < root->key) {
        root->left = insert(root->left, key, priority);
        if (root->left->priority > root->priority)
            root = right_rotate(root);
    } else {
        root->right = insert(root->right, key, priority);
        if (root->right->priority > root->priority)
            root = left_rotate(root);
    }
    return root;
}

Node* remove(Node* root, int key) {
    if (!root)
        return NULL;
    if (key < root->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            if (root->left->priority > root->right->priority) {
                root = right_rotate(root);
                root->right = remove(root->right, key);
            } else {
                root = left_rotate(root);
                root->left = remove(root->left, key);
            }
        }
    }
    return root;
}

void split(Node* root, int key, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }
    if (root->key <= key) {
        *left = root;
        split(root->right, key, &((*left)->right), right);
    } else {
        *right = root;
        split(root->left, key, left, &((*right)->left));
    }
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}