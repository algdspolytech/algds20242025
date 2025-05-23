#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split(B_node* parent, int idx);
void insertNotFull(B_node* node, int data);

static const split_t LocalSplit = split;
static const insertNotFull_t LocalInsertNotFull = insertNotFull;

extern split_t const* SplitFPtr;
extern insertNotFull_t const* InsertNotFullPtr;

static B_node* alloc_node(int is_leaf) {
    B_node* n = (B_node*)malloc(sizeof(B_node));
    if (!n)
        return NULL;
    n->keys_count = 0;
    n->is_leaf = is_leaf;
    n->parent = NULL;
    memset(n->children, 0, sizeof(n->children));
    return n;
}

int Next(B_tree_iterator* iter) {
    if (!iter || !iter->node)
        return 0;
    B_node* current_node = iter->node;
    int current_pos = iter->position;
    if (!current_node->is_leaf && current_pos != -1) {
        B_node* child = current_node->children[current_pos + 1];
        while (!child->is_leaf)
            child = child->children[0];
        iter->node = child;
        iter->position = 0;
        return 1;
    }
    if (current_node->is_leaf) {
        if (current_pos + 1 < current_node->keys_count) {
            iter->position++;
            return 1;
        }
        else {
            B_node* child = current_node;
            B_node* parent = child->parent;
            int child_idx;
            while (parent) {
                for (child_idx = 0; child_idx <= parent->keys_count; child_idx++) {
                    if (parent->children[child_idx] == child) {
                        break;
                    }
                }
                if (child_idx < parent->keys_count) {
                    iter->node = parent;
                    iter->position = child_idx;
                    return 1;
                }
                child = parent;
                parent = parent->parent;
            }
            iter->node = NULL;
            iter->position = -1;
            return 0;
        }
    }
    if (!current_node->is_leaf && current_pos == -1) {
        B_node* child = current_node;
        while (!child->is_leaf)
            child = child->children[0];
        iter->node = child;
        iter->position = 0;
        return 1;
    }
    iter->node = NULL;
    iter->position = -1;
    return 0;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator it = { 0 };
    if (!tree || !tree->root || tree->root->keys_count == 0) {
        it.node = NULL;
        it.position = -1;
        return it;
    }
    B_node* n = tree->root;
    while (!n->is_leaf)
        n = n->children[0];
    it.node = n;
    it.position = -1;
    return it;
}

int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position < 0 ||
        iter->position >= iter->node->keys_count)
        return 0;
    return iter->node->keys[iter->position];
}

B_search_result Search(B_tree* tree, int data) {
    B_node* n = tree->root;
    while (n) {
        int i = 0;
        while (i < n->keys_count && data > n->keys[i])
            i++;
        if (i < n->keys_count && data == n->keys[i])
            return EXISTS;
        if (n->is_leaf)
            break;
        n = n->children[i];
    }
    return MISSING;
}

extern "C" void Insert(B_tree* tree, int data) {
    if (!tree->root) {
        tree->root = alloc_node(1);
    }
    if (Search(tree, data) == EXISTS)
        return;
    B_node* r = tree->root;
    if (r->keys_count == MAX_KEYS) {
        B_node* s = alloc_node(0);
        tree->root = s;
        s->children[0] = r;
        r->parent = s;
        (*SplitFPtr)(s, 0);
        (*InsertNotFullPtr)(s, data);
    }
    else {
        (*InsertNotFullPtr)(r, data);
    }
}

void insertNotFull(B_node* node, int data) {
#ifdef MY_DEBUG_PRINT
    printf("insertNotFull: node keys_count=%d, data=%d\n", node->keys_count,
        data);
#endif
    int i = node->keys_count - 1;
    if (node->is_leaf) {
        while (i >= 0 && data < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = data;
        node->keys_count++;
    }
    else {
        while (i >= 0 && data < node->keys[i])
            i--;
        i++;
        B_node* child = node->children[i];
        if (child->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            if (data > node->keys[i])
                i++;
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

void split(B_node* parent, int idx) {
#ifdef MY_DEBUG_PRINT
    printf("split: parent keys_count=%d, idx=%d\n", parent->keys_count, idx);
#endif
    B_node* y = parent->children[idx];
    B_node* z = alloc_node(y->is_leaf);
    int mid = T - 1;
    for (int j = 0; j < mid; j++) {
        z->keys[j] = y->keys[j + T];
    }
    if (!y->is_leaf) {
        for (int j = 0; j < T; j++) {
            z->children[j] = y->children[j + T];
            if (z->children[j])
                z->children[j]->parent = z;
        }
    }
    z->keys_count = mid;
    y->keys_count = mid;
    for (int j = parent->keys_count; j >= idx + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[idx + 1] = z;
    z->parent = parent;
    for (int j = parent->keys_count - 1; j >= idx; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[idx] = y->keys[mid];
    parent->keys_count++;
}

void Free(B_tree* tree) {
    if (!tree->root)
        return;
    size_t cap = 16, sp = 0;
    B_node** stack = (B_node**)malloc(sizeof(B_node*) * cap);
    stack[sp++] = tree->root;
    while (sp) {
        B_node* n = stack[--sp];
        if (!n->is_leaf) {
            for (int i = 0; i <= n->keys_count; i++) {
                if (n->children[i]) {
                    if (sp == cap) {
                        cap *= 2;
                        stack = (B_node**)realloc(stack, sizeof(B_node*) * cap);
                    }
                    stack[sp++] = n->children[i];
                }
            }
        }
        free(n);
    }
    free(stack);
    tree->root = NULL;
}