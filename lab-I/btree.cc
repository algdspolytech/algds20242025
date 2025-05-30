#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

B_search_result Search(B_tree *tree, int data) {
    B_node *node = tree->root;
    while (node != NULL) {
        int i = 0;

        while (i < node->keys_count && data > node->keys[i]) ++i;

        if (i < node->keys_count && data == node->keys[i]) return EXISTS;

        if (node->is_leaf) return MISSING;

        else node = node->children[i];
    }
    return MISSING;
}


static B_node *create_node(bool is_leaf, B_node *parent) {
    B_node *node = (B_node *) malloc(sizeof(B_node));
    node->is_leaf = is_leaf;
    node->keys_count = 0;
    node->parent = parent;
    memset(node->children, 0, sizeof(node->children));
    return node;
}

void insertNotFull(B_node *node, int data) {
    int i = node->keys_count - 1;

    if (node->is_leaf) {
        while (i >= 0 && data < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = data;
        node->keys_count++;
    } else {
        while (i >= 0 && data < node->keys[i]) --i;

        ++i;

        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            if (data > node->keys[i]) ++i;

        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

void split(B_node *parent, int i) {
    B_node *full_child = parent->children[i];
    B_node *new_child = create_node(full_child->is_leaf, parent);

    new_child->keys_count = MIN_CHILDREN;

    for (int j = 0; j < MIN_CHILDREN; ++j) {
        new_child->keys[j] = full_child->keys[j + T];
    }

    if (!full_child->is_leaf) {
        for (int j = 0; j <= MIN_CHILDREN; ++j) {
            new_child->children[j] = full_child->children[j + T];
            if (new_child->children[j]) {
                new_child->children[j]->parent = new_child;
            }
        }
    }

    for (int j = parent->keys_count; j > i; --j) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = new_child;

    for (int j = parent->keys_count - 1; j >= i; --j) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = full_child->keys[MIN_CHILDREN];
    parent->keys_count++;

    full_child->keys_count = MIN_CHILDREN;
}


void Insert(B_tree *tree, int data) {
    if (!SplitFPtr) SplitFPtr = (split_t const *) (void *) &split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const *) (void *) &insertNotFull;

    if (Search(tree, data) == EXISTS) return;

    if (!tree->root) {
        tree->root = create_node(true, NULL);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    B_node *root = tree->root;

    if (root->keys_count == MAX_KEYS) {
        B_node *new_root = create_node(false, NULL);
        new_root->children[0] = root;
        root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, data);
    } else {
        (*InsertNotFullPtr)(root, data);
    }
}

int Key(B_tree_iterator *iter) {
    return iter->node->keys[iter->position];
}


int Next(B_tree_iterator *iter) {

    if (!iter->node)
        return 0;

    B_node *node = iter->node;
    int position = iter->position;

    if (node->is_leaf) {
        if (position + 1 < node->keys_count) {
            iter->position = position + 1;
            return 1;
        }

    } else {

        if (position + 1 <= node->keys_count && node->children[position + 1]) {
            B_node *current = node->children[position + 1];
            while (!current->is_leaf) {
                current = current->children[0];
            }
            iter->node = current;
            iter->position = 0;
            return 1;
        }
    }

    B_node *current = node;
    while (current->parent) {
        B_node *p = current->parent;

        int i = 0;
        while (i <= p->keys_count && p->children[i] != current) i++;

        if (i < p->keys_count) {
            iter->node = p;
            iter->position = i;
            return 1;
        }
        current = p;
    }

    iter->node = NULL;
    return 0;
}


void free_node(B_node *node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i) {
            free_node(node->children[i]);
        }
    }
    free(node);
}

void Free(B_tree *tree) {
    if (tree && tree->root) {
        free_node(tree->root);
        tree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree *tree) {
    B_tree_iterator treeIterator = {0};

    if (!tree->root) {
        treeIterator.node = NULL;
        treeIterator.position = -1;
        return treeIterator;
    }

    B_node *current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    treeIterator.node = current;
    treeIterator.position = -1;
    return treeIterator;
}
