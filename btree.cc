#include "btree.h"
#include <stdlib.h>

static B_node* createNode(bool is_leaf, B_node* parent) 
{
    B_node* node = (B_node*)malloc(sizeof(B_node));
    node->is_leaf = is_leaf;
    node->keys_count = 0;
    node->parent = parent;
    for (int i = 0; i < MAX_CHILDREN; ++i)
        node->children[i] = NULL;
    return node;
}

void Free(B_tree* tree) 
{
    if (!tree || !tree->root)
        return;

    B_node* root = tree->root;

    for (int i = 0; i <= root->keys_count; ++i) 
    {
        if (root->children[i]) 
        {
            B_tree temp_tree = { .root = root->children[i] };
            Free(&temp_tree);
        }
    }

    free(root);
    tree->root = NULL;
}


B_search_result Search(B_tree* tree, int data) 
{
    if (!tree || !tree->root)
        return MISSING;

    B_node* node = tree->root;
    while (node) 
    {
        int i = 0;
        while (i < node->keys_count && data > node->keys[i])
            i++;

        if (i < node->keys_count && data == node->keys[i])
            return EXISTS;

        if (node->is_leaf) 
        {
            return MISSING;
        }
        node = node->children[i];
    }
    return MISSING;
}

void split(B_node* parent, int index) 
{
    B_node* full = parent->children[index];
    B_node* right = createNode(full->is_leaf, parent);

    right->keys_count = MIN_CHILDREN;
    for (int i = 0; i < MIN_CHILDREN; ++i)
        right->keys[i] = full->keys[i + T];

    if (!full->is_leaf)
        for (int i = 0; i <= MIN_CHILDREN; ++i)
        {
            right->children[i] = full->children[i + T];
            if (right->children[i]) 
            {
                right->children[i]->parent = right;
            }
        }

    for (int i = parent->keys_count; i > index; --i) 
    {
        parent->children[i + 1] = parent->children[i];
    }

    for (int j = parent->keys_count - 1; j >= index; j--) 
    {
        parent->keys[j + 1] = parent->keys[j];
    }

    parent->children[index + 1] = right;
    parent->keys[index] = full->keys[MIN_CHILDREN];
    parent->keys_count++;

    full->keys_count = MIN_CHILDREN;
}

void insertNotFull(B_node* node, int data) 
{
    int i = node->keys_count - 1;

    if (node->is_leaf) 
    {
        while (i >= 0 && data < node->keys[i]) 
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = data;
        node->keys_count++;
    }
    else 
    {
        while (i >= 0 && data < node->keys[i])
            i--;
        i++;

        if (node->children[i]->keys_count == MAX_KEYS) 
        {
            (*SplitFPtr)(node, i);
            if (data > node->keys[i])
                i++;
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

void Insert(B_tree* tree, int data) 
{
    if (!tree->root) 
    {
        tree->root = createNode(true, NULL);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    if (Search(tree, data) == EXISTS)
        return;

    B_node* root = tree->root;

    if (root->keys_count == MAX_KEYS) 
    {
        B_node* newRoot = createNode(false, NULL);
        newRoot->children[0] = root;
        root->parent = newRoot;
        tree->root = newRoot;

        (*SplitFPtr)(newRoot, 0);
        (*InsertNotFullPtr)(newRoot, data);
    }
    else 
    {
        (*InsertNotFullPtr)(root, data);
    }
}

// ============================== ศาละภาฮะ ==============================

int Key(B_tree_iterator* iter) 
{
    if (!iter || !iter->node || iter->position < 0) return 0;
    return iter->node->keys[iter->position];
}

B_tree_iterator IteratorBegin(B_tree* tree) 
{
    B_tree_iterator iterator = { 0 };

    if (!tree->root) 
    {
        iterator.node = NULL;
        iterator.position = -1;
        return iterator;
    }

    B_node* current = tree->root;
    while (!current->is_leaf) 
    {
        current = current->children[0];
    }
    iterator.node = current;
    iterator.position = -1;
    return iterator;
}

int Next(B_tree_iterator* iterator) 
{
    if (!iterator->node) 
    {
        return 0;
    }

    B_node* current_node = iterator->node;
    int current_pos = iterator->position;

    if (current_node->is_leaf) 
    {
        if (current_pos + 1 < current_node->keys_count) 
        {
            iterator->position = current_pos + 1;
            return 1;
        }
    }
    else 
    {
        if (current_pos + 1 <= current_node->keys_count && current_node->children[current_pos + 1]) 
        {
            B_node* next_node = current_node->children[current_pos + 1];
            while (!next_node->is_leaf) 
            {
                next_node = next_node->children[0];
            }
            iterator->node = next_node;
            iterator->position = 0;
            return 1;
        }
    }

    B_node* node = current_node;
    while (node->parent) 
    {
        B_node* parent = node->parent;

        int idx = 0;
        while (idx <= parent->keys_count && parent->children[idx] != node) 
        {
            idx++;
        }

        if (idx < parent->keys_count) 
        {
            iterator->node = parent;
            iterator->position = idx;
            return 1;
        }

        node = parent;
    }

    iterator->node = NULL;
    return 0;
}