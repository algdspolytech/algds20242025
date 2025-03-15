#ifndef RB_TREE_H
#define RB_TREE_H

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

extern Node* NIL;

void insert(Node** root, int key);
void delete(Node** root, int key);
Node* search(Node* root, int key);
void free_tree(Node* root);

#endif // RB_TREE_H