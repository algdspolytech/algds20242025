#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subtree.h"


// new node creation
TreeNode* create_node(const char* word) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->word = _strdup(word); // copy word
    node->left = NULL;
    node->right = NULL;
    node->subtree_width = 0; 
    return node;
}

// recursive subtree width computation
int compute_subtree_width(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    // compute width of left and right
    int left_width = compute_subtree_width(node->left);
    int right_width = compute_subtree_width(node->right);

    // final sum
    node->subtree_width = left_width + right_width + (int)strlen(node->word);
    return node->subtree_width;
}

// recursive print
void print_tree(TreeNode* root, int depth) {
    if (root == NULL) {
        return;
    }
    // print right tree
    print_tree(root->right, depth + 1);

    // print word with margin
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%s\n", root->word);

    // width of word under the word
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%d\n", root->subtree_width);

    // print left tree
    print_tree(root->left, depth + 1);
}

// free memory
void free_tree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root->word);
    free(root);
}

