#ifndef TREE_H
#define TREE_H
#include<stdio.h>

typedef enum color {
    BLACK = 0,
    RED = 1
} color_t;

typedef enum  direction {
    LEFT = 0,
    RIGHT = 1
} direction_t;

typedef struct Node {
    struct Node* parent;

    color_t color;
    struct Node* left;
    struct Node* right;

    int data;
} node_t;

typedef struct Tree {
    struct Node* root;
    struct Node* nil;
} tree_t;

tree_t* tree_create();
node_t* create_node(int data, color_t color, node_t *nil);

node_t* findLUB(int upper_bound, tree_t* tree);

direction_t get_direction(node_t* node);

void dispose_tree(tree_t* tree);

void rotate(tree_t* tree, node_t* node);
void insert(tree_t* tree, node_t* node);
void fix_violations(tree_t *tree, node_t *new_node);
void rb_remove(tree_t* tree, node_t* node);

#endif //TREE_H
