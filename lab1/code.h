#ifndef CODE_H
#define CODE_H

typedef struct node {
    int key;
    int priority;
    node *left;
    node *right;
} node;

void destroy_tree(node *root);

node *merge(node *a, node *b);

void split(node *n, int key, node **a, node **b);

void add(node **root, int key);

void del(node **root, int key);

int check(node** root, int key);


#endif //CODE_H
