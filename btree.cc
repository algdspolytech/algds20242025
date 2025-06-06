#include "btree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


B_node* create_node(bool is_leaf, B_node* parent) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    node->is_leaf = is_leaf;
    node->keys_count = 0;
    node->parent = parent;
    memset(node->children, 0, sizeof(node->children));
    return node;
}

int diap(int data, int keys[], int keys_count) {
    if (data < keys[0]) {
        return 0;
    }
    for (int i = 0; i < keys_count; i++) {
        if (data > keys[i] && data < keys[i + 1])
            return i + 1;
    }
    return keys_count;
}

B_search_result Search(B_tree* tree, int data) {
    B_node* node = tree->root;
    while (node != NULL) {
        int i = 0;
        while (i < node->keys_count && data > node->keys[i]) {
            ++i;
        }
        if (i < node->keys_count && data == node->keys[i]) {
            return EXISTS;
        }
        if (node->is_leaf) {
            return MISSING;
        }
        else {
            node = node->children[i];
        }
    }
    return MISSING;
}

void insertNotFull(B_node* node, int data) {
    int i = node->keys_count - 1;

    if (node->is_leaf) {
        while (i >= 0 && data < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = data;
        node->keys_count++;
    }
    else {
        while (i >= 0 && data < node->keys[i]) {
            --i;
        }
        ++i;
        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            if (data > node->keys[i]) {
                ++i;
            }
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

void split(B_node* parent, int i) {
    B_node* left = parent->children[i];
    B_node* right = create_node(left->is_leaf, parent);
    right->keys_count = MIN_CHILDREN;
    for (int j = 0; j < MIN_CHILDREN; ++j) {
        right->keys[j] = left->keys[j + T];
    }
    if (!left->is_leaf) {
        for (int j = 0; j <= MIN_CHILDREN; ++j) {
            right->children[j] = left->children[j + T];
            if (right->children[j]) {
                right->children[j]->parent = right;
            }
        }
    }
    for (int j = parent->keys_count; j > i; --j) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = right;

    for (int j = parent->keys_count - 1; j >= i; --j) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = left->keys[MIN_CHILDREN];
    parent->keys_count++;



        left->keys_count = MIN_CHILDREN;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_node* node = tree->root;
    while (node->is_leaf == false) {
        node = node->children[0];
    }
    B_tree_iterator* res = (B_tree_iterator*)malloc(sizeof(B_tree_iterator));
    res->node = node;
    res->position = 0;
    return *res;
}

int Next(B_tree_iterator* iter) {
    if (iter->node->is_leaf) {
        if (iter->position < iter->node->keys_count - 1) {
            iter->position++;
        }
        else {
            int max = iter->node->keys[iter->position];
            B_node* back = iter->node->parent;
            while (max > back->keys[back->keys_count - 1]) {
                back = back->parent;
            }
            if (back->parent == NULL && max > back->keys[back->keys_count - 1]) {
                iter->node = NULL;
                return 0;
            }
            int i = 0;
            while (i < back->keys_count && back->keys[i] < max) {
                i++;
            }
            iter->node = back;
            iter->position = i;
        }
        return 1;
    }
    else {
        iter->node = iter->node->children[iter->position + 1];
        while (iter->node->is_leaf == false) {
            iter->node = iter->node->children[0];
        }
        iter->position = 0;
        return 1;
    }
}

int Key(B_tree_iterator* iter) {
    if (iter->node == NULL)
        return 0;
    return iter->node->keys[iter->position];
}


void Insert(B_tree* tree, int data) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;
    if (Search(tree, data) == EXISTS) {
        return;
    }
    if (!tree->root) {
        tree->root = create_node(true, NULL);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }
    B_node* root = tree->root;
    if (root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false, NULL);
        new_root->children[0] = root;
        root->parent = new_root;
        tree->root = new_root;
        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, data);
    }
    else {
        (*InsertNotFullPtr)(root, data);
    }
}

void freenode(B_node* node) {
    if (node->is_leaf) {
        free(node);
        return;
    }
    else {
        for (int i = 0; i <= node->keys_count; i++) {
            freenode(node->children[i]);
        }
        free(node);
    }
}

void Free(B_tree* tree) {
    freenode(tree->root);
    free(tree);
}