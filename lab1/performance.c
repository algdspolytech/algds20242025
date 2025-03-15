#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rb_tree.h"

typedef struct BSTNode {
    int key;
    struct BSTNode* left, * right;
} BSTNode;

BSTNode* bst_insert(BSTNode* root, int key) {
    if (!root) {
        BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
        node->key = key;
        node->left = node->right = NULL;
        return node;
    }
    if (key < root->key)
        root->left = bst_insert(root->left, key);
    else
        root->right = bst_insert(root->right, key);
    return root;
}

void measure_performance() {
    const int N = 100000;
    int* data = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) data[i] = rand();

    // RB Tree
    clock_t start = clock();
    Node* rb_root = NIL;
    for (int i = 0; i < N; i++) insert(&rb_root, data[i]);
    printf("RB Insert: %.2f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    free_tree(rb_root);

    // BST
    start = clock();
    BSTNode* bst_root = NULL;
    for (int i = 0; i < N; i++) bst_root = bst_insert(bst_root, data[i]);
    printf("BST Insert: %.2f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    free(data);
}

int main() {
    measure_performance();
    return 0;
}