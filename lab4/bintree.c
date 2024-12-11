#include "bintree.h"

int main() {
    Bin_Tree *tree = init_tree(11);
    add_new_node(tree->root,6);
    add_new_node(tree->root,3);
    add_new_node(tree->root,1);
    add_new_node(tree->root,2);
    add_new_node(tree->root,8);
    add_new_node(tree->root,7);
    add_new_node(tree->root,12);
    print_tree(tree->root,0);
    free_tree(tree->root);
    return 0;
}

Node *init_node(double value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->min_leaf_height = 0;
    return new_node;
}

Bin_Tree *init_tree(double value) {
    Bin_Tree *new_tree = malloc(sizeof(Bin_Tree));
    new_tree->root = init_node(value);
    new_tree->count_of_nodes = 1;
    return new_tree;
}

int calculate_min_leaf_height(Node *leaf) {
    bool flag = true;
    int res = 10000000;
    if(!leaf->left && !leaf->right) {
        res = 0;
        flag = false;
    }
    if(flag) {
        int res_1, res_2;
        if(leaf->left) {
            res_1 = calculate_min_leaf_height(leaf->left);
        } else {
            res_1 = 1000000;
        }
        if(leaf->right) {
            res_2 = calculate_min_leaf_height(leaf->right);
        } else {
            res_2  = 1000000;
        }
        res = res_1 > res_2 ? res_2 + 1 : res_1 + 1;
    }
    return res;
}

void updatee_heigths(Node *root) {
    bool flag = true;
    if(!root->left && !root->right) {
        root->min_leaf_height = 0;
        flag = false;
    } 
    if(flag) {
        if(root->left) updatee_heigths(root->left);
        if(root->right) updatee_heigths(root->right);
        root->min_leaf_height = calculate_min_leaf_height(root);
    }
}

void add_new_node(Node *root, double value) {
    if(value > root->value) {
        if(root->right) {
            add_new_node(root->right, value);
        } else {
            root->right = init_node(value);
        }
    } else {
        if(root->left) {
            add_new_node(root->left, value);
        } else {
            root->left = init_node(value);
        }
    }
    updatee_heigths(root);
}

void free_tree(Node *root) {
    bool flag = true;
    if(!root->left && !root->right) {
        free(root);
        flag = false;
    }
    if(flag) {
        if(root->left) {
            free_tree(root->left);
            root->left = NULL;
        }
        if(root->right) {
            free_tree(root->right);
            root->right = NULL;
        }
        free(root);
    }
}

void print_tree(Node *root, int offest) {
    for(int i = 0; i < offest; i++) 
        printf("\t\t");
    printf("(value = %.1lf; min height = %d)\n",root->value,root->min_leaf_height);
    if(root->left) {
        print_tree(root->left,offest+1);
    }
    if(root->right) {
        print_tree(root->right,offest+1);
    }
}


