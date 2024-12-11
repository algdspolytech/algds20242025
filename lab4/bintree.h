#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int min_leaf_height;
    double value;
    struct Node *left;
    struct Node *right; 
} Node;

typedef struct {
    Node *root;
    int count_of_nodes;
} Bin_Tree;

Bin_Tree *init_tree(double value);
Node *init_node(double value);
int calculate_min_leaf_height(Node *leaf);
void updatee_heigths(Node *root);
void add_new_node(Node *root, double value);
void print_tree(Node *root, int offset);
void free_tree(Node *root);