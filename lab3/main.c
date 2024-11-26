#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode* createNode(const char* word) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    node->word = (char*)malloc(strlen(word) + 1);
    if (node->word == NULL) {
        fprintf(stderr, "Memory allocation error for word\n");
        free(node);
        exit(EXIT_FAILURE);
    }
    strcpy(node->word, word);

    node->subtree_width = 0;
    node->left = node->right = NULL;
    return node;
}

void freeTree(TreeNode* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root->word);
    free(root);
}

TreeNode* insert(TreeNode* root, const char* word) {
    if (root == NULL) {
        return createNode(word);
    }
    if (strcmp(word, root->word) < 0) {
        root->left = insert(root->left, word);
    }
    else {
        root->right = insert(root->right, word);
    }
    return root;
}

int computeSubtreeWidth(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int left_width = computeSubtreeWidth(root->left);
    int right_width = computeSubtreeWidth(root->right);
    int node_width = strlen(root->word);
    root->subtree_width = left_width + right_width + node_width;
    return root->subtree_width;
}

void printTree(TreeNode* root) {
    if (root == NULL)
        return;
    printTree(root->left);

    printf("%s\n", root->word);

    int word_length = strlen(root->word);
    int width_digits = snprintf(NULL, 0, "%d", root->subtree_width);
    int padding = (word_length - width_digits) / 2;
    if (padding > 0) {
        printf("%*s", padding, "");
    }
    printf("%d\n", root->subtree_width);

    printTree(root->right);
}

int main() {
    TreeNode* root = NULL;

    root = insert(root, "tree");
    root = insert(root, "binary");
    root = insert(root, "node");
    root = insert(root, "subtree");
    root = insert(root, "word");
    root = insert(root, "width");

    computeSubtreeWidth(root);

    printf("Tree with subtree widths:\n\n");
    printTree(root);

    freeTree(root);

    return 0;
}