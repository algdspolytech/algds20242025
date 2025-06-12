#include "tree.h"
int min_t(int a, int b) {
    return (a < b) ? a : b;
}
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->min_leaf_height = -1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
int calculateAndSetMinLeafHeight(Node* node) {
    if (node == NULL) {
        return INT_MAX;
    }
    if (node->left == NULL && node->right == NULL) {
        node->min_leaf_height = 0;
        return 0;
    }
    int left_min_height = calculateAndSetMinLeafHeight(node->left);
    int right_min_height = calculateAndSetMinLeafHeight(node->right);
    int min_child_height = min(left_min_height, right_min_height);
    if (min_child_height == INT_MAX) {
    }

    node->min_leaf_height = 1 + min_child_height;

    return node->min_leaf_height;
}
void printTreePreOrder(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("uzel(%d) [MinLeafHeight: %d]\n", node->data, node->min_leaf_height);
    printTreePreOrder(node->left);
    printTreePreOrder(node->right);
}
void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}