#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct Node* create_node(int value) {
    struct Node* node = malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Ошибка: нет памяти\n");
        return NULL;
    }
    node->value = value;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int get_tree_size(struct Node* root) {
    if (root == NULL) return 0;
    return root->count;
}

struct Node* add_to_tree(struct Node* root, int value) {
    if (root == NULL) {
        return create_node(value);
    }
    
    if (value < root->value) {
        root->left = add_to_tree(root->left, value);
    } else {
        root->right = add_to_tree(root->right, value);
    }
    
    root->count = 1 + get_tree_size(root->left) + get_tree_size(root->right);
    return root;
}

void clear_tree(struct Node** root) {
    if (*root == NULL) return;
    
    clear_tree(&(*root)->left);
    clear_tree(&(*root)->right);
    
    free(*root);
    *root = NULL;
}

static int find_kth_helper(struct Node* root, int k, int* count) {
    if (root == NULL) return -1;
    
    int left = find_kth_helper(root->left, k, count);
    if (left != -1) return left;
    
    (*count)++;
    if (*count == k) return root->value;
    
    return find_kth_helper(root->right, k, count);
}

int find_kth_smallest(struct Node* root, int k) {
    int count = 0;
    return find_kth_helper(root, k, &count);
}

static void print_helper(struct Node* root, int k, int* count) {
    if (root == NULL) return;
    
    print_helper(root->left, k, count);
    
    if (*count < k - 1) {
        printf("%d ", root->value);
    }
    (*count)++;
    
    print_helper(root->right, k, count);
}

void print_if_kth_even(struct Node* root, int k) {
    int kth = find_kth_smallest(root, k);
    
    if (kth != -1 && kth % 2 == 0) {
        int count = 0;
        print_helper(root, k, &count);
        printf("\n");
    }
}
