#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

B_node* create_node(bool is_leaf, B_node* parent) {
    B_node* node = (B_node*)calloc(1, sizeof(B_node));
    if (node) {
        node->is_leaf = is_leaf;
        node->parent = parent;
    }
    return node;
}

B_search_result Search(B_tree* tree, int data) {
    if (!tree || !tree->root) return MISSING;

    B_node* node = tree->root;
    while (node) {
        int idx = 0;
        while (idx < node->keys_count && data > node->keys[idx]) {
            idx++;
        }

        if (idx < node->keys_count && data == node->keys[idx]) {
            return EXISTS;
        }

        node = node->is_leaf ? NULL : node->children[idx];
    }
    return MISSING;
}

void insertNotFull(B_node* node, int data) {
    int idx = node->keys_count - 1;

    if (node->is_leaf) {
        while (idx >= 0 && node->keys[idx] > data) {
            node->keys[idx + 1] = node->keys[idx];
            idx--;
        }
        node->keys[idx + 1] = data;
        node->keys_count++;
    }
    else {
        while (idx >= 0 && data < node->keys[idx]) {
            idx--;
        }
        idx++;

        if (node->children[idx]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, idx);
            if (data > node->keys[idx]) {
                idx++;
            }
        }

        (*InsertNotFullPtr)(node->children[idx], data);
    }
}

void split(B_node* parent, int index) {
    B_node* full = parent->children[index];
    B_node* right = create_node(full->is_leaf, parent);

    right->keys_count = MIN_CHILDREN;
    for (int i = 0; i < MIN_CHILDREN; ++i) {
        right->keys[i] = full->keys[i + T];
    }

    if (!full->is_leaf) {
        for (int i = 0; i <= MIN_CHILDREN; ++i) {
            right->children[i] = full->children[i + T];
            if (right->children[i]) {
                right->children[i]->parent = right;
            }
        }
    }

    for (int j = parent->keys_count; j > index; --j) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[index + 1] = right;

    for (int j = parent->keys_count - 1; j >= index; --j) {
        parent->keys[j + 1] = parent->keys[j];
    }

    parent->keys[index] = full->keys[MIN_CHILDREN];
    parent->keys_count++;

    full->keys_count = MIN_CHILDREN;
}

void Insert(B_tree* tree, int data) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)&insertNotFull;

    if (!tree) return;
    if (Search(tree, data) == EXISTS) return;

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

void free_node(B_node* node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i) {
            free_node(node->children[i]);
        }
    }
    free(node);
}

void Free(B_tree* tree) {
    if (tree && tree->root) {
        free_node(tree->root);
        tree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { NULL, -1 };
    if (!tree || !tree->root) return iter;

    B_node* current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    iter.node = current;
    return iter;
}

int Next(B_tree_iterator* iter) {
    if (!iter || !iter->node) return 0;

    B_node* node = iter->node;
    int pos = iter->position;

    if (node->is_leaf) {
        if (++pos < node->keys_count) {
            iter->position = pos;
            return 1;
        }
    }
    else {
        if (++pos <= node->keys_count && node->children[pos]) {
            B_node* current = node->children[pos];
            while (!current->is_leaf) {
                current = current->children[0];
            }
            iter->node = current;
            iter->position = 0;
            return 1;
        }
    }

    B_node* current = node;
    while (current->parent) {
        B_node* parent = current->parent;
        int idx = 0;
        while (idx <= parent->keys_count && parent->children[idx] != current) {
            ++idx;
        }
        if (idx < parent->keys_count) {
            iter->node = parent;
            iter->position = idx;
            return 1;
        }
        current = parent;
    }

    iter->node = NULL;
    return 0;
}

int Key(B_tree_iterator* iter) {
    return iter->node->keys[iter->position];
}