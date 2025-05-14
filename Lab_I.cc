#include "btree.h"
#include <stdlib.h>
#include <string.h>


extern split_t const* SplitFPtr;
extern insertNotFull_t const* InsertNotFullPtr;

static void InitFunctionPointers(void) {
    static split_t const split_arr[] = { split };
    static insertNotFull_t const insert_arr[] = { insertNotFull };
    SplitFPtr = split_arr;
    InsertNotFullPtr = insert_arr;
}

static B_node* CreateNode(bool is_leaf, B_node* parent) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    memset(node, 0, sizeof(B_node));
    node->is_leaf = is_leaf;
    node->parent = parent;
    return node;
}

void split(B_node* parent, int i) {
    B_node* z = CreateNode(parent->children[i]->is_leaf, parent);
    B_node* y = parent->children[i];
    z->keys_count = MIN_CHILDREN;

    for (int j = 0; j < MIN_CHILDREN; j++)
        z->keys[j] = y->keys[j + T];

    if (!y->is_leaf) {
        for (int j = 0; j < T; j++) {
            z->children[j] = y->children[j + T];
            if (z->children[j])
                z->children[j]->parent = z;
        }
    }

    y->keys_count = MIN_CHILDREN;

    for (int j = parent->keys_count; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[i + 1] = z;

    for (int j = parent->keys_count - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = y->keys[MIN_CHILDREN];
    parent->keys_count++;
}

void insertNotFull(B_node* node, int data) {
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

        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            if (data > node->keys[i])
                i++;
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

void Insert(B_tree* tree, int data) {
    InitFunctionPointers();

    if (!tree->root) {
        tree->root = CreateNode(true, NULL);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    if (Search(tree, data) == EXISTS)
        return;

    B_node* r = tree->root;

    if (r->keys_count == MAX_KEYS) {
        B_node* s = CreateNode(false, NULL);
        s->children[0] = r;
        r->parent = s;
        tree->root = s;
        (*SplitFPtr)(s, 0);
        (*InsertNotFullPtr)(s, data);
    }
    else {
        (*InsertNotFullPtr)(r, data);
    }
}

B_search_result Search(B_tree* tree, int data) {
    B_node* cur = tree->root;
    while (cur) {
        int i = 0;
        while (i < cur->keys_count && data > cur->keys[i])
            i++;
        if (i < cur->keys_count && data == cur->keys[i])
            return EXISTS;
        if (cur->is_leaf)
            return MISSING;
        cur = cur->children[i];
    }
    return MISSING;
}

void FreeNode(B_node* node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            FreeNode(node->children[i]);
        }
    }
    free(node);
}

void Free(B_tree* tree) {
    FreeNode(tree->root);
    tree->root = NULL;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator it = { NULL, -1 };
    if (!tree || !tree->root)
        return it;

    B_node* cur = tree->root;
    while (!cur->is_leaf)
        cur = cur->children[0];

    it.node = cur;
    it.position = -1;
    return it;
}

int Next(B_tree_iterator* it) {
    if (!it || !it->node)
        return 0;

    it->position++;

    if (!it->node->is_leaf && it->position <= it->node->keys_count) {
        B_node* child = it->node->children[it->position];
        while (!child->is_leaf)
            child = child->children[0];
        it->node = child;
        it->position = 0;
        return 1;
    }

    if (it->position < it->node->keys_count)
        return 1;



    B_node* node = it->node;
    while (node->parent) {
        B_node* parent = node->parent;
        int i = 0;
        while (i <= parent->keys_count && parent->children[i] != node)
            i++;
        if (i < parent->keys_count) {
            it->node = parent;
            it->position = i;
            return 1;
        }
        node = parent;
    }

    it->node = NULL;
    return 0;
}

int Key(B_tree_iterator* it) {
    return it->node->keys[it->position];
}
