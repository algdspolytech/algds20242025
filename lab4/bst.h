#ifndef BST_H
#define BST_H

struct Node {
    int value;         
    struct Node* left; 
    struct Node* right; 
    int count;         
};

struct Node* create_node(int value);
struct Node* add_to_tree(struct Node* root, int value);
void clear_tree(struct Node** root);
int find_kth_smallest(struct Node* root, int k);
void print_if_kth_even(struct Node* root, int k);
int get_tree_size(struct Node* root);
#endif
