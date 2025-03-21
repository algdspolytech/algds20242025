#include "BSTTreee.h"

BSTNode* newBSTNode(int key) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode* BSTInsert(BSTNode* node, int key) {
    if (node == NULL) return newBSTNode(key);
    
    if (key < node->key)
        node->left = BSTInsert(node->left, key);
    else if (key > node->key)
        node->right = BSTInsert(node->right, key);
    
    return node;
}

BSTNode* BSTDelete(BSTNode* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = BSTDelete(root->left, key);
    else if (key > root->key)
        root->right = BSTDelete(root->right, key);
    else {
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }

        BSTNode* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        
        root->key = temp->key;
        root->right = BSTDelete(root->right, temp->key);
    }
    return root;
}

int BSTSearch(BSTNode* root, int key) {
    if (root == NULL) return 0;
    if (root->key == key) return 1;
    return key < root->key ? BSTSearch(root->left, key) : BSTSearch(root->right, key);
}