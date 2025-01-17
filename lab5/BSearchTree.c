#include "BSearchTree.h"

BinaryTreeNode* Create(int key) {
    BinaryTreeNode* new_node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->size = 1;
    return new_node;
}

void UpdateSize(BinaryTreeNode* node) {
    if (node) {
        int leftSize = 0;
        int rightSize = 0;
    if (node->left) {
        leftSize = node->left->size;
    }
    if (node->right) {
        rightSize = node->right->size;
    } 
    node->size = 1 + leftSize + rightSize;
    }
}

BinaryTreeNode* Insert(BinaryTreeNode* node, int value) {
    if (node == NULL) {
        return Create(value);
    }

    if (value < node->key) {
        node->left = Insert(node->left, value);
    }
    else if (value > node->key) {
        node->right = Insert(node->right, value);
    }
    UpdateSize(node); 
    return node;
}

int FindNumElem(BinaryTreeNode* node, int key) {
    int order = 0; 
    BinaryTreeNode* current = node;

    while (current != NULL) {
        int leftSize = 0 ; 

        if (current->left != NULL) {
            leftSize = current->left->size;
        }
        if (key == current->key) {
            order += leftSize + 1;
            return order;
        }
        if (key < current->key) {
            current = current->left; 
        }
        else {
            order += leftSize + 1; 
            current = current->right;
        }
    }
    return -1; 
}

BinaryTreeNode* FindElemInNum(BinaryTreeNode* node, int k) {
    if (node == NULL) {
        return NULL;
    }

    int leftSize = 0;
    if (node->left) {
        leftSize = node->left->size;
    }

    if (k == leftSize + 1) {
        return node;
    }
    else if (k <= leftSize) {
        return FindElemInNum(node->left, k);
    }
    else {
        return FindElemInNum(node->right, k - leftSize - 1);
    }
}

BinaryTreeNode* FindElemNumMinusK(BinaryTreeNode* node, int key, int k) {
    int currentOrder = FindNumElem(node, key);

    if (currentOrder == -1 || currentOrder <= k) {
        return NULL; 
    }
    return FindElemInNum(node, currentOrder - k);
}

bool Print(BinaryTreeNode* root) {
    bool flag = false;
    if (root != NULL) {
        Print(root->left);
        printf("%d ", root->key);
        Print(root->right);
        flag = true;
    }
    return flag;
}

void Free(BinaryTreeNode* root) {
    if (root) {
        Free(root->left);
        Free(root->right);
        free(root);
    }
}
