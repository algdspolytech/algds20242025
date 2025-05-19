#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

static B_node* allocate_node(bool leaf, B_node* parent) {
    B_node* n = (B_node*)malloc(sizeof(B_node));
    if (!n) return NULL;
    n->is_leaf = leaf;
    n->keys_count = 0;
    n->parent = parent;
    memset(n->children, 0, sizeof(n->children));
    return n;
}

B_search_result Search(B_tree* tree, int value) {
    B_node* current = tree->root;

    while (current) {
        int i = 0;
        while (i < current->keys_count && value > current->keys[i]) {
            i++;
        }

        if (i < current->keys_count && current->keys[i] == value)
            return EXISTS;

        if (current->is_leaf)
            return MISSING;

        current = current->children[i];
    }

    return MISSING;
}

void insertNotFull(B_node* node, int value) {
    int idx = node->keys_count - 1;

    if (node->is_leaf) {
        while (idx >= 0 && node->keys[idx] > value) {
            node->keys[idx + 1] = node->keys[idx];
            idx--;
        }
        node->keys[idx + 1] = value;
        node->keys_count++;
    }
    else {
        while (idx >= 0 && value < node->keys[idx]) {
            idx--;
        }
        idx++;
        if (node->children[idx]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, idx);
            if (value > node->keys[idx]) {
                idx++;
            }
        }
        (*InsertNotFullPtr)(node->children[idx], value);
    }
}

void split(B_node* parent, int index) {
    B_node* left = parent->children[index];
    B_node* right = allocate_node(left->is_leaf, parent);

    right->keys_count = MIN_CHILDREN;

    memcpy(right->keys, &left->keys[T], MIN_CHILDREN * sizeof(int));

    if (!left->is_leaf) {
        for (int i = 0; i <= MIN_CHILDREN; ++i) {
            right->children[i] = left->children[i + T];
            if (right->children[i])
                right->children[i]->parent = right;
        }
    }

    for (int j = parent->keys_count; j > index; --j) {
        parent->children[j + 1] = parent->children[j];
        parent->keys[j] = parent->keys[j - 1];
    }

    parent->children[index + 1] = right;
    parent->keys[index] = left->keys[MIN_CHILDREN];
    parent->keys_count++;

    left->keys_count = MIN_CHILDREN;
}

void Insert(B_tree* tree, int value) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    if (Search(tree, value) == EXISTS)
        return;

    if (!tree->root) {
        tree->root = allocate_node(true, NULL);
        tree->root->keys[0] = value;
        tree->root->keys_count = 1;
        return;
    }

    B_node* r = tree->root;

    if (r->keys_count == MAX_KEYS) {
        B_node* new_root = allocate_node(false, NULL);
        new_root->children[0] = r;
        r->parent = new_root;
        tree->root = new_root;
        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, value);
    }
    else {
        (*InsertNotFullPtr)(r, value);
    }
}

static void destroy_node(B_node* node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            destroy_node(node->children[i]);
        }
    }
    free(node);
}

void Free(B_tree* tree) {
    if (tree && tree->root) {
        destroy_node(tree->root);
        tree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { 0 };
    if (!tree->root) {
        iter.node = NULL;
        iter.position = -1;
        return iter;
    }

    B_node* n = tree->root;
    while (!n->is_leaf)
        n = n->children[0];

    iter.node = n;
    iter.position = -1;
    return iter;
}

int Next(B_tree_iterator* iter) {
    if (!iter->node) return 0;

    B_node* node = iter->node;
    int pos = iter->position;

    if (node->is_leaf) {
        if (pos + 1 < node->keys_count) {
            iter->position++;
            return 1;
        }
    }
    else if (pos + 1 <= node->keys_count) {
        B_node* next = node->children[pos + 1];
        while (!next->is_leaf)
            next = next->children[0];
        iter->node = next;
        iter->position = 0;
        return 1;
    }

    B_node* current = node;
    while (current->parent) {
        B_node* parent = current->parent;
        int i = 0;
        while (i <= parent->keys_count && parent->children[i] != current)
            i++;

        if (i < parent->keys_count) {
            iter->node = parent;
            iter->position = i;
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