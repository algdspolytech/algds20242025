#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int x, c;
    int priority;
    int max_c;
    struct Node* left, * right;
} Node;

Node* newNode(int x, int c) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->x = x;
    temp->c = c;
    temp->max_c = c;
    temp->priority = rand();
    temp->left = temp->right = NULL;
    return temp;
}

void updateMax(Node* node) {
    if (node == NULL)
        return;
    node->max_c = node->c;
    if (node->left != NULL && node->left->max_c > node->max_c)
        node->max_c = node->left->max_c;
    if (node->right != NULL && node->right->max_c > node->max_c)
        node->max_c = node->right->max_c;
}

void split(Node* root, int x, Node** left, Node** right) {
    if (root == NULL) {
        *left = *right = NULL;
        return;
    }
    if (root->x < x) {
        split(root->right, x, &root->right, right);
        *left = root;
    }
    else {
        split(root->left, x, left, &root->left);
        *right = root;
    }
    updateMax(root);
}

Node* merge(Node* left, Node* right) {
    if (left == NULL)
        return right;
    if (right == NULL)
        return left;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        updateMax(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        updateMax(right);
        return right;
    }
}

Node* insert(Node* root, int x, int c) {
    Node* new_node = newNode(x, c);
    Node* left, * right;
    split(root, x, &left, &right);
    return merge(merge(left, new_node), right);
}

int findMax(Node* root, int x, int y) {
    Node* left, * middle, * right;
    split(root, x, &left, &middle);
    split(middle, y, &middle, &right);
    int max_c = (middle != NULL) ? middle->max_c : -1;
    root = merge(merge(left, middle), right);
    return max_c;
}