#include <stdlib.h>
#include <stdbool.h>
#include "btree.h"

static B_node* create_node(bool is_leaf) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (node) {
        node->keys_count = 0;
        node->is_leaf = is_leaf;
        node->parent = NULL;
        for (int i = 0; i < MAX_CHILDREN; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

static int find_key_index(B_node* node, int key) {
    int i = 0;
    while (i < node->keys_count && key > node->keys[i]) {
        i++;
    }
    return i;
}

static void insert_key_to_node(B_node* node, int key) {
    int i = node->keys_count - 1;

    while (i >= 0 && key < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }

    node->keys[i + 1] = key;
    node->keys_count++;
}

static B_node* search_node(B_node* node, int key, int* position) {
    int i = find_key_index(node, key);

    if (i < node->keys_count && key == node->keys[i]) {
        *position = i;
        return node;
    }

    if (node->is_leaf) {
        return NULL;
    }

    return search_node(node->children[i], key, position);
}

void split(B_node* parent_of_splited, int split_at_index) {
    B_node* full_node = parent_of_splited->children[split_at_index];
    B_node* new_node = create_node(full_node->is_leaf);
    new_node->parent = parent_of_splited;

    int median = full_node->keys[T - 1];

    new_node->keys_count = T - 1;
    for (int i = 0; i < T - 1; i++) {
        new_node->keys[i] = full_node->keys[i + T];
    }

    if (!full_node->is_leaf) {
        for (int i = 0; i < T; i++) {
            new_node->children[i] = full_node->children[i + T];
            if (new_node->children[i]) {
                new_node->children[i]->parent = new_node;
            }
        }
    }

    full_node->keys_count = T - 1;

    for (int i = parent_of_splited->keys_count; i > split_at_index; i--) {
        parent_of_splited->children[i + 1] = parent_of_splited->children[i];
    }
    parent_of_splited->children[split_at_index + 1] = new_node;

    insert_key_to_node(parent_of_splited, median);
}

void insertNotFull(B_node* node, int data) {
    int i = node->keys_count - 1;

    if (node->is_leaf) {
        insert_key_to_node(node, data);
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
    if (tree->root == NULL) {
        tree->root = create_node(true);
        insert_key_to_node(tree->root, data);
        return;
    }

    int pos;
    if (search_node(tree->root, data, &pos)) {
        return;
    }

    if (tree->root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false);
        new_root->children[0] = tree->root;
        tree->root->parent = new_root;
        tree->root = new_root;
        (*SplitFPtr)(new_root, 0);
    }

    (*InsertNotFullPtr)(tree->root, data);
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

void free_node(B_node* node) {
    if (node == NULL) {
        return;
    }

    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            free_node(node->children[i]);
        }
    }

    free(node);
}

void Free(B_tree* tree) {
    free_node(tree->root);
    tree->root = NULL;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { NULL, -1 };

    if (!(tree && tree->root)) {
        return iter;
    }
    B_node* node = tree->root;
    while (!node->is_leaf) {
        node = node->children[0];
    }
    iter.node = node;
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

int Key(B_tree_iterator* iter) {
    if (iter->node == NULL) {
        return 0;
    }
    return iter->node->keys[iter->position];
}