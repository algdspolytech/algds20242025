#include "treap.h"
#include <stdlib.h>
#include <time.h>

static void update_stats(Node* node) {
    node->sum = node->c;
    node->min_key = node->key;
    node->max_key = node->key;

    if (node->left) {
        node->sum += node->left->sum;
        if (node->left->min_key < node->min_key)
            node->min_key = node->left->min_key;
        if (node->left->max_key > node->max_key)
            node->max_key = node->left->max_key;
    }

    if (node->right) {
        node->sum += node->right->sum;
        if (node->right->min_key < node->min_key)
            node->min_key = node->right->min_key;
        if (node->right->max_key > node->max_key)
            node->max_key = node->right->max_key;
    }
}

static void split(Node* root, int key, Node** left, Node** right) {
    if (!root) {
        *left = NULL;
        *right = NULL;
        return;
    }

    if (root->key <= key) {
        split(root->right, key, &root->right, right);
        *left = root;
    }
    else {
        split(root->left, key, left, &root->left);
        *right = root;
    }
    update_stats(root);
}

static Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update_stats(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        update_stats(right);
        return right;
    }
}

Node* create_node(int key, int c) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->c = c;
    node->priority = rand() % 1000;
    node->left = node->right = NULL;
    update_stats(node);
    return node;
}

Node* insert(Node* root, Node* new_node) {
    if (!root) return new_node;

    if (new_node->priority > root->priority) {
        split(root, new_node->key, &new_node->left, &new_node->right);
        update_stats(new_node);
        return new_node;
    }

    if (new_node->key < root->key)
        root->left = insert(root->left, new_node);
    else
        root->right = insert(root->right, new_node);

    update_stats(root);
    return root;
}

int get_sum(Node* root, int x, int y) {
    if (!root) return 0;

    if (root->max_key < x || root->min_key >= y)
        return 0;

    int sum = 0;
    if (x <= root->key && root->key < y)
        sum += root->c;

    return sum + get_sum(root->left, x, y) + get_sum(root->right, x, y);
}

void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}