#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

static B_node* create_node(bool is_leaf_flag, B_node* parent_node) {
    B_node* new_node = (B_node*)malloc(sizeof(B_node));
    new_node->is_leaf = is_leaf_flag;
    new_node->keys_count = 0;
    new_node->parent = parent_node;
    memset(new_node->children, 0, sizeof(new_node->children));
    return new_node;
}

B_search_result Search(B_tree* tree, int key_value) {
    B_node* current = tree->root;

    while (current != NULL) {
        int idx = 0;
        while (idx < current->keys_count && key_value > current->keys[idx]) {
            ++idx;
        }

        if (idx < current->keys_count && key_value == current->keys[idx]) {
            return EXISTS;
        }

        if (current->is_leaf) {
            return MISSING;
        }
        else {
            current = current->children[idx];
        }
    }

    return MISSING;
}

void insertNotFull(B_node* current_node, int new_key) {
    int pos = current_node->keys_count - 1;

    if (current_node->is_leaf) {
        while (pos >= 0 && new_key < current_node->keys[pos]) {
            current_node->keys[pos + 1] = current_node->keys[pos];
            --pos;
        }
        current_node->keys[pos + 1] = new_key;
        current_node->keys_count++;
    }
    else {
        while (pos >= 0 && new_key < current_node->keys[pos]) {
            --pos;
        }
        ++pos;

        if (current_node->children[pos]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(current_node, pos);
            if (new_key > current_node->keys[pos]) {
                ++pos;
            }
        }
        (*InsertNotFullPtr)(current_node->children[pos], new_key);
    }
}

void split(B_node* parent_node, int child_idx) {
    B_node* child_node = parent_node->children[child_idx];
    B_node* new_node = create_node(child_node->is_leaf, parent_node);

    new_node->keys_count = MIN_CHILDREN;

    for (int k = 0; k < MIN_CHILDREN; ++k) {
        new_node->keys[k] = child_node->keys[k + T];
    }

    if (!child_node->is_leaf) {
        for (int k = 0; k <= MIN_CHILDREN; ++k) {
            new_node->children[k] = child_node->children[k + T];
            if (new_node->children[k]) {
                new_node->children[k]->parent = new_node;
            }
        }
    }

    for (int k = parent_node->keys_count; k > child_idx; --k) {
        parent_node->children[k + 1] = parent_node->children[k];
    }
    parent_node->children[child_idx + 1] = new_node;

    for (int k = parent_node->keys_count - 1; k >= child_idx; --k) {
        parent_node->keys[k + 1] = parent_node->keys[k];
    }
    parent_node->keys[child_idx] = child_node->keys[MIN_CHILDREN];
    parent_node->keys_count++;

    child_node->keys_count = MIN_CHILDREN;
}

void Insert(B_tree* tree, int key_value) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    if (Search(tree, key_value)) {
        return;
    }

    if (!tree->root) {
        tree->root = create_node(true, NULL);
        tree->root->keys[0] = key_value;
        tree->root->keys_count = 1;
        return;
    }

    B_node* root_node = tree->root;

    if (root_node->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false, NULL);
        new_root->children[0] = root_node;
        root_node->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, key_value);
    }
    else {
        (*InsertNotFullPtr)(root_node, key_value);
    }
}

void free_node(B_node* node_to_free) {
    if (!node_to_free) return;
    if (!node_to_free->is_leaf) {
        for (int i = 0; i <= node_to_free->keys_count; ++i) {
            free_node(node_to_free->children[i]);
        }
    }
    free(node_to_free);
}

void Free(B_tree* tree) {
    if (tree && tree->root) {
        free_node(tree->root);
        tree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator it = { 0 };

    if (!tree->root) {
        it.node = NULL;
        it.position = -1;
        return it;
    }

    B_node* current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    it.node = current;
    it.position = -1;
    return it;
}

int Next(B_tree_iterator* it) {
    if (!it->node)
        return 0;

    B_node* current_node = it->node;
    int current_pos = it->position;

    if (current_node->is_leaf) {
        if (current_pos + 1 < current_node->keys_count) {
            it->position = current_pos + 1;
            return 1;
        }
    }
    else {
        if (current_pos + 1 <= current_node->keys_count && current_node->children[current_pos + 1]) {
            B_node* next_node = current_node->children[current_pos + 1];
            while (!next_node->is_leaf) {
                next_node = next_node->children[0];
            }
            it->node = next_node;
            it->position = 0;
            return 1;
        }
    }

    B_node* node = current_node;
    while (node->parent) {
        B_node* parent_node = node->parent;

        int idx = 0;
        while (idx <= parent_node->keys_count && parent_node->children[idx] != node) {
            idx++;
        }

        if (idx < parent_node->keys_count) {
            it->node = parent_node;
            it->position = idx;
            return 1;
        }

        node = parent_node;
    }

    it->node = NULL;
    return 0;
}

int Key(B_tree_iterator* it) {
    return it->node->keys[it->position];
}