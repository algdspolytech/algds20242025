#include "bst_tree.h"
#include <stdlib.h>

BSTNode* newBSTNode(int key) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode* bst_insert(BSTNode* node, int key) {
    if (!node) return newBSTNode(key);

    if (key < node->key)
        node->left = bst_insert(node->left, key);
    else if (key > node->key)
        node->right = bst_insert(node->right, key);

    return node;
}

BSTNode* bst_minValueNode(BSTNode* node) {
    BSTNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

BSTNode* bst_remove(BSTNode* node, int key) {
    if (!node) return node;

    if (key < node->key)
        node->left = bst_remove(node->left, key);
    else if (key > node->key)
        node->right = bst_remove(node->right, key);
    else {
        if (!node->left) {
            BSTNode* temp = node->right;
            free(node);
            return temp;
        } else if (!node->right) {
            BSTNode* temp = node->left;
            free(node);
            return temp;
        }

        BSTNode* temp = bst_minValueNode(node->right);
        node->key = temp->key;
        node->right = bst_remove(node->right, temp->key);
    }
    return node;
}

int bst_search(BSTNode* node, int key) {
    if (!node) return 0;
    if (node->key == key) return 1;
    if (key < node->key)
        return bst_search(node->left, key);
    else
        return bst_search(node->right, key);
}

void BSTree_init(BSTree* tree) {
    tree->root = NULL;
}

void BSTree_insert(BSTree* tree, int key) {
    tree->root = bst_insert(tree->root, key);
}

int BSTree_search(BSTree* tree, int key) {
    return bst_search(tree->root, key);
}

void BSTree_remove(BSTree* tree, int key) {
    tree->root = bst_remove(tree->root, key);
}

void BSTree_free(BSTree* tree) {
    while (tree->root) {
        BSTree_remove(tree, tree->root->key);
    }
}
