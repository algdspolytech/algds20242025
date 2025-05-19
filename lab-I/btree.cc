#include "btree.h"
#include <stdlib.h>
#include <stdbool.h>

B_node* create_node(bool is_leaf, B_node* parent) {
    B_node* new_node = (B_node*)malloc(sizeof(B_node));
    if (!new_node) return NULL;
    
    new_node->is_leaf = is_leaf;
    new_node->keys_count = 0;
    new_node->parent = parent;
    
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        new_node->children[i] = NULL;
    }
    return new_node;
}

B_search_result search_key(B_tree* tree, int key) {
    if (!tree || !tree->root) return MISSING;

    B_node* current = tree->root;
    while (current) {
        int idx = 0;
        while (idx < current->keys_count && key > current->keys[idx]) {
            idx++;
        }
        
        if (idx < current->keys_count && key == current->keys[idx]) {
            return EXISTS;
        }
        
        if (current->is_leaf) break;
        
        current = current->children[idx];
    }
    return MISSING;
}

void split_node(B_node* parent, int child_idx) {
    B_node* full_child = parent->children[child_idx];
    B_node* new_child = create_node(full_child->is_leaf, parent);

    new_child->keys_count = MIN_CHILDREN;
    for (int i = 0; i < MIN_CHILDREN; ++i) {
        new_child->keys[i] = full_child->keys[i + T];
    }

    if (!full_child->is_leaf) {
        for (int i = 0; i < T; ++i) {
            new_child->children[i] = full_child->children[i + T];
            if (new_child->children[i]) {
                new_child->children[i]->parent = new_child;
            }
        }
    }

    full_child->keys_count = MIN_CHILDREN;
    
    for (int i = parent->keys_count; i > child_idx; --i) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[child_idx + 1] = new_child;

    for (int i = parent->keys_count - 1; i >= child_idx; --i) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[child_idx] = full_child->keys[MIN_CHILDREN];
    parent->keys_count++;
}

void insert_non_full(B_node* node, int key) {
    int pos = node->keys_count - 1;

    if (node->is_leaf) {
        while (pos >= 0 && key < node->keys[pos]) {
            node->keys[pos + 1] = node->keys[pos];
            pos--;
        }
        node->keys[pos + 1] = key;
        node->keys_count++;
    } else {
        while (pos >= 0 && key < node->keys[pos]) pos--;
        pos++;

        if (node->children[pos]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, pos);
            if (key > node->keys[pos]) pos++;
        }
        (*InsertNotFullPtr)(node->children[pos], key);
    }
}

void insert_key(B_tree* tree, int key) {
    if (search_key(tree, key) == EXISTS) return;

    B_node* root = tree->root;

    if (!root) {
        tree->root = create_node(true, NULL);
        tree->root->keys[0] = key;
        tree->root->keys_count = 1;
        return;
    }

    if (root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false, NULL);
        new_root->children[0] = root;
        root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        
        int insert_idx = (key > new_root->keys[0]) ? 1 : 0;
        (*InsertNotFullPtr)(new_root->children[insert_idx], key);
    } else {
        (*InsertNotFullPtr)(root, key);
    }
}

void free_subtree(B_node* node) {
    if (!node) return;
    
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i) {
            free_subtree(node->children[i]);
        }
    }
    free(node);
}

void free_tree(B_tree* tree) {
    if (!tree || !tree->root) return;
    free_subtree(tree->root);
    tree->root = NULL;
}

B_tree_iterator begin_iter(B_tree* tree) {
    B_tree_iterator iter = {NULL, -1};
    if (!tree || !tree->root) return iter;

    B_node* current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    iter.node = current;
    iter.position = 0;
    return iter;
}

int get_next(B_tree_iterator* iter) {
    if (!iter || !iter->node) return 0;

    if (++iter->position < iter->node->keys_count) {
        return 1;
    }

    B_node* current = iter->node;
    while (current->parent) {
        int child_idx = 0;
        while (child_idx <= current->parent->keys_count && 
               current->parent->children[child_idx] != current) {
            child_idx++;
        }

        if (child_idx < current->parent->keys_count) {
            current = current->parent->children[child_idx + 1];
            while (!current->is_leaf) {
                current = current->children[0];
            }
            iter->node = current;
            iter->position = 0;
            return 1;
        }
        current = current->parent;
    }

    iter->node = NULL;
    return 0;
}

int get_current_key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position < 0) return -1;
    return iter->node->keys[iter->position];
}
