#include "binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

TreeNode* create_node(int value, TreeNode* parent) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) return NULL;
    node->value = value;
    node->left = node->right = NULL;
    node->parent = parent;
    node->node_count = 1;
    return node;
}

TreeNode* add_node(TreeNode** root, int value) {
    if (!root) return NULL;

    if (*root == NULL) {
        *root = create_node(value, NULL);
        return *root;
    }

    TreeNode* current = *root;
    TreeNode* parent = NULL;

    while (1) {
        current->node_count++;
        parent = current;

        if (!current->left || (current->left->node_count <= current->right->node_count)) {
            if (!current->left) {
                current->left = create_node(value, current);
                return current->left;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right = create_node(value, current);
                return current->right;
            }
            current = current->right;
        }
    }
}

TreeNode* find_min(TreeNode* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

void remove_node(TreeNode** root, int value) {
    if (!root || !(*root)) return;

    TreeNode* current = *root;
    TreeNode* parent = NULL;

    while (current && current->value != value) {
        parent = current;
        current->node_count--;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (!current) return; // Узел не найден

    // Узел без потомков
    if (!current->left && !current->right) {
        if (current == *root) {
            *root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
    // Узел с двумя потомками
    else if (current->left && current->right) {
        TreeNode* successor = find_min(current->right);
        int successor_value = successor->value;
        remove_node(root, successor->value);
        current->value = successor_value;
    }
    // Узел с одним потомком
    else {
        TreeNode* child = current->left ? current->left : current->right;
        if (current == *root) {
            *root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        child->parent = parent;
        free(current);
    }
}
