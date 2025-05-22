#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "b_tree.h" // Assuming your header file is named b_tree.h

// Helper function to create a new B_node
static B_node* create_node(bool is_leaf, B_node *parent) {
    B_node *new_node = (B_node*)malloc(sizeof(B_node));
    if (!new_node) {
        perror("Failed to allocate B_node");
        // In a real application, more robust error handling might be needed
        exit(EXIT_FAILURE);
    }
    new_node->is_leaf = is_leaf;
    new_node->keys_count = 0;
    new_node->parent = parent;
    // Initialize children pointers to NULL
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        new_node->children[i] = NULL;
    }
    // Keys array doesn't strictly need initialization if keys_count is managed correctly
    return new_node;
}

// Recursive helper for Search
static B_node* search_node_recursive(B_node *node, int data) {
    if (!node) {
        return NULL;
    }

    int i = 0;
    // Find the first key greater than or equal to data, or end of keys
    while (i < node->keys_count && data > node->keys[i]) {
        i++;
    }

    // If data is found at index i in this node
    if (i < node->keys_count && data == node->keys[i]) {
        return node; // Key found
    }

    // If node is a leaf and key not found
    if (node->is_leaf) {
        return NULL; // Key not found, and nowhere else to go
    }

    // Go to the appropriate child (children[i])
    return search_node_recursive(node->children[i], data);
}

B_search_result Search(B_tree *tree, int data) {
    if (tree == NULL || tree->root == NULL) {
        return MISSING;
    }
    if (search_node_recursive(tree->root, data) != NULL) {
        return EXISTS;
    }
    return MISSING;
}

void split(B_node *parent_node, int child_index_to_split) {
    // child_to_split is the full child of parent_node at child_index_to_split
    B_node *child_to_split = parent_node->children[child_index_to_split];
    // new_sibling will store (T-1) keys from child_to_split
    B_node *new_sibling = create_node(child_to_split->is_leaf, parent_node);
    new_sibling->keys_count = T - 1;

    // Copy the (T-1) largest keys from child_to_split to new_sibling
    for (int j = 0; j < T - 1; j++) {
        new_sibling->keys[j] = child_to_split->keys[j + T];
    }

    // If child_to_split is an internal node, copy its last T children to new_sibling
    if (!child_to_split->is_leaf) {
        for (int j = 0; j < T; j++) {
            new_sibling->children[j] = child_to_split->children[j + T];
            if (new_sibling->children[j] != NULL) {
                new_sibling->children[j]->parent = new_sibling; // Update parent of moved children
            }
        }
    }

    // child_to_split now has (T-1) keys
    child_to_split->keys_count = T - 1;

    // Shift children in parent_node to make space for new_sibling
    for (int j = parent_node->keys_count; j >= child_index_to_split + 1; j--) {
        parent_node->children[j + 1] = parent_node->children[j];
    }
    // Link new_sibling as a child of parent_node
    parent_node->children[child_index_to_split + 1] = new_sibling;

    // Shift keys in parent_node to make space for the middle key from child_to_split
    for (int j = parent_node->keys_count - 1; j >= child_index_to_split; j--) {
        parent_node->keys[j + 1] = parent_node->keys[j];
    }
    // Move the median key of child_to_split up to parent_node
    parent_node->keys[child_index_to_split] = child_to_split->keys[T - 1];

    parent_node->keys_count++;
}

void insertNotFull(B_node *node, int data) {
    int i = node->keys_count - 1; // Start from the rightmost key

    if (node->is_leaf) {
        // Find the position to insert data and shift keys greater than data to the right
        while (i >= 0 && data < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        // Insert data at the correct position
        node->keys[i + 1] = data;
        node->keys_count++;
    } else {
        // Find the child where the new key should be inserted
        while (i >= 0 && data < node->keys[i]) {
            i--;
        }
        // i is now the index of the key just less than data, or -1 if data is smaller than all keys.
        // The child to descend into is children[i+1].
        i++;

        // If the found child is full, split it
        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i); // Call split via function pointer
            // After split, the median key from children[i] moved up to node->keys[i].
            // Determine which of the two new children data should go into.
            if (data > node->keys[i]) {
                i++; // Data goes into the new right child (which is now at index i)
            }
        }
        (*InsertNotFullPtr)(node->children[i], data); // Call insertNotFull recursively via function pointer
    }
}

void Insert(B_tree *tree, int data) {
    if (tree == NULL) {
        // Or handle error appropriately, e.g. fprintf(stderr, "Tree pointer is NULL\n");
        return;
    }

    // If key already exists, do nothing
    if (Search(tree, data) == EXISTS) {
        return;
    }

    B_node *root = tree->root;
    if (root == NULL) {
        // Tree is empty, create a new root
        tree->root = create_node(true, NULL);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
    } else {
        if (root->keys_count == MAX_KEYS) {
            // Root is full, tree grows in height
            B_node *new_root = create_node(false, NULL); // New root is internal
            tree->root = new_root;
            new_root->children[0] = root; // Old root becomes child of new root
            root->parent = new_root;    // Update parent of old root

            (*SplitFPtr)(new_root, 0); // Split the old root (now child 0 of new_root)

            // New root now has one key and two children.
            // Decide which child of new_root to insert data into.
            int child_idx_for_insert = 0;
            if (new_root->keys[0] < data) { // Compare with the key promoted to new_root
                child_idx_for_insert = 1;
            }
            (*InsertNotFullPtr)(new_root->children[child_idx_for_insert], data);
        } else {
            // Root is not full, insert into root's subtree
            (*InsertNotFullPtr)(root, data);
        }
    }
}

// Recursive helper to free nodes
static void free_node_recursive(B_node *node) {
    if (node == NULL) {
        return;
    }
    // Recursively free children if it's an internal node
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) { // A node with k keys has k+1 children
            free_node_recursive(node->children[i]);
        }
    }
    // Free the node itself
    free(node);
}

void Free(B_tree *tree) {
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    free_node_recursive(tree->root);
    tree->root = NULL;
}

B_tree_iterator IteratorBegin(B_tree *tree) {
    B_tree_iterator iter;
    if (tree == NULL) { // Handle NULL tree explicitly
        iter.node = NULL;
        iter.position = -1;
        return iter;
    }
    // For the loop `while(Next(&iter)){ Key() }`, IteratorBegin should set up
    // the iterator so that the first call to Next() positions it at the first element.
    // A common way is to set node to root and position to a special "before first" marker.
    iter.node = tree->root;
    iter.position = -1;     // Indicates "before the first element" or "needs initialization by Next"
    return iter;
}

int Next(B_tree_iterator *iter) {
    if (iter == NULL) return 0;
    // If node is NULL from start (empty tree from Begin) or after traversal end
    if (iter->node == NULL && iter->position == -1) {
        // This handles empty tree case from IteratorBegin or if root was NULL
        return 0;
    }


    B_node *current_node = iter->node;
    int current_position = iter->position;

    // Case 0: Initial call to Next after IteratorBegin (position is -1)
    if (current_position == -1) {
        if (current_node == NULL) return 0; // Empty tree, iter->node was NULL from Begin

        // Find the very first element (leftmost leaf, first key)
        B_node *n = current_node; // Should be root if tree is not empty
        while (!n->is_leaf) {
            // Ensure there's a child to go to; protects against malformed/empty internal nodes
            if (n->children[0] == NULL) {
                iter->node = NULL; // Cannot proceed
                return 0;
            }
            n = n->children[0];
        }
        iter->node = n;
        iter->position = 0;
        // If the leftmost leaf is empty (shouldn't happen in a valid, non-empty B-tree)
        if (iter->node->keys_count == 0) {
            iter->node = NULL; // No elements
            return 0;
        }
        return 1; // Positioned at the first element
    }

    // If current_node became NULL by some other means (e.g. tree modified during iteration - not handled here)
    if (current_node == NULL) return 0;


    // Case 1: Current node is an internal node.
    // The next element is the leftmost element in the subtree rooted at children[current_position + 1].
    if (!current_node->is_leaf) {
        if (current_position + 1 > current_node->keys_count || current_node->children[current_position + 1] == NULL) {
            // This implies we are at the rightmost key of an internal node, and there's no child subtree to its right,
            // or tree structure is inconsistent. For a valid B-tree, this path should lead to ascent.
            // However, the logic for internal nodes expects a child C[k+1] after key K[k].
            // Let's refine: this means we already "visited" key K[k], next is in child C[k+1].
             iter->node = NULL; // Should not happen if logic is correct before this point
             return 0;
        }
        B_node *next_subtree_root = current_node->children[current_position + 1];
        while (!next_subtree_root->is_leaf) {
             if (next_subtree_root->children[0] == NULL) { // Protection
                iter->node = NULL; return 0;
            }
            next_subtree_root = next_subtree_root->children[0];
        }
        iter->node = next_subtree_root;
        iter->position = 0;
        if(iter->node->keys_count == 0){ // Leftmost leaf found is empty.
            // This implies an issue or an empty part of tree. Try to ascend as if leaf end.
             B_node *p_node = iter->node; // The empty leaf
             B_node *parent = iter->node->parent;
             // Fall into ascent logic from Case 2 below.
             // For simplicity here, we'll assume non-empty leaves if found this way.
             // If this is hit, it means the tree might be empty or malformed.
             // To correctly handle, it would need to re-trigger ascent.
             // Given typical B-tree, keys_count > 0 for leaves unless tree is fully empty.
             // If it is 0, it means this path leads to no more elements.
             // A more robust way: if keys_count is 0, continue to the parent logic of Case 2.
             // For now, assume valid B-trees don't have empty leaves unless they are the root.
             iter->node = NULL; return 0;
        }
        return 1;
    }

    // Case 2: Current node is a leaf node.
    // Try to advance to the next key in the current leaf.
    current_position++;
    if (current_position < current_node->keys_count) {
        iter->position = current_position;
        return 1;
    } else {
        // Exhausted keys in this leaf. Need to ascend to find the next key.
        B_node *p_node = current_node;  // Start with the current leaf
        B_node *parent = current_node->parent;

        while (parent != NULL) {
            int child_idx = 0;
            // Find which child p_node was of parent
            while (child_idx <= parent->keys_count && parent->children[child_idx] != p_node) {
                child_idx++;
            }

            if (child_idx > parent->keys_count) { // Should not happen: p_node not found in parent's children
                iter->node = NULL; return 0; // Error state
            }

            if (child_idx < parent->keys_count) {
                // p_node was children[child_idx]. The next key is parent->keys[child_idx].
                iter->node = parent;
                iter->position = child_idx;
                return 1;
            } else { // p_node was children[parent->keys_count] (the rightmost child pointer)
                // We have processed all keys in parent associated with children up to and including p_node.
                // Continue ascending.
                p_node = parent;
                parent = parent->parent;
            }
        }
        // If loop finishes, parent is NULL. We've ascended past the root. No more elements.
        iter->node = NULL;
        iter->position = -1; // Mark as ended
        return 0;
    }
}

int Key(B_tree_iterator *iter) {
    // This function assumes iter is valid and points to an element,
    // as per the problem: "значение через Key уже не получить" if Next returns 0.
    // No extensive error check here based on that premise.
    if (iter == NULL || iter->node == NULL || iter->position < 0 || iter->position >= iter->node->keys_count) {
        // This case should ideally not be hit if the loop `while(Next()){ Key() }` is used
        // and Next behaves correctly.
        // Return a sentinel or handle error, though problem implies it won't be called.
        fprintf(stderr, "Error: Key() called on invalid iterator state.\n");
        return -1; // Placeholder for error
    }
    return iter->node->keys[iter->position];
}