#include "btree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static B_node* create_node(bool is_leaf) {
    B_node* node = (B_node*)calloc(1, sizeof(B_node));
    if (!node) return NULL;

    node->is_leaf = is_leaf;
    return node;
}

static int find_position(B_node* node, int data) {
    if (!node) return 0;

    int pos = 0;
    while (pos < node->keys_count && data > node->keys[pos]) {
        pos++;
    }
    return pos;
}

void split(B_node* parent, int child_index) {
    if (!parent || child_index < 0 || child_index > parent->keys_count) return;
    if (!parent->children[child_index]) return;

    B_node* child = parent->children[child_index];
    if (child->keys_count != MAX_KEYS) return;

    B_node* new_node = create_node(child->is_leaf);
    if (!new_node) return;

    new_node->parent = parent;
    int t = T;
    for (int i = 0; i < t - 1; i++) {
        new_node->keys[i] = child->keys[t + i];
    }
    new_node->keys_count = t - 1;

    if (!child->is_leaf) {
        for (int i = 0; i < t; i++) {
            new_node->children[i] = child->children[t + i];
            if (new_node->children[i]) {
                new_node->children[i]->parent = new_node;
            }
            child->children[t + i] = NULL;
        }
    }
    child->keys_count = t - 1;

    for (int i = parent->keys_count; i > child_index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[child_index + 1] = new_node;

    for (int i = parent->keys_count - 1; i >= child_index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[child_index] = child->keys[t - 1];
    parent->keys_count++;
}

void insertNotFull(B_node* node, int data) {
    if (!node) return;

    int pos = find_position(node, data);

    if (node->is_leaf) {
        if (pos < node->keys_count&& node->keys[pos] == data) return;

        for (int i = node->keys_count; i > pos; i--) {
            node->keys[i] = node->keys[i - 1];
        }
        node->keys[pos] = data;
        node->keys_count++;
    }
    else {
        if (pos > 0 && node->keys[pos - 1] == data) return;

        if (node->children[pos]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, pos);
            if (data > node->keys[pos]) pos++;
        }
        (*InsertNotFullPtr)(node->children[pos], data);
    }
}

void Insert(B_tree* tree, int data) {
    if (!tree) return;

    if (tree->root) {
        int pos = find_position(tree->root, data);
        if (pos < tree->root->keys_count && tree->root->keys[pos] == data) {
            return;
        }
    }

    if (!tree->root) {
        tree->root = create_node(true);
        if (!tree->root) return;
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    if (tree->root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false);
        if (!new_root) return;

        new_root->children[0] = tree->root;
        tree->root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
    }

    (*InsertNotFullPtr)(tree->root, data);
}

B_search_result Search(B_tree* tree, int data) {
    if (!tree || !tree->root) return MISSING;

    B_node* current = tree->root;
    while (current) {
        int pos = find_position(current, data);

        if (pos < current->keys_count && current->keys[pos] == data) {
            return EXISTS;
        }

        if (current->is_leaf) {
            return MISSING;
        }

        current = current->children[pos];
    }
    return MISSING;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { NULL, -1 };

    if (!tree || !tree->root || tree->root->keys_count == 0) {
        return iter;
    }

    B_node* current = tree->root;
    while (current && !current->is_leaf) {
        current = current->children[0];
    }

    if (current && current->keys_count > 0) {
        iter.node = current;
        iter.position = -1;
    }

    return iter;
}

int Next(B_tree_iterator* iter) {
    if (!iter || !iter->node) {
        return 0;
    }

    if (iter->position == -1) {
        if (iter->node->keys_count > 0) {
            iter->position = 0;
            return 1;
        }
        iter->node = NULL;
        return 0;
    }

    if (iter->position + 1 < iter->node->keys_count) {
        iter->position++;
        return 1;
    }

    B_node* current = iter->node;

    if (!current->parent) {
        iter->node = NULL;
        return 0;
    }

    int child_idx = 0;
    while (child_idx <= current->parent->keys_count) {
        if (current->parent->children[child_idx] == current) {
            break;
        }
        child_idx++;
    }

    if (child_idx <= current->parent->keys_count &&
        child_idx < current->parent->keys_count) {

        current = current->parent->children[child_idx + 1];
        if (!current) {
            iter->node = NULL;
            return 0;
        }

        while (current && !current->is_leaf) {
            current = current->children[0];
            if (!current) {
                iter->node = NULL;
                return 0;
            }
        }

        if (current && current->keys_count > 0) {
            iter->node = current;
            iter->position = 0;
            return 1;
        }
    }

    iter->node = NULL;
    return 0;
}

int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node ||
        iter->position < 0 ||
        iter->position >= iter->node->keys_count) {
        return 0;
    }
    return iter->node->keys[iter->position];
}

static void free_recursive(B_node* node) {
    if (!node) return;

    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            free_recursive(node->children[i]);
        }
    }
    free(node);
}

void Free(B_tree* tree) {
    if (!tree) return;
    free_recursive(tree->root);
    tree->root = NULL;
}