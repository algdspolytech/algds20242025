#include <stdlib.h>
#include "treap.h"

void update_sum(TreapNode* node) {
    if (!node) return;
    node->sum = node->c;
    if (node->left) node->sum += node->left->sum;
    if (node->right) node->sum += node->right->sum;
}

void split(TreapNode* root, int key, TreapNode** left, TreapNode** right) {
    if (!root) {
        *left = NULL;
        *right = NULL;
        return;
    }

    if (root->x <= key) {
        TreapNode* r = NULL;
        split(root->right, key, &r, right);
        root->right = r;
        *left = root;
    } else {
        TreapNode* l = NULL;
        split(root->left, key, left, &l);
        root->left = l;
        *right = root;
    }
    update_sum(root);
}

TreapNode* merge(TreapNode* a, TreapNode* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->priority > b->priority) {
        a->right = merge(a->right, b);
        update_sum(a);
        return a;
    } else {
        b->left = merge(a, b->left);
        update_sum(b);
        return b;
    }
}

static TreapNode* create_node(int x, int c, int priority) {
    TreapNode* node = (TreapNode*)malloc(sizeof(TreapNode));
    node->x = x;
    node->c = c;
    node->priority = priority;
    node->sum = c;
    node->left = node->right = NULL;
    return node;
}

static TreapNode* insert_node(TreapNode* root, TreapNode* newNode) {
    if (!root) return newNode;

    if (newNode->priority > root->priority) {
        split(root, newNode->x, &newNode->left, &newNode->right);
        update_sum(newNode);
        return newNode;
    }

    if (newNode->x <= root->x)
        root->left = insert_node(root->left, newNode);
    else
        root->right = insert_node(root->right, newNode);

    update_sum(root);
    return root;
}

void insert(TreapNode** root, int x, int c) {
    int priority = rand();
    TreapNode* newNode = create_node(x, c, priority);
    *root = insert_node(*root, newNode);
}

int sum_range(TreapNode** root, int x_start, int x_end) {
    TreapNode* left1, * right1;
    split(*root, x_start - 1, &left1, &right1);

    TreapNode* left2, * right2;
    split(right1, x_end - 1, &left2, &right2);

    int sum = left2 ? left2->sum : 0;

    TreapNode* temp = merge(left2, right2);
    *root = merge(left1, temp);

    return sum;
}

void free_treap(TreapNode* root) {
    if (!root) return;
    free_treap(root->left);
    free_treap(root->right);
    free(root);
}