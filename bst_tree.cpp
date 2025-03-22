#include "bst_tree.h"

BSTree::BSTree() : root(nullptr) {}

BSTNode* BSTree::insert(BSTNode* node, int key) {
    if (!node) return new BSTNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

BSTNode* BSTree::minValueNode(BSTNode* node) {
    BSTNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

BSTNode* BSTree::remove(BSTNode* node, int key) {
    if (!node) return node;

    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        if (!node->left) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        BSTNode* temp = minValueNode(node->right);
        node->key = temp->key;
        node->right = remove(node->right, temp->key);
    }
    return node;
}

bool BSTree::search(BSTNode* node, int key) {
    if (!node) return false;
    if (node->key == key) return true;
    if (key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}

void BSTree::insert(int key) { root = insert(root, key); }
void BSTree::remove(int key) { root = remove(root, key); }
bool BSTree::search(int key) { return search(root, key); }
