#include <stdlib.h>
#include "treap.h"
#include <limits.h>

int int_max(int a, int b) {
    return a > b ? a : b;
}

int get_max(TreapNode* node) {
    return node ? node->max_value : INT_MIN;
}

void update(TreapNode* node) {
    if (node) {
        node->max_value = int_max(node->value, int_max(get_max(node->left), get_max(node->right)));
    }
}

TreapNode* create_node(int key, int value, int priority) {
    TreapNode* node = (TreapNode*)malloc(sizeof(TreapNode));
    node->key = key;
    node->value = value;
    node->priority = priority;
    node->max_value = value;
    node->left = node->right = NULL;
    return node;
}

void split(TreapNode* root, int key, TreapNode** left, TreapNode** right) {
    if (!root) {
        *left = *right = NULL;
    }
    else if (key <= root->key) {
        split(root->left, key, left, &root->left);
        *right = root;
    }
    else {
        split(root->right, key, &root->right, right);
        *left = root;
    }
    update(root);
}

TreapNode* merge(TreapNode* left, TreapNode* right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

TreapNode* insert(TreapNode* root, TreapNode* node) {
    if (!root) return node;
    if (node->priority > root->priority) {
        split(root, node->key, &node->left, &node->right);
        update(node);
        return node;
    }
    if (node->key < root->key) root->left = insert(root->left, node);
    else root->right = insert(root->right, node);
    update(root);
    return root;
}

int range_max_query(TreapNode* root, int x, int y) {
    TreapNode* left, * middle, * right;
    split(root, x, &left, &middle);
    TreapNode* middle2;
    split(middle, y, &middle2, &right);

    int result = get_max(middle2);

    TreapNode* tmp = merge(middle2, right);
    root = merge(left, tmp);

    return result;
}

void free_treap(TreapNode* root) {
    if (!root) return;
    free_treap(root->left);
    free_treap(root->right);
    free(root);
}