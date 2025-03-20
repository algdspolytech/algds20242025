#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int priority;
    struct node *left;
    struct node *right;
} node;


void destroy_tree(node *root) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        destroy_tree(root->left);
    }
    if (root->right != NULL) {
        destroy_tree(root->right);
    }
    free(root);
}

node *create_node(int key) {
    int priority = rand();
    node *temp = (node *) malloc(sizeof(node));
    if (temp == NULL) {
        printf("\n couldn't allocate memory create_node, key = %d, priority = %d", key, priority);
        assert(0);
    }
    temp->key = key;
    temp->priority = priority;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node *merge(node *a, node *b) {
    if (a == NULL) return b;

    if (b == NULL) return a;

    if (a->priority > b->priority) {
        a->right = merge(a->right, b);
        return a;
    }
    b->left = merge(a, b->left);
    return b;
}

void split(node *n, int key, node **a, node **b) {
    if (n == NULL) {
        if (a) *a = NULL;
        if (b) *b = NULL;
        return;
    }

    if (n->key < key) {
        split(n->right, key, &n->right, b);
        *a = n;
    } else {
        split(n->left, key, a, &n->left);
        *b = n;
    }
}

void insert(node **root, int key) {
    node *less;
    node *great;
    split(*root, key, &less, &great);
    *root = merge(merge(less, create_node(key)), great);
}

int contains(node **root, int key) {
    node *less;
    node *equal;
    node *great;

    split(*root, key, &less, &great);
    split(great, key + 1, &equal, &great);
    int result = 0;
    if (equal) result = 1;

    *root = merge(merge(less, equal), great);

    return result;
}

void erase(node **root, int key) {
    node *less;
    node *equal;
    node *great;
    split(*root, key, &less, &great);
    split(great, key + 1, &equal, &great);
    *root = merge(less, great);
    destroy_tree(equal);
}

void print_inorder(node *root) {
    if (root == NULL) return;
    print_inorder(root->left);
    printf("Key: %d, Priority: %d\n", root->key, root->priority);
    print_inorder(root->right);
}
