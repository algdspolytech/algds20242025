#include <stdlib.h>
#include "btree.h"

#include <string.h>
#include <stdbool.h>

static B_node* init_node(bool is_leaf, B_node* parent_node) {
    B_node* new_node = (B_node*)malloc(sizeof(B_node));
    new_node->is_leaf = is_leaf;
    new_node->keys_count = 0;
    new_node->parent = parent_node;
    memset(new_node->children, 0, sizeof(new_node->children));
    return new_node;
}

B_search_result Search(B_tree* tree, int key) {
    B_node* current = tree->root;

    while (current) {
        int idx = 0;
        while (idx < current->keys_count && key > current->keys[idx]) {
            idx++;
        }

        if (idx < current->keys_count && key == current->keys[idx]) return EXISTS;
        if (current->is_leaf) return MISSING;
        current = current->children[idx];
    }

    return MISSING;
}

// Insert a key into a non-full node
void insertNotFull(B_node* node, int key) {
    int idx = node->keys_count - 1;

    if (node->is_leaf) {
        while (idx >= 0 && key < node->keys[idx]) {
            node->keys[idx + 1] = node->keys[idx];
            idx--;
        }
        node->keys[idx + 1] = key;
        node->keys_count++;
    }
    else {
        while (idx >= 0 && key < node->keys[idx]) idx--;
        idx++;

        if (node->children[idx]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, idx);
            if (key > node->keys[idx]) {
                idx++;
            }
        }
        (*InsertNotFullPtr)(node->children[idx], key);
    }
}

void split(B_node* parent_node, int split_index) {
    B_node* child_to_split = parent_node->children[split_index];
    B_node* new_sibling = init_node(child_to_split->is_leaf, parent_node);

    new_sibling->keys_count = MIN_CHILDREN;

    for (int j = 0; j < MIN_CHILDREN; j++) {
        new_sibling->keys[j] = child_to_split->keys[j + T];
    }

    if (!child_to_split->is_leaf) {
        for (int j = 0; j <= MIN_CHILDREN; j++) {
            new_sibling->children[j] = child_to_split->children[j + T];
            if (new_sibling->children[j]) {
                new_sibling->children[j]->parent = new_sibling;
            }
        }
    }

    for (int j = parent_node->keys_count; j > split_index; j--) {
        parent_node->children[j + 1] = parent_node->children[j];
    }
    parent_node->children[split_index + 1] = new_sibling;

    for (int j = parent_node->keys_count - 1; j >= split_index; j--) {
        parent_node->keys[j + 1] = parent_node->keys[j];
    }
    parent_node->keys[split_index] = child_to_split->keys[MIN_CHILDREN];
    parent_node->keys_count++;

    child_to_split->keys_count = MIN_CHILDREN;
}

void Insert(B_tree* tree, int key) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    if (Search(tree, key) == EXISTS) return;


    if (!tree->root) {
        tree->root = init_node(true, NULL);
        tree->root->keys[0] = key;
        tree->root->keys_count = 1;
        return;
    }

    B_node* current_root = tree->root;

    if (current_root->keys_count == MAX_KEYS) {
        B_node* new_root_node = init_node(false, NULL);
        new_root_node->children[0] = current_root;
        current_root->parent = new_root_node;
        tree->root = new_root_node;

        (*SplitFPtr)(new_root_node, 0);
        (*InsertNotFullPtr)(new_root_node, key);
    }
    else  (*InsertNotFullPtr)(current_root, key);
   
}

    ///
void free_node(B_node* node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int idx = 0; idx <= node->keys_count; idx++) {
            free_node(node->children[idx]);
        }
    }
    free(node);
}

            /// Free the entire B-tree
void Free(B_tree* tree) {
    if (tree && tree->root) {
        free_node(tree->root);
        tree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iterator = { 0 };

    if (!tree->root) {
        iterator.node = NULL;
        iterator.position = -1;
        return iterator;
    }

    B_node* current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    iterator.node = current;
    iterator.position = -1;
    return iterator;
}

int Next(B_tree_iterator* iterator) {
    if (!iterator->node) {
        return 0;
    }

    B_node* current_node = iterator->node;
    int current_pos = iterator->position;

    if (current_node->is_leaf) {
        if (current_pos + 1 < current_node->keys_count) {
            iterator->position = current_pos + 1;
            return 1;
        }
    }
    else {
        if (current_pos + 1 <= current_node->keys_count && current_node->children[current_pos + 1]) {
            B_node* next_node = current_node->children[current_pos + 1];
            while (!next_node->is_leaf) {
                next_node = next_node->children[0];
            }
            iterator->node = next_node;
            iterator->position = 0;
            return 1;
        }
    }

    B_node* node = current_node;
    while (node->parent) {
        B_node* parent = node->parent;

        int idx = 0;
        while (idx <= parent->keys_count && parent->children[idx] != node) {
            idx++;
        }

        if (idx < parent->keys_count) {
            iterator->node = parent;
            iterator->position = idx;
            return 1;
        }

        node = parent;
    }

    iterator->node = NULL;
    return 0;
}

/// Retrieve the current key from the iterator
int Key(B_tree_iterator* iterator) {
    return iterator->node->keys[iterator->position];
}