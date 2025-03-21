#include "functions.h"

//int max(int a, int b) {
//    return (a > b) ? a : b;
//}

int height(AVLNode* node) {
    if (node != NULL) {
        return node->height;
    } 
}

void update_height(AVLNode* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

int balance_factor(AVLNode* node) {
    return height(node->left) - height(node->right);
}

AVLNode* new_node(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    return x;
}

AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    return y;
}

AVLNode* avl_insert(AVLNode* node, int key) {
    if (node == NULL) return new_node(key);

    if (key < node->key)
        node->left = avl_insert(node->left, key);
    else if (key > node->key)
        node->right = avl_insert(node->right, key);
    else
        return node;

    update_height(node);

    int balance = balance_factor(node);

    if (balance > 1 && key < node->left->key)
        return right_rotate(node);

    if (balance < -1 && key > node->right->key)
        return left_rotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

AVLNode* min_value_node(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

AVLNode* avl_delete(AVLNode* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = avl_delete(root->left, key);
    else if (key > root->key)
        root->right = avl_delete(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            AVLNode* temp = min_value_node(root->right);
            root->key = temp->key;
            root->right = avl_delete(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    update_height(root);

    int balance = balance_factor(root);

    if (balance > 1 && balance_factor(root->left) >= 0)
        return right_rotate(root);

    if (balance > 1 && balance_factor(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && balance_factor(root->right) <= 0)
        return left_rotate(root);

    if (balance < -1 && balance_factor(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

AVLNode* avl_search(AVLNode* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    return (key < root->key) ? avl_search(root->left, key) : avl_search(root->right, key);
}

void free_avl_tree(AVLNode* root) {
    if (root == NULL) return;
    free_avl_tree(root->left);
    free_avl_tree(root->right);
    free(root);
}