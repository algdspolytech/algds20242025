#ifndef TREAP_H
#define TREAP_H

typedef struct Node {
    int key;
    int priority;
    int c;
    int sum;
    int min_key;
    int max_key;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int key, int c);
Node* insert(Node* root, Node* new_node);
int get_sum(Node* root, int x, int y);
void free_tree(Node* root);

#endif