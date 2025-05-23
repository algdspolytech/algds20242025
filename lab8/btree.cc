#include "btree.h"
#include <stdlib.h>
#include <string.h>

extern split_t const *SplitFPtr;
extern insertNotFull_t const *InsertNotFullPtr;

static B_node* create_node(void) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (!node) return NULL;
    
    memset(node->children, 0, sizeof(node->children));
    memset(node->keys, 0, sizeof(node->keys));
    node->keys_count = 0;
    node->is_leaf = true;
    node->parent = NULL;
    return node;
}

void split(B_node* parent_of_splited, int split_at_index) {
    if (!parent_of_splited || split_at_index < 0 || split_at_index >= MAX_CHILDREN) {
        return;
    }

    B_node* full_node = parent_of_splited->children[split_at_index];
    if (!full_node) return;

    B_node* new_node = create_node();
    if (!new_node) return;
    
    new_node->is_leaf = full_node->is_leaf;
    new_node->parent = parent_of_splited;
    
    int mid = T - 1;
    new_node->keys_count = T - 1;
    
    for (int i = 0; i < T - 1; i++) {
        new_node->keys[i] = full_node->keys[T + i];
    }
    
    if (!full_node->is_leaf) {
        for (int i = 0; i < T; i++) {
            new_node->children[i] = full_node->children[T + i];
            if (new_node->children[i]) {
                new_node->children[i]->parent = new_node;
            }
        }
    }
    
    full_node->keys_count = T - 1;
    
    for (int i = parent_of_splited->keys_count; i > split_at_index; i--) {
        parent_of_splited->keys[i] = parent_of_splited->keys[i - 1];
        parent_of_splited->children[i + 1] = parent_of_splited->children[i];
    }
    
    parent_of_splited->keys[split_at_index] = full_node->keys[mid];
    parent_of_splited->children[split_at_index + 1] = new_node;
    parent_of_splited->keys_count++;
}

void insertNotFull(B_node* node, int data) {
    if (!node) return;

    int i = node->keys_count - 1;
    
    if (node->is_leaf) {
        while (i >= 0 && node->keys[i] > data) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = data;
        node->keys_count++;
    } else {
        while (i >= 0 && node->keys[i] > data) {
            i--;
        }
        i++;
        
        if (i >= 0 && i < MAX_CHILDREN && node->children[i]) {
            if (node->children[i]->keys_count == MAX_KEYS) {
                (*SplitFPtr)(node, i);
                if (data > node->keys[i]) {
                    i++;
                }
            }
            if (i >= 0 && i < MAX_CHILDREN && node->children[i]) {
                (*InsertNotFullPtr)(node->children[i], data);
            }
        }
    }
}

void Insert(B_tree* tree, int data) {
    if (!tree) return;

    if (Search(tree, data) == EXISTS) {
        return;
    }
    
    if (!tree->root) {
        tree->root = create_node();
        if (!tree->root) return;
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }
    
    B_node* root = tree->root;
    if (root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node();
        if (!new_root) return;
        new_root->is_leaf = false;
        new_root->children[0] = root;
        root->parent = new_root;
        tree->root = new_root;
        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, data);
    } else {
        (*InsertNotFullPtr)(root, data);
    }
}

B_search_result Search(B_tree* tree, int data) {
    if (!tree || !tree->root) return MISSING;
    
    B_node* current = tree->root;
    while (current) {
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
        
        if (i >= 0 && i < MAX_CHILDREN) {
            current = current->children[i];
        } else {
            return MISSING;
        }
    }
    return MISSING;
}

void Free(B_tree* tree) {
    if (!tree || !tree->root) return;
    
    size_t capacity = 16;
    size_t stack_size = 0;
    B_node** stack = (B_node**)malloc(sizeof(B_node*) * capacity);
    if (!stack) return;
    
    stack[stack_size++] = tree->root;
    
    while (stack_size > 0) {
        B_node* current = stack[--stack_size];
        
        if (!current->is_leaf) {
            for (int i = 0; i <= current->keys_count; i++) {
                if (current->children[i]) {
                    if (stack_size == capacity) {
                        capacity *= 2;
                        B_node** new_stack = (B_node**)realloc(stack, sizeof(B_node*) * capacity);
                        if (!new_stack) {
                            free(stack);
                            return;
                        }
                        stack = new_stack;
                    }
                    stack[stack_size++] = current->children[i];
                }
            }
        }
        free(current);
    }
    
    free(stack);
    tree->root = NULL;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = {NULL, -1};
    if (!tree || !tree->root || tree->root->keys_count == 0) {
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
    if (!iter || !iter->node) return 0;
    
    B_node* current = iter->node;
    int pos = iter->position;
    
    if (current->is_leaf) {
        if (pos + 1 < current->keys_count) {
            iter->position++;
            return 1;
        }
        
        while (current->parent) {
            int child_idx = 0;
            while (child_idx <= current->parent->keys_count && 
                   current->parent->children[child_idx] != current) {
                child_idx++;
            }
            
            if (child_idx < current->parent->keys_count) {
                iter->node = current->parent;
                iter->position = child_idx;
                return 1;
            }
            
            current = current->parent;
        }
        
        iter->node = NULL;
        iter->position = -1;
        return 0;
    }
    
    if (pos == -1) {
        B_node* child = current->children[0];
        while (!child->is_leaf) {
            child = child->children[0];
        }
        iter->node = child;
        iter->position = 0;
        return 1;
    }
    
    B_node* next_child = current->children[pos + 1];
    if (next_child) {
        while (!next_child->is_leaf) {
            next_child = next_child->children[0];
        }
        iter->node = next_child;
        iter->position = 0;
        return 1;
    }
    
    iter->node = NULL;
    iter->position = -1;
    return 0;
}

int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position < 0 || iter->position >= iter->node->keys_count) {
        return 0;
    }
    return iter->node->keys[iter->position];
} 