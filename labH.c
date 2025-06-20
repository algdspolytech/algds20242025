#include <stdlib.h>
#include "labH.h"

typedef struct Node {
    int x, c, priority;
    int sum;
    struct Node* left, * right;
} Node;

static int get_sum(Node* n) {
    return n ? n->sum : 0;
}

static void update(Node* n) {
    if (n) {
        n->sum = n->c + get_sum(n->left) + get_sum(n->right);
    }
}

static Node* create_node(int x, int c) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->x = x;
    n->c = c;
    n->priority = rand();
    n->left = n->right = NULL;
    update(n);
    return n;
}

static void split(Node* root, int key, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
    }
    else if (key <= root->x) {
        split(root->left, key, left, &root->left);
        *right = root;
        update(root);
    }
    else {
        split(root->right, key, &root->right, right);
        *left = root;
        update(root);
    }
}

static Node* merge(Node* left, Node* right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

Node* insert(Node* root, int x, int c) {
    Node* n = create_node(x, c);
    Node* l, * r;
    split(root, x, &l, &r);
    return merge(merge(l, n), r);
}

int range_sum(Node* root, int x, int y) {
    Node* l, * mid, * r;
    split(root, x, &l, &mid);
    split(mid, y, &mid, &r);
    int res = get_sum(mid);
    root = merge(l, merge(mid, r)); // Restore original tree
    return res;
}

void free_tree(Node* root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
