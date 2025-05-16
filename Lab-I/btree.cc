#include "btree.h"
#include <stdlib.h>

B_node* createNode(bool is_leaf, B_node* parent) {
    B_node* new_node = (B_node*)malloc(sizeof(B_node));
    if (!new_node) return NULL;
    new_node->is_leaf = is_leaf;
    new_node->keys_count = 0;
    new_node->parent = parent;
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        new_node->children[i] = NULL;
    }
    return new_node;
}

B_search_result Search(B_tree* tree, int data) {
    if (!(tree && tree->root)) {
        return MISSING;
    }

    B_node* current = tree->root;
    while (current != NULL) {
        int i = 0;
        while (i < current->keys_count && data > current->keys[i]) {
            i++;
        }
        if (i < current->keys_count && data == current->keys[i]) {
            return EXISTS;
        }
        if (current->is_leaf) {
            return MISSING;
        }
        current = current->children[i];
    }
    return MISSING;
}

void split(B_node* parent_of_splited, int split_at_index) {
    B_node* full = parent_of_splited->children[split_at_index];
    B_node* new_node = createNode(full->is_leaf, parent_of_splited);

    if (!new_node) return;

    new_node->keys_count = T - 1;
    for (int j = 0; j < T - 1; ++j) {
        new_node->keys[j] = full->keys[j + T];
    }

    if (!full->is_leaf) {
        for (int j = 0; j < T; ++j) {
            new_node->children[j] = full->children[j + T];
            if (new_node->children[j] != NULL) {
                new_node->children[j]->parent = new_node;
            }
        }
    }

    full->keys_count = T - 1;

    for (int j = parent_of_splited->keys_count; j >= split_at_index + 1; --j) {
        parent_of_splited->children[j + 1] = parent_of_splited->children[j];
    }
    parent_of_splited->children[split_at_index + 1] = new_node;

    for (int j = parent_of_splited->keys_count - 1; j >= split_at_index; --j) {
        parent_of_splited->keys[j + 1] = parent_of_splited->keys[j];
    }
    parent_of_splited->keys[split_at_index] = full->keys[T - 1];
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
    if (Search(tree, data) == EXISTS) {
        return;
    }

    B_node* root_node = tree->root;

    if (!root_node) {
        tree->root = createNode(true, NULL);
        if (!tree->root) { return; }
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    if (root_node->keys_count == MAX_KEYS) {
        B_node* new_root = createNode(false, NULL);
        if (!new_root) return;

        tree->root = new_root;
        new_root->children[0] = root_node;
        root_node->parent = new_root;

        (*SplitFPtr)(new_root, 0);

        int child_idx_to_insert = 0;
        if (data > new_root->keys[0]) {
            child_idx_to_insert = 1;
        }
        (*InsertNotFullPtr)(new_root->children[child_idx_to_insert], data);
    }
    else {
        (*InsertNotFullPtr)(root_node, data);
    }
}



void freeNodes(B_node* node) {
    if (!node) {
        return;
    }
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i) {
            if (node->children[i] != NULL) {
                freeNodes(node->children[i]);
            }
        }
    }
    free(node);
}

void Free(B_tree* tree) {
    if (!(tree && tree->root)) {
        return;
    }
    freeNodes(tree->root);
    tree->root = NULL;
}

int Key(B_tree_iterator* iter) {
    if (!(iter && iter->node) && iter->position < 0) return -1;
    return iter->node->keys[iter->position];
}


B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { NULL, -1 };

    if (!(tree && tree->root)) return iter;

    B_node* current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    iter.node = current;
    return iter;
}


int Next(B_tree_iterator* iter) {
    if (!(iter && iter->node)) return 0;

    B_node* node = iter->node;
    int position = iter->position;

    if (node->is_leaf) {

        if (position + 1 < node->keys_count) {
            iter->position++;
            return 1;
        }
    }
    else {

        if (position + 1 <= node->keys_count && node->children[position + 1]) {
            B_node* current = node->children[position + 1];
            while (!current->is_leaf) {
                current = current->children[0];
            }
            iter->node = current;
            iter->position = 0;
            return 1;
        }
    }

    B_node* current = node;
    while (current->parent) {
        B_node* parent = current->parent;

        int i = 0;
        while (i <= parent->keys_count && parent->children[i] != current) {
            i++;
        }

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