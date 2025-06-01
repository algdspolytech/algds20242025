#include "btree.h"
#include <stdlib.h>
#include <stdbool.h>
#ifdef MY_DEBUG_PRINT
#include <stdio.h>
#endif
static B_node* create_b_node(bool is_leaf, B_node* parent) {
    B_node* new_node = (B_node*)malloc(sizeof(B_node));
    if (!new_node) {
#ifdef MY_DEBUG_PRINT
        fprintf(stderr, "Error: Memory allocation failed for B_node.\n");
#endif
        return NULL;
    }
    new_node->is_leaf = is_leaf;
    new_node->keys_count = 0;
    new_node->parent = parent;
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        new_node->children[i] = NULL;
    }
    return new_node;
}
static void free_b_node_recursive(B_node* node) {
    if (node == NULL) {
        return;
    }
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i) {
            if (node->children[i] != NULL) {
                free_b_node_recursive(node->children[i]);
            }
        }
    }
    free(node);
}

void Free(B_tree* tree) {
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    free_b_node_recursive(tree->root);
    tree->root = NULL;
}

B_search_result Search(B_tree* tree, int data) {
    if (tree == NULL || tree->root == NULL) {
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
    B_node* child_to_split = parent_of_splited->children[split_at_index];
    B_node* new_sibling = create_b_node(child_to_split->is_leaf, parent_of_splited);

    if (!new_sibling) {
#ifdef MY_DEBUG_PRINT
        fprintf(stderr, "split: Failed to allocate new_sibling node.\n");
#endif
        return;
    }

    new_sibling->keys_count = T - 1;
    for (int j = 0; j < T - 1; ++j) {
        new_sibling->keys[j] = child_to_split->keys[j + T];
    }

    if (!child_to_split->is_leaf) {
        for (int j = 0; j < T; ++j) {
            new_sibling->children[j] = child_to_split->children[j + T];
            if (new_sibling->children[j] != NULL) {
                new_sibling->children[j]->parent = new_sibling;
            }
        }
    }

    child_to_split->keys_count = T - 1;

    for (int j = parent_of_splited->keys_count; j >= split_at_index + 1; --j) {
        parent_of_splited->children[j + 1] = parent_of_splited->children[j];
    }
    parent_of_splited->children[split_at_index + 1] = new_sibling;

    for (int j = parent_of_splited->keys_count - 1; j >= split_at_index; --j) {
        parent_of_splited->keys[j + 1] = parent_of_splited->keys[j];
    }
    parent_of_splited->keys[split_at_index] = child_to_split->keys[T - 1];
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

    if (root_node == NULL) {
        tree->root = create_b_node(true, NULL);
        if (!tree->root) { return; }
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    if (root_node->keys_count == MAX_KEYS) {
        B_node* new_root = create_b_node(false, NULL);
        if (!new_root) { return; }

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

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter;
    if (tree == NULL || tree->root == NULL) {
        iter.node = NULL;
        iter.position = -1;
        return iter;
    }
    iter.node = tree->root;
    iter.position = -1;
    return iter;
}

int Next(B_tree_iterator* iter) {
    if (iter == NULL) return 0;
    if (iter->node == NULL && iter->position == -1) {
        return 0;
    }

    if (iter->position == -1) {
        B_node* current = iter->node;
        if (current == NULL) return 0;

        while (!current->is_leaf) {
            if (current->children[0] == NULL) {
#ifdef MY_DEBUG_PRINT
                fprintf(stderr, "Next (initial): Non-leaf node has NULL children[0]. Node keys: %d\n", current->keys_count);
#endif
                iter->node = NULL; return 0;
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
        B_node* subtree_root = iter->node->children[iter->position + 1];
        if (subtree_root == NULL) {
#ifdef MY_DEBUG_PRINT
            fprintf(stderr, "Next (from internal): Child pointer at children[%d+1] is NULL.\n", iter->position);
#endif
            iter->node = NULL; return 0;
        }

        while (!subtree_root->is_leaf) {
            if (subtree_root->children[0] == NULL) {
#ifdef MY_DEBUG_PRINT
                fprintf(stderr, "Next (descending internal): Non-leaf child has NULL children[0].\n");
#endif
                iter->node = NULL; return 0;
            }
            subtree_root = subtree_root->children[0];
        }
        iter->node = subtree_root;
        if (iter->node->keys_count == 0) {
#ifdef MY_DEBUG_PRINT
            fprintf(stderr, "Next (descended to leaf): Leaf has 0 keys. This is unexpected for T>=2 non-root leaf.\n");
#endif
            iter->node = NULL;
            return 0;
        }
        iter->position = 0;
        return 1;
    }

    iter->position++;
    if (iter->position < iter->node->keys_count) {
        return 1;
    }
    else {
        B_node* curr_child_node = iter->node;
        while (true) {
            B_node* parent_node = curr_child_node->parent;
            if (parent_node == NULL) {
                iter->node = NULL;
                iter->position = -1;
                return 0;
            }

            int child_idx = 0;
            while (child_idx <= parent_node->keys_count && parent_node->children[child_idx] != curr_child_node) {
                child_idx++;
            }

            if (child_idx > parent_node->keys_count) {
#ifdef MY_DEBUG_PRINT
                fprintf(stderr, "Next (ascending): Child not found in parent. Corrupted tree?\n");
#endif
                iter->node = NULL; return 0;
            }

            if (child_idx < parent_node->keys_count) {
                iter->node = parent_node;
                iter->position = child_idx;
                return 1;
            }
            else {
                curr_child_node = parent_node;
            }
        }
    }
}

int Key(B_tree_iterator* iter) {
    if (iter == NULL || iter->node == NULL || iter->position < 0 || iter->position >= iter->node->keys_count) {
#ifdef MY_DEBUG_PRINT
        fprintf(stderr, "Key() called on invalid iterator state.\n");
        if (iter && iter->node) {
            fprintf(stderr, "Node keys_count: %d, position: %d\n", iter->node->keys_count, iter->position);
        }
        else if (iter) {
            fprintf(stderr, "Node is NULL, position: %d\n", iter->position);
        }
#endif
        return -1;
    }
    return iter->node->keys[iter->position];
}