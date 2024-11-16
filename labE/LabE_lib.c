#include <stdio.h>
#include <stdlib.h>
#include "LabE_lib.h"

TreeNode* create_node(int value) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

TreeNode* add_node(TreeNode* root, int value) {
    if (root == NULL) {
        return create_node(value);
    }

    if (value < root->value) {
        root->left = add_node(root->left, value);
    }
    else {
        root->right = add_node(root->right, value);
    }

    return root;
}

TreeNode* initialize_tree(int* elements, int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = add_node(root, elements[i]);
    }
    return root;
}

void print_tree(TreeNode* root, int depth) {
    if (root == NULL) {
        return;
    }

    print_tree(root->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%d\n", root->value);

    print_tree(root->left, depth + 1);
}

void print_compact_tree(TreeNode* root) {
    if (root == NULL) {
        printf("NULL");
        return;
    }

    printf("%d (", root->value);
    print_compact_tree(root->left); 
    printf(") (");
    print_compact_tree(root->right); 
    printf(")");
}

void free_tree(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
