#include "treap.h"
#include <stdlib.h>
#include <stdio.h>

TreapNode* treap_create_node(int key, int priority) {
    TreapNode* node = (TreapNode*)malloc(sizeof(TreapNode));
    node->key = key;
    node->priority = priority;
    node->left = node->right = NULL;
    return node;
}

TreapNode* treap_merge(TreapNode* left, TreapNode* right) {
    if (!left) return right;
    if (!right) return left;
    if (left->priority > right->priority) {
        left->right = treap_merge(left->right, right);
        return left;
    }
    else {
        right->left = treap_merge(left, right->left);
        return right;
    }
}

void treap_split(TreapNode* root, int key, TreapNode** left, TreapNode** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }
    if (key < root->key) {
        treap_split(root->left, key, left, &root->left);
        *right = root;
    }
    else {
        treap_split(root->right, key, &root->right, right);
        *left = root;
    }
}

TreapNode* treap_insert(TreapNode* root, int key, int priority) {
    if (!root) return treap_create_node(key, priority);
    if (key == root->key) return root;

    if (priority > root->priority) {
        TreapNode* new_node = treap_create_node(key, priority);
        treap_split(root, key, &new_node->left, &new_node->right);
        return new_node;
    }

    if (key < root->key) root->left = treap_insert(root->left, key, priority);
    else root->right = treap_insert(root->right, key, priority);

    return root;
}

TreapNode* treap_delete(TreapNode* root, int key) {
    if (!root) return NULL;
    if (key == root->key) {
        TreapNode* new_root = treap_merge(root->left, root->right);
        free(root);
        return new_root;
    }
    if (key < root->key) root->left = treap_delete(root->left, key);
    else root->right = treap_delete(root->right, key);
    return root;
}

bool treap_search(TreapNode* root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    return treap_search((key < root->key) ? root->left : root->right, key);
}

void treap_destroy(TreapNode* root) {
    if (!root) return;
    treap_destroy(root->left);
    treap_destroy(root->right);
    free(root);
}

void treap_inorder(TreapNode* root) {
    if (!root) return;
    treap_inorder(root->left);
    printf("Key: %d, Priority: %d\n", root->key, root->priority);
    treap_inorder(root->right);
}

int treap_size(TreapNode* root) {
    if (!root) return 0;
    return 1 + treap_size(root->left) + treap_size(root->right);
}