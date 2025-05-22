#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

static B_node* create_new_node(bool is_leaf, B_node* parent) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (!node) return NULL;

    node->is_leaf = is_leaf;
    node->keys_count = 0;
    node->parent = parent;

    for (int i = 0; i < MAX_CHILDREN; ++i)
        node->children[i] = NULL;

    return node;
}

B_search_result Search(B_tree* tree, int value) {
    if (!tree || !tree->root) return MISSING;

    B_node* current = tree->root;

    while (current) {
        int left = 0;
        int right = current->keys_count;

        while (left < right) {
            int mid = (left + right) / 2;
            if (value == current->keys[mid])
                return EXISTS;
            else if (value < current->keys[mid])
                right = mid;
            else
                left = mid + 1;
        }

        if (current->is_leaf)
            return MISSING;

        current = current->children[left];
    }

    return MISSING;
}

void split(B_node* parent, int index) {
    B_node* old_node = parent->children[index];
    B_node* new_node = create_new_node(old_node->is_leaf, parent);
    if (!new_node) return;

    new_node->keys_count = MIN_CHILDREN;

    for (int i = 0; i < MIN_CHILDREN; ++i)
        new_node->keys[i] = old_node->keys[i + T];

    if (!old_node->is_leaf) {
        for (int i = 0; i <= MIN_CHILDREN; ++i) {
            new_node->children[i] = old_node->children[i + T];
            if (new_node->children[i])
                new_node->children[i]->parent = new_node;
        }
    }

    old_node->keys_count = MIN_CHILDREN;

    for (int i = parent->keys_count; i > index; --i)
        parent->children[i + 1] = parent->children[i];

    parent->children[index + 1] = new_node;

    for (int i = parent->keys_count - 1; i >= index; --i)
        parent->keys[i + 1] = parent->keys[i];

    parent->keys[index] = old_node->keys[MIN_CHILDREN];
    parent->keys_count++;
}

void insertNotFull(B_node* node, int value) {
    int pos = node->keys_count;

    if (node->is_leaf) {
        while (pos > 0 && value < node->keys[pos - 1]) {
            node->keys[pos] = node->keys[pos - 1];
            --pos;
        }
        node->keys[pos] = value;
        node->keys_count++;
        return;
    }

    pos = 0;
    while (pos < node->keys_count && value > node->keys[pos])
        ++pos;

    B_node* child = node->children[pos];

    if (child->keys_count == MAX_KEYS) {
        (*SplitFPtr)(node, pos);
        if (value > node->keys[pos])
            ++pos;
    }

    (*InsertNotFullPtr)(node->children[pos], value);
}

void Insert(B_tree* tree, int value) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    if (Search(tree, value) == EXISTS)
        return;

    if (!tree->root) {
        tree->root = create_new_node(true, NULL);
        if (!tree->root) return;
        tree->root->keys[0] = value;
        tree->root->keys_count = 1;
        return;
    }

    B_node* root = tree->root;

    if (root->keys_count == MAX_KEYS) {
        B_node* new_root = create_new_node(false, NULL);
        if (!new_root) return;

        new_root->children[0] = root;
        root->parent = new_root;

        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, value);
    } else {
        (*InsertNotFullPtr)(root, value);
    }
}

void free_node(B_node* node) {
    if (!node) return;

    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i)
            free_node(node->children[i]);
    }

    free(node);
}

void Free(B_tree* tree) {
    if (!tree || !tree->root) return;

    free_node(tree->root);
    tree->root = NULL;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator it = {NULL, -1};
    if (!tree || !tree->root) return it;

    B_node* current = tree->root;

    while (current && !current->is_leaf)
        current = current->children[0];

    it.node = current;
    it.position = -1;

    return it;
}

int Next(B_tree_iterator* it) {
    if (!it || !it->node) return 0;

    B_node* curr = it->node;
    int pos = it->position + 1;

    if (curr->is_leaf && pos < curr->keys_count) {
        it->position = pos;
        return 1;
    }

    if (!curr->is_leaf && pos <= curr->keys_count) {
        B_node* next = curr->children[pos];
        if (next) {
            while (!next->is_leaf)
                next = next->children[0];
            it->node = next;
            it->position = 0;
            return 1;
        }
    }

    B_node* up = curr->parent;

    while (up) {
        int idx = 0;
        while (idx <= up->keys_count && up->children[idx] != curr)
            ++idx;

        if (idx < up->keys_count) {
            it->node = up;
            it->position = idx;
            return 1;
        }

        curr = up;
        up = up->parent;
    }

    it->node = NULL;
    it->position = -1;
    return 0;
}

int Key(B_tree_iterator* it) {
    if (!it || !it->node || it->position < 0)
        return 0;

    return it->node->keys[it->position];
}