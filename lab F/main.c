#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

Node* create_node(int value, Node* parent) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->subtree_size = 1;
    new_node->parent = parent;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void update_subtree_size(Node* node) {
    while (node) {
        int left_size = node->left ? node->left->subtree_size : 0;
        int right_size = node->right ? node->right->subtree_size : 0;
        node->subtree_size = 1 + left_size + right_size;
        node = node->parent;
    }
}

void add_node(Node** root, int value) {
    if (*root == NULL) {
        *root = create_node(value, NULL);
        return;
    }

    Node* current = *root;
    while (1) {
        int left_size = current->left ? current->left->subtree_size : 0;
        int right_size = current->right ? current->right->subtree_size : 0;

        if (left_size <= right_size) {
            if (current->left == NULL) {
                current->left = create_node(value, current);
                break;
            }
            else {
                current = current->left;
            }
        }
        else {
            if (current->right == NULL) {
                current->right = create_node(value, current);
                break;
            }
            else {
                current = current->right;
            }
        }
    }

    update_subtree_size(current);
}

Node* find_minimum(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

void delete_node(Node** root, int value) {
    Node* current = *root;
    Node* parent = NULL;

    while (current && current->value != value) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (!current) {
        return;
    }

    if (current->left && current->right) {
        Node* successor = find_minimum(current->right);
        int successor_value = successor->value;
        delete_node(&(current->right), successor_value);
        current->value = successor_value;
        update_subtree_size(current);
        return;
    }

    Node* child = current->left ? current->left : current->right;
    if (parent == NULL) {
        *root = child;
    }
    else if (parent->left == current) {
        parent->left = child;
    }
    else {
        parent->right = child;
    }

    if (child) {
        child->parent = parent;
    }

    update_subtree_size(parent);
    free(current);
}


void inorder_traversal(Node* node) {
    if (!node) return;
    inorder_traversal(node->left);
    inorder_traversal(node->right);
}

void free_tree(Node* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    TESTS();
    return 0;
}
