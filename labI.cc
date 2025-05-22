#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"


static B_node* make_node(bool leaf_flag, B_node* parent_node) {
    B_node* new_node = (B_node*)malloc(sizeof(B_node));
    new_node->is_leaf = leaf_flag;
    new_node->keys_count = 0;
    new_node->parent = parent_node;
    memset(new_node->children, 0, sizeof(new_node->children));
    return new_node;
}

B_search_result Search(B_tree* btree, int value) {
    B_node* current = btree->root;

    while (current != NULL) {
        int idx = 0;
        while (idx < current->keys_count && value > current->keys[idx]) {
            ++idx;
        }

        if (idx < current->keys_count && value == current->keys[idx]) {
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

void insertNotFull(B_node* target_node, int new_value) {
    int pos = target_node->keys_count - 1;

    if (target_node->is_leaf) {
        while (pos >= 0 && new_value < target_node->keys[pos]) {
            target_node->keys[pos + 1] = target_node->keys[pos];
            --pos;
        }
        target_node->keys[pos + 1] = new_value;
        target_node->keys_count++;
    }
    else {
        while (pos >= 0 && new_value < target_node->keys[pos]) {
            --pos;
        }
        ++pos;

        if (target_node->children[pos]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(target_node, pos);
            if (new_value > target_node->keys[pos]) {
                ++pos;
            }
        }
        (*InsertNotFullPtr)(target_node->children[pos], new_value);
    }
}

void split(B_node* parent_node, int child_idx) {
    B_node* old_child = parent_node->children[child_idx];
    B_node* right_child = make_node(old_child->is_leaf, parent_node);

    right_child->keys_count = MIN_CHILDREN;

    for (int j = 0; j < MIN_CHILDREN; ++j) {
        right_child->keys[j] = old_child->keys[j + T];
    }

    if (!old_child->is_leaf) {
        for (int j = 0; j <= MIN_CHILDREN; ++j) {
            right_child->children[j] = old_child->children[j + T];
            if (right_child->children[j]) {
                right_child->children[j]->parent = right_child;
            }
        }
    }

    for (int j = parent_node->keys_count; j > child_idx; --j) {
        parent_node->children[j + 1] = parent_node->children[j];
    }
    parent_node->children[child_idx + 1] = right_child;

    for (int j = parent_node->keys_count - 1; j >= child_idx; --j) {
        parent_node->keys[j + 1] = parent_node->keys[j];
    }
    parent_node->keys[child_idx] = old_child->keys[MIN_CHILDREN];
    parent_node->keys_count++;

    old_child->keys_count = MIN_CHILDREN;
}

void Insert(B_tree* btree, int value) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    if (Search(btree, value) == EXISTS) {
        return;
    }

    if (!btree->root) {
        btree->root = make_node(true, NULL);
        btree->root->keys[0] = value;
        btree->root->keys_count = 1;
        return;
    }

    B_node* root_node = btree->root;

    if (root_node->keys_count == MAX_KEYS) {
        B_node* new_root = make_node(false, NULL);
        new_root->children[0] = root_node;
        root_node->parent = new_root;
        btree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, value);
    }
    else {
        (*InsertNotFullPtr)(root_node, value);
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

void Free(B_tree* btree) {
    if (btree && btree->root) {
        free_node(btree->root);
        btree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree* btree) {
    B_tree_iterator iter = { 0 };

    if (!btree->root) {
        iter.node = NULL;
        iter.position = -1;
        return iter;
    }

    B_node* current = btree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    iter.node = current;
    iter.position = -1;
    return iter;
}

int Next(B_tree_iterator* iterator) {

    if (!iterator->node)
        return 0;

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
            B_node* cur = current_node->children[current_pos + 1];
            while (!cur->is_leaf) {
                cur = cur->children[0];
            }
            iterator->node = cur;
            iterator->position = 0;
            return 1;
        }

    }

    B_node* cur = current_node;
    while (cur->parent) {
        B_node* parent = cur->parent;

        int i = 0;
        while (i <= parent->keys_count && parent->children[i] != cur) {
            i++;
        }

        if (i < parent->keys_count) {
            iterator->node = parent;
            iterator->position = i;
            return 1;
        }

        cur = parent;
    }


    iterator->node = NULL;
    return 0;
}


int Key(B_tree_iterator* iterator) {
    return iterator->node->keys[iterator->position];
}