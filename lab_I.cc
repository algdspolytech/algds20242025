#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "btree.h"

B_node* CreateNode(B_node* parent, bool is_leaf) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (!node) {
        return NULL;
    }

    node->parent = parent;
    node->keys_count = 0;
    node->is_leaf = is_leaf;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }

    return node;
}

B_search_result Search(B_tree* tree, int data) {
    if (!tree || !tree->root) {
        return MISSING;
    }

    B_node* curNode = tree->root;

    while (curNode) {
        int i = 0;
        while (i < curNode->keys_count && data > curNode->keys[i]) {
            i++;
        }
        if (i < curNode->keys_count && data == curNode->keys[i]) {
            return EXISTS;
        }
        if (curNode->is_leaf) {
            return MISSING;
        }

        curNode = curNode->children[i];
    }

    return MISSING;
}

void split(B_node* parent_of_splited, int split_at_index) {
    B_node* child = parent_of_splited->children[split_at_index];
    B_node* newNode = CreateNode(parent_of_splited, true);

    int mid = T - 1;
    newNode->is_leaf = child->is_leaf;
    newNode->keys_count = mid;

    for (int i = 0; i < mid; i++) {
        newNode->keys[i] = child->keys[mid + 1 + i];
    }

    if (!child->is_leaf) {
        for (int i = 0; i < mid + 1; i++) {
            newNode->children[i] = child->children[mid + 1 + i];
            if (newNode->children[i]) {
                newNode->children[i]->parent = newNode;
            }
        }
    }

    child->keys_count = mid;

    for (int i = parent_of_splited->keys_count; i > split_at_index; i--) {
        parent_of_splited->keys[i] = parent_of_splited->keys[i - 1];
        parent_of_splited->children[i + 1] = parent_of_splited->children[i];
    }

    parent_of_splited->keys[split_at_index] = child->keys[mid];
    parent_of_splited->children[split_at_index + 1] = newNode;
    parent_of_splited->keys_count++;
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

void Insert(B_tree* tree, int data) {
    if (!SplitFPtr) {
        SplitFPtr = (split_t const*)(void*)&split;
    }
    if (!InsertNotFullPtr) {
        InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;
    }

    if (Search(tree, data) == EXISTS) {
        return;
    }

    if (!tree->root) {
        tree->root = CreateNode(NULL, true);
        (*InsertNotFullPtr)(tree->root, data);
        return;
    }

    if (tree->root->keys_count == MAX_KEYS) {
        B_node* new_root = CreateNode(NULL, false);
        new_root->children[0] = tree->root;
        tree->root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
    }

    B_node* current = tree->root;
    while (!current->is_leaf) {
        int i = 0;
        while (i < current->keys_count && data > current->keys[i]) {
            i++;
        }

        if (current->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(current, i);
            if (data > current->keys[i]) {
                i++;
            }
        }

        current = current->children[i];
    }

    (*InsertNotFullPtr)(current, data);
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
    if (!tree) return;

    if (tree->root) {
        FreeNode(tree->root);
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

    B_node* cur = tree->root;
    while (!cur->is_leaf) {
        cur = cur->children[0];
    }
    iter.node = cur;
    iter.position = -1;
    return iter;
}

int Next(B_tree_iterator* iter) {
    if (!iter->node)
        return 0;

    B_node* node = iter->node;
    int pos = iter->position;

    if (node->is_leaf) {
        if (pos + 1 < node->keys_count) {
            iter->position = pos + 1;
            return 1;
        }
    }
    else {
        if (pos + 1 <= node->keys_count && node->children[pos + 1]) {
            B_node* curNode = node->children[pos + 1];
            while (!curNode->is_leaf) {
                curNode = curNode->children[0];
            }
            iter->node = curNode;
            iter->position = 0;
            return 1;
        }
    }

    B_node* curNode = node;
    while (curNode->parent) {
        B_node* parentNode = curNode->parent;
        int i = 0;
        while (i <= parentNode->keys_count && parentNode->children[i] != curNode) {
            i++;
        }
        if (i < parentNode->keys_count) {
            iter->node = parentNode;
            iter->position = i;
            return 1;
        }
        curNode = parentNode;
    }

    iter->node = NULL;
    return 0;
}


int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position < 0 ||
        iter->position >= iter->node->keys_count) {
        return INT_MIN;
    }
    return iter->node->keys[iter->position];
}