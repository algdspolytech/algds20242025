#include "funcs.h"

Node* make_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Failed to allocate memory for node\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = value;
    new_node->priority = rand();
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    return new_node;
}

Node* combine_trees(Node* tree1, Node* tree2) {
    if (!tree1)
        return tree2;
    if (!tree2)
        return tree1;

    if (tree1->priority > tree2->priority) {
        tree1->right_child = combine_trees(tree1->right_child, tree2);
        return tree1;
    }
    else {
        tree2->left_child = combine_trees(tree1, tree2->left_child);
        return tree2;
    }
}

void divide_tree(Node* root, int value, Node** left_tree, Node** right_tree) {
    if (!root) {
        *left_tree = NULL;
        *right_tree = NULL;
        return;
    }

    if (value >= root->value) {
        divide_tree(root->right_child, value, &root->right_child, right_tree);
        *left_tree = root;
    }
    else {
        divide_tree(root->left_child, value, left_tree, &root->left_child);
        *right_tree = root;
    }
}

Node* add_value(Node* root, int value) {
    if (!root)
        return make_node(value);

    if (value <= root->value) {
        root->left_child = add_value(root->left_child, value);

        if (root->left_child->priority > root->priority) {
            Node* new_root = root->left_child;
            root->left_child = new_root->right_child;
            new_root->right_child = root;
            root = new_root;
        }
    }
    else {
        root->right_child = add_value(root->right_child, value);

        if (root->right_child->priority > root->priority) {
            Node* new_root = root->right_child;
            root->right_child = new_root->left_child;
            new_root->left_child = root;
            root = new_root;
        }
    }

    return root;
}

Node* remove_value(Node* root, int value) {
    if (!root)
        return NULL;

    if (value < root->value)
        root->left_child = remove_value(root->left_child, value);
    else if (value > root->value)
        root->right_child = remove_value(root->right_child, value);
    else {
        if (!root->left_child && !root->right_child) {
            free(root);
            return NULL;
        }
        else if (!root->left_child) {
            Node* temp = root->right_child;
            free(root);
            return temp;
        }
        else if (!root->right_child) {
            Node* temp = root->left_child;
            free(root);
            return temp;
        }
        else {
            if (root->left_child->priority > root->right_child->priority) {
                Node* new_root = root->left_child;
                root->left_child = new_root->right_child;
                new_root->right_child = root;
                root = new_root;
                root->right_child = remove_value(root->right_child, value);
            }
            else {
                Node* new_root = root->right_child;
                root->right_child = new_root->left_child;
                new_root->left_child = root;
                root = new_root;
                root->left_child = remove_value(root->left_child, value);
            }
        }
    }

    return root;
}

void release_tree(Node* root) {
    if (!root)
        return;

    release_tree(root->left_child);
    release_tree(root->right_child);
    free(root);
}