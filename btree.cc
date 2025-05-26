#include "btree.h"
#include <stdlib.h>
#include <string.h>

extern split_t const* SplitFPtr;
extern insertNotFull_t const* InsertNotFullPtr;

static B_node* create_node(void) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (!node) return NULL;

    for (int i = 0; i < MAX_CHILDREN; ++i)
        node->children[i] = NULL;

    for (int i = 0; i < MAX_KEYS; ++i)
        node->keys[i] = 0;

    node->keys_count = 0;
    node->is_leaf = true;
    node->parent = NULL;
    return node;
}

void insertNotFull(B_node* node, int value) {
    if (!node) return;

    int pos = node->keys_count - 1;

    if (node->is_leaf) {
        while (pos >= 0 && node->keys[pos] > value) {
            node->keys[pos + 1] = node->keys[pos];
            pos--;
        }
        node->keys[pos + 1] = value;
        node->keys_count++;
    }
    else {
        while (pos >= 0 && node->keys[pos] > value)
            pos--;

        pos++;

        if (pos >= 0 && pos < MAX_CHILDREN && node->children[pos]) {
            if (node->children[pos]->keys_count == MAX_KEYS) {
                (*SplitFPtr)(node, pos);
                if (value > node->keys[pos]) pos++;
            }

            if (pos >= 0 && pos < MAX_CHILDREN && node->children[pos])
                (*InsertNotFullPtr)(node->children[pos], value);
        }
    }
}

void split(B_node* parent, int index) {
    if (!parent || index < 0 || index >= MAX_CHILDREN)
        return;

    B_node* child = parent->children[index];
    if (!child) return;

    B_node* right = create_node();
    if (!right) return;

    right->is_leaf = child->is_leaf;
    right->parent = parent;
    right->keys_count = T - 1;

    for (int i = 0; i < T - 1; ++i)
        right->keys[i] = child->keys[i + T];

    if (!child->is_leaf) {
        for (int i = 0; i < T; ++i) {
            right->children[i] = child->children[i + T];
            if (right->children[i])
                right->children[i]->parent = right;
        }
    }

    child->keys_count = T - 1;

    for (int i = parent->keys_count; i > index; --i) {
        parent->keys[i] = parent->keys[i - 1];
        parent->children[i + 1] = parent->children[i];
    }

    parent->keys[index] = child->keys[T - 1];
    parent->children[index + 1] = right;
    parent->keys_count++;
}

void Insert(B_tree* tree, int key) {
    if (!tree) return;

    if (Search(tree, key) == EXISTS) return;

    if (!tree->root) {
        tree->root = create_node();
        if (!tree->root) return;
        tree->root->keys[0] = key;
        tree->root->keys_count = 1;
        return;
    }

    if (tree->root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node();
        if (!new_root) return;

        new_root->is_leaf = false;
        new_root->children[0] = tree->root;
        tree->root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, key);
    }
    else {
        (*InsertNotFullPtr)(tree->root, key);
    }
}

B_search_result Search(B_tree* tree, int key) {
    if (!tree || !tree->root) return MISSING;

    B_node* current = tree->root;
    while (current) {
        int pos = 0;
        while (pos < current->keys_count && key > current->keys[pos])
            pos++;

        if (pos < current->keys_count && key == current->keys[pos])
            return EXISTS;

        if (current->is_leaf) break;

        if (pos >= 0 && pos < MAX_CHILDREN)
            current = current->children[pos];
        else
            break;
    }
    return MISSING;
}

void Free(B_tree* tree) {
    if (!tree || !tree->root) return;

    size_t stack_size = 0;
    size_t max_stack_size = 16;

    B_node** stack = (B_node**)malloc(sizeof(B_node*) * max_stack_size);
    if (!stack) return;

    stack[stack_size++] = tree->root;

    while (stack_size > 0) {
        B_node* node = stack[--stack_size];

        if (!node->is_leaf) {
            for (int i = 0; i <= node->keys_count; i++) {
                if (node->children[i]) {
                    if (stack_size == max_stack_size) {
                        max_stack_size *= 2;
                        B_node** tmp = (B_node**)realloc(stack, sizeof(B_node*) * max_stack_size);
                        if (!tmp) {
                            free(stack);
                            return;
                        }
                        stack = tmp;
                    }
                    stack[stack_size++] = node->children[i];
                }
            }
        }
        free(node);
    }

    free(stack);
    tree->root = NULL;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator it = { NULL, -1 };
    if (!tree || !tree->root || tree->root->keys_count == 0)
        return it;

    B_node* curr = tree->root;
    while (!curr->is_leaf && curr->children[0])
        curr = curr->children[0];

    it.node = curr;
    it.position = -1;
    return it;
}

int Next(B_tree_iterator* it) {
    if (!it || !it->node) return 0;

    B_node* node = it->node;
    int pos = it->position;

    if (node->is_leaf) {
        if (pos + 1 < node->keys_count) {
            it->position++;
            return 1;
        }

        while (node->parent) {
            int idx = 0;
            while (idx <= node->parent->keys_count && node->parent->children[idx] != node)
                idx++;

            if (idx < node->parent->keys_count) {
                it->node = node->parent;
                it->position = idx;
                return 1;
            }
            node = node->parent;
        }
    }
    else {
        if (pos == -1) {
            B_node* leftmost = node->children[0];
            while (!leftmost->is_leaf)
                leftmost = leftmost->children[0];

            it->node = leftmost;
            it->position = 0;
            return 1;
        }

        B_node* next_child = node->children[pos + 1];
        if (next_child) {
            while (!next_child->is_leaf)
                next_child = next_child->children[0];

            it->node = next_child;
            it->position = 0;
            return 1;
        }
    }

    it->node = NULL;
    it->position = -1;
    return 0;
}

int Key(B_tree_iterator* it) {
    if (!it || !it->node || it->position < 0 || it->position >= it->node->keys_count)
        return 0;
    return it->node->keys[it->position];
}