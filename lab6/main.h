#pragma once

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;


void free_tree(RBNode *root);

RBNode* new_node(int key, Color color);


int black_height(RBNode* root);

void left_rotate(RBNode **root, RBNode *x);

void right_rotate(RBNode **root, RBNode *x);

void rb_insert_fixup(RBNode **root, RBNode *x);

RBNode* rb_join(RBNode *S1, RBNode *x, RBNode *S2);

int validate_rb_recursive(RBNode *node);

void validate_rb_tree(RBNode *root);

void inorder_traversal(RBNode *root, int *arr, int *index); 
