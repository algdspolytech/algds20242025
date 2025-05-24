#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "btree.h"

B_node* create_node(bool is_leaf, B_node* parent) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (!node) {
        return NULL;
    }

    node->keys_count = 0;
    node->is_leaf = is_leaf;
    node->parent = parent;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }

    return node;
}

static void free_node(B_node* node) {
    if (node ==NULL) return;

    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            free_node(node->children[i]);
        }
    }

    free(node);
}

void Free(B_tree* tree) {
    if (!tree || !tree->root) return;
    free_node(tree->root);
    tree->root = NULL;
}

B_search_result Search(B_tree* tree, int data) {
    if (!tree || !tree->root) return MISSING;

    B_node* current = tree->root;
    while (current!=NULL) {
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
    B_node* child = parent_of_splited->children[split_at_index];
    B_node* new_child = create_node(child->is_leaf, parent_of_splited);
    if (!new_child) return;

    new_child->parent = parent_of_splited;
   

    for (int i = 0; i < MIN_CHILDREN; i++) {
        new_child->keys[i] = child->keys[T + i];
    }
    new_child->keys_count = MIN_CHILDREN;
    if (!child->is_leaf) {
        for (int i = 0; i <= MIN_CHILDREN; i++) {
            new_child->children[i] = child->children[T + i];
            if (new_child->children[i]) {
                new_child->children[i]->parent = new_child;
            }
        }
    }
    child->keys_count = MIN_CHILDREN;

    for (int i = parent_of_splited->keys_count; i>= split_at_index+1; i--) {
        parent_of_splited->children[i + 1] = parent_of_splited->children[i];
    }
    parent_of_splited->children[split_at_index + 1] = new_child;

    for (int i = parent_of_splited->keys_count - 1; i >= split_at_index; i--) {
        parent_of_splited->keys[i + 1] = parent_of_splited->keys[i];
    }
    parent_of_splited->keys[split_at_index] = child->keys[MIN_CHILDREN];
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
    if (!tree) return;

    if (!tree->root) {
        tree->root = create_node(true, NULL);
        if (!tree->root) return;
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    if (Search(tree, data) == EXISTS) {
        return;
    }
    B_node* root = tree->root;
    if (tree->root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false, NULL);
        if (!new_root) return;

        new_root->children[0] = root;
        root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        int child_index = 0;
        if (data > new_root->keys[0]) {
            child_index = 1;
        }
        (*InsertNotFullPtr)(new_root->children[child_index], data);
    }
    else
    {
        (*InsertNotFullPtr)(root, data);
    }
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { NULL, -1 };
    if (!tree || !tree->root) { 
        iter.node = NULL;
        iter.position = -1;
        return iter;
    }

    B_node* current = tree->root;
    while (!current->is_leaf) {
        if (!current->children[0]) break;
        current = current->children[0];
    }

    iter.node = current;
    iter.position = -1;
    return iter;
}

int Next(B_tree_iterator* iter) {
    if (!iter) return 0;
    if (!iter->node && iter->position == -1) return 0;
    if (iter->position == -1) {
        B_node* current = iter->node;
        if (!current) return 0;
        while (!current->is_leaf) {
            if (!current->children[0]) {
                iter->node = NULL;
                return 0;
            }
            current = current->children[0];
        }
        iter->node = current;
        if (current->keys_count == 0) {
            iter->node = NULL;
            return 0;
        }
        iter->position = 0;
        return 1;
    }
    if (!iter->node->is_leaf) {
        B_node* subtree = iter->node->children[iter->position + 1];
        if (!subtree) {
            iter->node = NULL;
            return 0;
        }
        while (!subtree->is_leaf) {
            if (!subtree->children[0]) {
                iter->node = NULL;
                return 0;
            }
            subtree = subtree->children[0];
        }
        iter->node = subtree;
        if (iter->node->keys_count == 0) {
            iter->node = NULL;
            return 0;
        }
        iter->position = 0;
        return 1;
    }
    iter->position++;
    if (iter->position < iter->node->keys_count) return 1;
    else {
        B_node* current_child = iter->node;
        while (true) {
            B_node* parent = current_child->parent;
            if (parent == NULL) {
                iter->node = NULL;
                iter->position = -1;
                return 0;
            }

            int child_i = 0;
            while (child_i <= parent->keys_count && parent->children[child_i] != current_child) {
                child_i++;
            }

            if (child_i > parent->keys_count) {

                iter->node = NULL; return 0;
            }

            if (child_i < parent->keys_count) {
                iter->node = parent;
                iter->position = child_i;
                return 1;
            }
            else {
                current_child = parent;
            }
        }
    }
}

int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position < 0 || iter->position >= iter->node->keys_count) {
        return -1;
    }
    return iter->node->keys[iter->position];
}
