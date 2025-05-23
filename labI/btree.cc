#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

#define T 2
#define MIN_KEYS (T - 1)
#define MAX_KEYS (2 * T - 1)
#define MAX_CHILDREN (2 * T)

static B_node* new_node(bool leaf, B_node* parent) {
    B_node* n = (B_node*)malloc(sizeof(B_node));
    if (!n) return NULL;
    n->is_leaf = leaf;
    n->keys_count = 0;
    n->parent = parent;
    memset(n->children, 0, sizeof(n->children));
    return n;
}

void split(B_node* p, int idx) {
    B_node* full = p->children[idx];
    B_node* sib = new_node(full->is_leaf, p);

    for (int j = 0; j < MIN_KEYS; ++j) {
        sib->keys[j] = full->keys[j + T];
    }
    sib->keys_count = MIN_KEYS;

    if (!full->is_leaf) {
        for (int j = 0; j < T; ++j) {
            sib->children[j] = full->children[j + T];
            if (sib->children[j])
                sib->children[j]->parent = sib;
        }
    }

    full->keys_count = MIN_KEYS;

    for (int j = p->keys_count + 1; j > idx + 1; --j) {
        p->children[j] = p->children[j - 1];
    }
    p->children[idx + 1] = sib;

    for (int j = p->keys_count; j > idx; --j) {
        p->keys[j] = p->keys[j - 1];
    }
    p->keys[idx] = full->keys[MIN_KEYS];
    p->keys_count += 1;
}

void insertNotFull(B_node* n, int key) {
    int i = n->keys_count - 1;
    if (n->is_leaf) {
        while (i >= 0 && key < n->keys[i]) {
            n->keys[i + 1] = n->keys[i];
            --i;
        }
        n->keys[i + 1] = key;
        n->keys_count += 1;
    }
    else {
        while (i >= 0 && key < n->keys[i]) --i;
        ++i;
        if (n->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(n, i);
            if (key > n->keys[i]) ++i;
        }
        (*InsertNotFullPtr)(n->children[i], key);
    }
}

void Insert(B_tree* tree, int key) {
    if (!SplitFPtr)
        SplitFPtr = (split_t const*)(void*)&split;
    if (!InsertNotFullPtr)
        InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    if (Search(tree, key) == EXISTS) return;

    if (!tree->root) {
        tree->root = new_node(true, NULL);
        tree->root->keys[0] = key;
        tree->root->keys_count = 1;
        return;
    }
    B_node* r = tree->root;
    if (r->keys_count == MAX_KEYS) {
        B_node* s = new_node(false, NULL);
        s->children[0] = r;
        r->parent = s;
        tree->root = s;
        (*SplitFPtr)(s, 0);
        (*InsertNotFullPtr)(s, key);
    }
    else {
        (*InsertNotFullPtr)(r, key);
    }
}

static B_search_result search_rec(B_node* n, int key) {
    int i = 0;
    while (i < n->keys_count && key > n->keys[i]) ++i;
    if (i < n->keys_count && key == n->keys[i])
        return EXISTS;
    if (n->is_leaf)
        return MISSING;
    return search_rec(n->children[i], key);
}

B_search_result Search(B_tree* tree, int key) {
    if (!tree->root) return MISSING;
    return search_rec(tree->root, key);
}

static void clear_node(B_node* n) {
    if (!n) return;
    if (!n->is_leaf) {
        for (int i = 0; i <= n->keys_count; ++i) {
            clear_node(n->children[i]);
        }
    }
    free(n);
}

void Free(B_tree* tree) {
    if (tree->root) {
        clear_node(tree->root);
        tree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator it = { .node = NULL, .position = -1 };
    B_node* n = tree->root;
    while (n && !n->is_leaf) {
        n = n->children[0];
    }
    it.node = n;
    return it;
}

int Next(B_tree_iterator* it) {
    if (!it->node) return 0;
    B_node* n = it->node;
    int pos = it->position + 1;

    if (n->is_leaf) {
        if (pos < n->keys_count) {
            it->position = pos;
            return 1;
        }
    }
    else {
        if (pos <= n->keys_count && n->children[pos]) {
            B_node* c = n->children[pos];
            while (!c->is_leaf) c = c->children[0];
            it->node = c;
            it->position = 0;
            return 1;
        }
    }

    while (n->parent) {
        B_node* p = n->parent;
        int idx = 0;
        while (idx <= p->keys_count && p->children[idx] != n) ++idx;
        if (idx < p->keys_count) {
            it->node = p;
            it->position = idx;
            return 1;
        }
        n = p;
    }

    it->node = NULL;
    return 0;
}

int Key(B_tree_iterator* it) {
    return it->node->keys[it->position];
}
