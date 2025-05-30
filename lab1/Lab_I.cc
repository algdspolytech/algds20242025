#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

/* Helper function to initialize a new B-tree node */
static B_node* CreateNode(bool is_leaf_node, B_node* parent_node) {
    B_node* new_node = (B_node*)malloc(sizeof(B_node));
    if (new_node == NULL) return NULL;

    new_node->is_leaf = is_leaf_node;
    new_node->keys_count = 0;
    new_node->parent = parent_node;

    for (int i = 0; i < MAX_CHILDREN; ++i) {
        new_node->children[i] = NULL;
    }
    
    return new_node;
}

/* Search for a value in the B-tree */
B_search_result Search(B_tree* tree, int target_value) {
    B_node* current_node = (tree != NULL) ? tree->root : NULL;
    
    while (current_node != NULL) {
        int key_index = 0;
        
        /* Find the appropriate position in current node */
        while (key_index < current_node->keys_count) {
            if (target_value == current_node->keys[key_index]) {
                return EXISTS;
            }
            if (target_value < current_node->keys[key_index]) {
                break;
            }
            ++key_index;
        }
        
        if (current_node->is_leaf) {
            return MISSING;
        }
        
        current_node = current_node->children[key_index];
    }
    
    return MISSING;
}

/* Split a full child node */
void split(B_node* parent_node, int child_index) {
    B_node* child_node = parent_node->children[child_index];
    B_node* new_node = CreateNode(child_node->is_leaf, parent_node);
    if (new_node == NULL) return;

    /* Copy upper half of keys to new node */
    new_node->keys_count = MIN_CHILDREN;
    for (int i = 0; i < MIN_CHILDREN; ++i) {
        new_node->keys[i] = child_node->keys[i + T];
    }

    /* Copy upper half of children if not leaf */
    if (!child_node->is_leaf) {
        for (int i = 0; i <= MIN_CHILDREN; ++i) {
            new_node->children[i] = child_node->children[i + T];
            if (new_node->children[i] != NULL) {
                new_node->children[i]->parent = new_node;
            }
        }
    }

    child_node->keys_count = MIN_CHILDREN;

    /* Make space in parent for new child */
    for (int i = parent_node->keys_count; i > child_index; --i) {
        parent_node->children[i + 1] = parent_node->children[i];
        parent_node->keys[i] = parent_node->keys[i - 1];
    }

    parent_node->children[child_index + 1] = new_node;
    parent_node->keys[child_index] = child_node->keys[MIN_CHILDREN];
    ++parent_node->keys_count;
}

/* Insert into a non-full node */
void insertNotFull(B_node* node, int new_value) {
    if (node->is_leaf) {
        /* Find position and shift keys to make space */
        int insert_pos = node->keys_count++;
        while (insert_pos > 0 && new_value < node->keys[insert_pos - 1]) {
            node->keys[insert_pos] = node->keys[insert_pos - 1];
            --insert_pos;
        }
        node->keys[insert_pos] = new_value;
        return;
    }

    /* Find appropriate child for insertion */
    int child_pos = 0;
    while (child_pos < node->keys_count && new_value > node->keys[child_pos]) {
        ++child_pos;
    }

    B_node* child = node->children[child_pos];
    if (child->keys_count == MAX_KEYS) {
        (*SplitFPtr)(node, child_pos);
        if (new_value > node->keys[child_pos]) {
            ++child_pos;
        }
    }
    (*InsertNotFullPtr)(node->children[child_pos], new_value);
}

/* Main insertion function */
void Insert(B_tree* tree, int value) {
    /* Initialize function pointers if not set */
    if (SplitFPtr == NULL) SplitFPtr = (split_t const*)(void*)&split;
    if (InsertNotFullPtr == NULL) InsertNotFullPtr = (insertNotFull_t const*)(void*)&insertNotFull;

    /* Check if value already exists */
    if (Search(tree, value) == EXISTS) return;

    /* Handle empty tree case */
    if (tree->root == NULL) {
        tree->root = CreateNode(true, NULL);
        if (tree->root == NULL) return;
        tree->root->keys[0] = value;
        tree->root->keys_count = 1;
        return;
    }

    B_node* root_node = tree->root;
    
    /* Handle full root case */
    if (root_node->keys_count == MAX_KEYS) {
        B_node* new_root = CreateNode(false, NULL);
        if (new_root == NULL) return;

        new_root->children[0] = root_node;
        root_node->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, value);
    } else {
        (*InsertNotFullPtr)(root_node, value);
    }
}

/* Recursively free node memory */
void FreeNode(B_node* node) {
    if (node == NULL) return;

    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i) {
            FreeNode(node->children[i]);
        }
    }
    
    free(node);
}

/* Free entire tree */
void Free(B_tree* tree) {
    if (tree == NULL || tree->root == NULL) return;
    
    FreeNode(tree->root);
    tree->root = NULL;
}

/* Initialize iterator to first element */
B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator it = { NULL, -1 };
    if (tree == NULL || tree->root == NULL) return it;

    B_node* current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }

    it.node = current;
    it.position = -1;
    return it;
}

/* Move iterator to next element */
int Next(B_tree_iterator* iterator) {
    if (iterator == NULL || iterator->node == NULL) return 0;

    B_node* current = iterator->node;
    int next_pos = iterator->position + 1;

    /* Case 1: Current node has more keys */
    if (current->is_leaf && next_pos < current->keys_count) {
        iterator->position = next_pos;
        return 1;
    }

    /* Case 2: Need to move to child node */
    if (!current->is_leaf && next_pos <= current->keys_count) {
        B_node* next_node = current->children[next_pos];
        if (next_node != NULL) {
            while (!next_node->is_leaf) {
                next_node = next_node->children[0];
            }
            iterator->node = next_node;
            iterator->position = 0;
            return 1;
        }
    }

    /* Case 3: Need to move up the tree */
    while (current->parent != NULL) {
        B_node* parent = current->parent;
        int child_index = 0;
        
        /* Find our position in parent's children */
        while (child_index <= parent->keys_count) {
            if (parent->children[child_index] == current) break;
            ++child_index;
        }

        if (child_index < parent->keys_count) {
            iterator->node = parent;
            iterator->position = child_index;
            return 1;
        }
        
        current = parent;
    }

    /* No more elements */
    iterator->node = NULL;
    iterator->position = -1;
    return 0;
}

/* Get current key from iterator */
int Key(B_tree_iterator* iterator) {
    if (iterator == NULL || iterator->node == NULL || iterator->position < 0) {
        return 0;
    }
    return iterator->node->keys[iterator->position];
}