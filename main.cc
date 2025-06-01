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

B_search_result Search(B_tree* tree, int search_key) {
    B_node* current_node = tree->root;

    while (current_node != NULL) {
        int key_index = 0;
        while (key_index < current_node->keys_count && search_key > current_node->keys[key_index]) {
            ++key_index;
        }

        if (key_index < current_node->keys_count && search_key == current_node->keys[key_index]) {
            return EXISTS;
        }

        if (current_node->is_leaf) {
            return MISSING;
        }
        else {
            current_node = current_node->children[key_index];
        }
    }

    return MISSING;
}

void insertNotFull(B_node* target_node, int new_key) {
    int position = target_node->keys_count - 1;

    if (target_node->is_leaf) {
        while (position >= 0 && new_key < target_node->keys[position]) {
            target_node->keys[position + 1] = target_node->keys[position];
            --position;
        }
        target_node->keys[position + 1] = new_key;
        target_node->keys_count++;
    }
    else {
        while (position >= 0 && new_key < target_node->keys[position]) {
            --position;
        }
        ++position;

        if (target_node->children[position]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(target_node, position);
            if (new_key > target_node->keys[position]) {
                ++position;
            }
        }
        (*InsertNotFullPtr)(target_node->children[position], new_key);
    }
}

void split(B_node* parent_node, int child_index) {
    B_node* child_to_split = parent_node->children[child_index];
    B_node* new_sibling = create_node(child_to_split->is_leaf, parent_node);

    new_sibling->keys_count = MIN_CHILDREN;

    for (int key_offset = 0; key_offset < MIN_CHILDREN; ++key_offset) {
        new_sibling->keys[key_offset] = child_to_split->keys[key_offset + T];
    }

    if (!child_to_split->is_leaf) {
        for (int child_offset = 0; child_offset <= MIN_CHILDREN; ++child_offset) {
            new_sibling->children[child_offset] = child_to_split->children[child_offset + T];
            if (new_sibling->children[child_offset]) {
                new_sibling->children[child_offset]->parent = new_sibling;
            }
        }
    }

    for (int parent_pos = parent_node->keys_count; parent_pos > child_index; --parent_pos) {
        parent_node->children[parent_pos + 1] = parent_node->children[parent_pos];
    }
    parent_node->children[child_index + 1] = new_sibling;

    for (int key_pos = parent_node->keys_count - 1; key_pos >= child_index; --key_pos) {
        parent_node->keys[key_pos + 1] = parent_node->keys[key_pos];
    }
    parent_node->keys[child_index] = child_to_split->keys[MIN_CHILDREN];
    parent_node->keys_count++;

    child_to_split->keys_count = MIN_CHILDREN;
}

void Insert(B_tree* tree, int new_key) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    if (Search(tree, new_key)) {
        return;
    }

    if (!tree->root) {
        tree->root = create_node(true, NULL);
            tree->root->keys[0] = new_key;
            tree->root->keys_count = 1;
            return;
    }

    B_node* current_root = tree->root;

    if (current_root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false, NULL);
        new_root->children[0] = current_root;
        current_root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, new_key);
    }
    else {
        (*InsertNotFullPtr)(current_root, new_key);
    }
}

void free_node(B_node* node_to_free) {
    if (!node_to_free) return;
    if (!node_to_free->is_leaf) {
        for (int child_num = 0; child_num <= node_to_free->keys_count; ++child_num) {
            free_node(node_to_free->children[child_num]);
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
    if (!iterator->node)
        return 0;

    B_node* current_node = iterator->node;
    int current_position = iterator->position;

    if (current_node->is_leaf) {
        if (current_position + 1 < current_node->keys_count) {
            iterator->position = current_position + 1;
            return 1;
        }
    }
    else {
        if (current_position + 1 <= current_node->keys_count &&
            current_node->children[current_position + 1]) {
            B_node* next_node = current_node->children[current_position + 1];
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
        B_node* parent_node = node->parent;

        int child_index = 0;
        while (child_index <= parent_node->keys_count &&
            parent_node->children[child_index] != node) {
            child_index++;
        }

        if (child_index < parent_node->keys_count) {
            iterator->node = parent_node;
            iterator->position = child_index;
            return 1;
        }

        node = parent_node;
    }

    iterator->node = NULL;
    return 0;
}

int Key(B_tree_iterator* iterator) {
    return iterator->node->keys[iterator->position];
}