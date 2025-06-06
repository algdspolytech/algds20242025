#include <stdlib.h>
#include <stdbool.h>
#include "btree.h"

typedef void (*split_t)(B_node *node_to_split, int split_at_index);
typedef void (*insertNotFull_t)(B_node *node, int data);

extern split_t const *SplitFPtr;
extern insertNotFull_t const *InsertNotFullPtr;

static B_node *createNode(bool is_leaf) {
    B_node *node = (B_node *)calloc(1, sizeof(B_node));
    node->is_leaf = is_leaf;
    return node;
}

void split(B_node *parent, int i) {
    B_node *full = parent->children[i];
    B_node *new_node = createNode(full->is_leaf);
    new_node->keys_count = MIN_CHILDREN;

    for (int j = 0; j < MIN_CHILDREN; j++) {
        new_node->keys[j] = full->keys[j + T];
    }

    if (!full->is_leaf) {
        for (int j = 0; j < T; j++) {
            new_node->children[j] = full->children[j + T];
            if (new_node->children[j])
                new_node->children[j]->parent = new_node;
        }
    }

    full->keys_count = MIN_CHILDREN;

    for (int j = parent->keys_count; j > i; j--) {
        parent->children[j + 1] = parent->children[j];
        parent->keys[j] = parent->keys[j - 1];
    }

    parent->children[i + 1] = new_node;
    parent->keys[i] = full->keys[MIN_CHILDREN];
    parent->keys_count++;
    new_node->parent = parent;
}

void insertNotFull(B_node *node, int data) {
    int i = node->keys_count - 1;
    if (node->is_leaf) {
        while (i >= 0 && data < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = data;
        node->keys_count++;
    } else {
        while (i >= 0 && data < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            if (data > node->keys[i]) {
                i++;
            }
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

void Insert(B_tree *tree, int data) {
    if (!tree->root) {
        tree->root = createNode(true);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    B_node *r = tree->root;
    for (int i = 0; i < r->keys_count; i++) {
        if (r->keys[i] == data)
            return;
    }

    if (r->keys_count == MAX_KEYS) {
        B_node *s = createNode(false);
        tree->root = s;
        s->children[0] = r;
        r->parent = s;
        (*SplitFPtr)(s, 0);
        (*InsertNotFullPtr)(s, data);
    } else {
        (*InsertNotFullPtr)(r, data);
    }
}

B_search_result Search(B_tree *tree, int data) {
    B_node *node = tree->root;
    while (node) {
        int i = 0;
        while (i < node->keys_count && data > node->keys[i]) {
            i++;
        }
        if (i < node->keys_count && data == node->keys[i]) {
            return EXISTS;
        } else if (node->is_leaf) {
            return MISSING;
        } else {
            node = node->children[i];
        }
    }
    return MISSING;
}

void freeNode(B_node *node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            freeNode(node->children[i]);
        }
    }
    free(node);
}

void Free(B_tree *tree) {
    freeNode(tree->root);
    tree->root = NULL;
}

static void minPushLeft(B_node **stack, int *top, B_node *node) {
    while (!node->is_leaf) {
        stack[++(*top)] = node;
        node = node->children[0];
    }
    stack[++(*top)] = node;
}

B_tree_iterator IteratorBegin(B_tree *tree) {
    B_tree_iterator iter = {0};
    if (!tree->root) return iter;
    B_node *stack[MAX_KEYS * MAX_CHILDREN] = {0};
    int top = -1;
    minPushLeft(stack, &top, tree->root);
    iter.node = stack[top];
    iter.position = -1;
    return iter;
}

int Next(B_tree_iterator *iter) {
    if (!iter->node) return 0;
    iter->position++;
    while (iter->position >= iter->node->keys_count) {
        if (!iter->node->parent) {
            iter->node = NULL;
            return 0;
        }
        B_node *parent = iter->node->parent;
        int i;
        for (i = 0; i <= parent->keys_count; i++) {
            if (parent->children[i] == iter->node)
                break;
        }
        if (i < parent->keys_count) {
            iter->node = parent;
            iter->position = i;
            return 1;
        }
        iter->node = parent;
        iter->position = parent->keys_count;
    }
    return 1;
}

int Key(B_tree_iterator *iter) {
    return iter->node->keys[iter->position];
}