#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node* insert(Node* root, int key);
Node* delete(Node* root, int key);
Node* search(Node* root, int key, int* found);
void free_tree(Node* root);

#endif // SPLAY_TREE_H