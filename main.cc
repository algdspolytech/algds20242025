#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

B_search_result Search(B_tree* btree, int value) {
    B_node* curr = btree ? btree->root : NULL;
    while (curr) {
        int pos = 0;
        for (; pos < curr->keys_count; pos++) {
            if (value == curr->keys[pos]) return EXISTS;
            if (value < curr->keys[pos]) break;
        }

        if (curr->is_leaf) return MISSING;
        curr = curr->children[pos];
    }
    return MISSING;
}

static B_node* CreateNode(bool leaf, B_node* parent_ref) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (!node) return NULL;

    node->is_leaf = leaf;
    node->keys_count = 0;
    node->parent = parent_ref;

    int i = 0;
    while (i < MAX_CHILDREN) {
        node->children[i++] = NULL;
    }
    return node;
}

void split(B_node* parent, int idx) {
    B_node* full_node = parent->children[idx];
    B_node* new_node = CreateNode(full_node->is_leaf, parent);
    if (!new_node) return;

    new_node->keys_count = MIN_CHILDREN;
    int k = MIN_CHILDREN - 1;
    while (k >= 0) {
        new_node->keys[k] = full_node->keys[k + T];
        k--;
    }

    if (!full_node->is_leaf) {
        int j = MIN_CHILDREN;
        do {
            new_node->children[j] = full_node->children[j + T];
            if (new_node->children[j]) {
                new_node->children[j]->parent = new_node;
            }
        } while (j-- > 0);
    }

    full_node->keys_count = MIN_CHILDREN;

    int j = parent->keys_count;
    do {
        parent->children[j + 1] = parent->children[j];
    } while (--j > idx);
    parent->children[idx + 1] = new_node;

    j = parent->keys_count;
    while (j-- > idx) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[idx] = full_node->keys[MIN_CHILDREN];
    parent->keys_count++;
}

void insertNotFull(B_node* curr, int value) {
    if (curr->is_leaf) {
        int pos = curr->keys_count++;
        while (pos > 0 && value < curr->keys[pos - 1]) {
            curr->keys[pos] = curr->keys[pos - 1];
            pos--;
        }
        curr->keys[pos] = value;
        return;
    }

    int pos = 0;
    while (pos < curr->keys_count && value > curr->keys[pos]) {
        pos++;
    }

    B_node* child = curr->children[pos];
    if (child->keys_count == MAX_KEYS) {
        (*SplitFPtr)(curr, pos);
        if (value > curr->keys[pos]) {
            pos++;
        }
    }
    (*InsertNotFullPtr)(curr->children[pos], value);
}

void Insert(B_tree* btree, int value) {
    if (!SplitFPtr) SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    if (Search(btree, value) == EXISTS) return;

    if (!btree->root) {
        btree->root = CreateNode(true, NULL);
        if (!btree->root) return;
        btree->root->keys[0] = value;
        btree->root->keys_count = 1;
        return;
    }

    B_node* root = btree->root;
    if (root->keys_count == MAX_KEYS) {
        B_node* new_root = CreateNode(false, NULL);
        if (!new_root) return;

        new_root->children[0] = root;
        root->parent = new_root;
        btree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, value);
    }
    else {
        (*InsertNotFullPtr)(root, value);
    }
}

void FreeNode(B_node* node) {
    if (!node) return;

    if (!node->is_leaf) {
        int i = node->keys_count;
        do {
            FreeNode(node->children[i]);
        } while (i-- > 0);
    }
    free(node);
}

void Free(B_tree* btree) {
    if (!btree || !btree->root) return;

    FreeNode(btree->root);
    btree->root = NULL;
}

B_tree_iterator IteratorBegin(B_tree* btree) {
    B_tree_iterator iter = { NULL, -1 };
    if (!btree || !btree->root) return iter;

    B_node* curr = btree->root;
    while (!curr->is_leaf) {
        curr = curr->children[0];
    }

    iter.node = curr;
    iter.position = -1;
    return iter;
}

int Next(B_tree_iterator* iter) {
    if (!iter || !iter->node) return 0;

    B_node* curr = iter->node;
    int pos = iter->position + 1;

    if (curr->is_leaf && pos < curr->keys_count) {
        iter->position = pos;
        return 1;
    }

    if (!curr->is_leaf && pos <= curr->keys_count) {
        B_node* next = curr->children[pos];
        if (next) {
            while (!next->is_leaf) {
                next = next->children[0];
            }
            iter->node = next;
            iter->position = 0;
            return 1;
        }
    }

    while (curr->parent) {
        B_node* parent = curr->parent;
        int idx = 0;
        for (; idx <= parent->keys_count; idx++) {
            if (parent->children[idx] == curr) break;
        }

        if (idx < parent->keys_count) {
            iter->node = parent;
            iter->position = idx;
            return 1;
        }
        curr = parent;
    }

    iter->node = NULL;
    iter->position = -1;
    return 0;
}

int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position < 0) return 0;
    return iter->node->keys[iter->position];
}