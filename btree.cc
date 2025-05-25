#include "btree.h"
#include <stdlib.h>
#include <stdbool.h>



static B_node* create_node(bool is_leaf) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (!node) return NULL;

    node->keys_count = 0;
    node->is_leaf = is_leaf;
    node->parent = NULL;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }

    return node;
}


static int find_key(B_node* node, int data) {
    int i = 0;
    while (i < node->keys_count && data > node->keys[i]) {
        i++;
    }
    return i;
}

B_search_result Search(B_tree* tree, int data) {
    if (!tree || !tree->root) return MISSING;

    B_node* current = tree->root;
    while (current) {
        int i = find_key(current, data);

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

void Insert(B_tree* tree, int data) {
    if (!tree) return;


    if (!tree->root) {
        tree->root = create_node(true);
        if (!tree->root) return;
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }


    if (tree->root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false);
        if (!new_root) return;

        new_root->children[0] = tree->root;
        tree->root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
    }


    (*InsertNotFullPtr)(tree->root, data);
}

void insertNotFull(B_node* node, int data) {
    if (!node) return;

    int i = node->keys_count - 1;

    if (node->is_leaf) {
        
        while (i >= 0 && data < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        
        if (i >= 0 && data == node->keys[i]) {
            return;
        }

        
        node->keys[i + 1] = data;
        node->keys_count++;
    }
    else {
        
        while (i >= 0 && data < node->keys[i]) {
            i--;
        }

       
        if (i >= 0 && data == node->keys[i]) {
            return;
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

void split(B_node* parent_of_splited, int split_at_index) {
    if (!parent_of_splited) return;

    B_node* full_node = parent_of_splited->children[split_at_index];
    B_node* new_node = create_node(full_node->is_leaf);
    if (!new_node) return;

    new_node->parent = parent_of_splited;

    
    int j = 0;
    for (int i = T; i < MAX_KEYS; i++) {
        new_node->keys[j++] = full_node->keys[i];
    }
    new_node->keys_count = MIN_CHILDREN;

    if (!full_node->is_leaf) {
        j = 0;
        for (int i = T; i < MAX_CHILDREN; i++) {
            new_node->children[j++] = full_node->children[i];
            if (full_node->children[i]) {
                full_node->children[i]->parent = new_node;
            }
        }
    }

    full_node->keys_count = MIN_CHILDREN;

    
    for (int i = parent_of_splited->keys_count; i > split_at_index; i--) {
        parent_of_splited->keys[i] = parent_of_splited->keys[i - 1];
        parent_of_splited->children[i + 1] = parent_of_splited->children[i];
    }

    
    parent_of_splited->keys[split_at_index] = full_node->keys[MIN_CHILDREN];
    parent_of_splited->children[split_at_index + 1] = new_node;
    parent_of_splited->keys_count++;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { NULL, 0 };
    if (!tree || !tree->root) return iter;

    
    B_node* current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }

    iter.node = current;
    iter.position = 0;
    return iter;
}

int Next(B_tree_iterator* iter) {
    if (!iter || !iter->node) return 0;

    
    if (iter->position + 1 < iter->node->keys_count) {
        iter->position++;
        return 1;
    }

    
    B_node* current = iter->node;
    int key = current->keys[iter->position];

    
    while (current->parent) {
        int pos = find_key(current->parent, key);

        if (pos < current->parent->keys_count) {
           
            current = current->parent->children[pos + 1];
            
            while (!current->is_leaf) {
                current = current->children[0];
            }
            iter->node = current;
            iter->position = 0;
            return 1;
        }

        current = current->parent;
    }

    
    iter->node = NULL;
    return 0;
}

int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position >= iter->node->keys_count) {
        return 0;
    }
    return iter->node->keys[iter->position];
}

static void free_node(B_node* node) {
    if (!node) return;

    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            free_node(node->children[i]);
        }
    }

    free(node);
}

void Free(B_tree* tree) {
    if (!tree) return;
    free_node(tree->root);
    tree->root = NULL;
}