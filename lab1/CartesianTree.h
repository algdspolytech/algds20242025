#ifndef MAIN_H
#define MAIN_H

typedef struct node {
    int key;
    int priority;
    node *left;
    node *right;
} node;

void destroy_tree(node *root);

node *create_node(int key);

node *merge(node *a, node *b);

void split(node *n, int key, node **a, node **b);

void insert(node **root, int key);

int contains(node **root, int key);

void erase(node **root, int key);


#endif //MAIN_H
