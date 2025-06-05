#include "btree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern split_t const *SplitFPtr;
extern insertNotFull_t const *InsertNotFullPtr;

static B_node *create_node(bool is_leaf, B_node *parent)
{
    B_node *new_node = (B_node *)malloc(sizeof(B_node));
    if (!new_node)
    {
#ifdef MY_DEBUG_PRINT
        fprintf(stderr, "Error: malloc failed in create_node\n");
#endif
        exit(1);
    }
    new_node->is_leaf = is_leaf;
    new_node->keys_count = 0;
    new_node->parent = parent;
    for (int i = 0; i < MAX_CHILDREN; ++i)
    {
        new_node->children[i] = NULL;
    }
    for (int i = 0; i < MAX_KEYS; ++i)
    {
        new_node->keys[i] = 0;
    }
    return new_node;
}

static void free_node_recursive(B_node *node)
{
    if (node == NULL)
    {
        return;
    }
    if (!node->is_leaf)
    {
        for (int i = 0; i <= node->keys_count; ++i)
        {
            free_node_recursive(node->children[i]);
        }
    }
    free(node);
}

void Free(B_tree *tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        return;
    }
    free_node_recursive(tree->root);
    tree->root = NULL;
}

void split(B_node *parent_of_splited, int split_at_index)
{
    B_node *y = parent_of_splited->children[split_at_index];
    B_node *z = create_node(y->is_leaf, parent_of_splited);
    z->keys_count = T - 1;

    for (int j = 0; j < T - 1; ++j)
    {
        z->keys[j] = y->keys[j + T];
    }

    if (!y->is_leaf)
    {
        for (int j = 0; j < T; ++j)
        {
            z->children[j] = y->children[j + T];
            if (z->children[j] != NULL)
            {
                z->children[j]->parent = z;
            }
        }
    }

    y->keys_count = T - 1;

    for (int j = parent_of_splited->keys_count; j >= split_at_index + 1; --j)
    {
        parent_of_splited->children[j + 1] = parent_of_splited->children[j];
    }
    parent_of_splited->children[split_at_index + 1] = z;

    for (int j = parent_of_splited->keys_count - 1; j >= split_at_index; --j)
    {
        parent_of_splited->keys[j + 1] = parent_of_splited->keys[j];
    }
    parent_of_splited->keys[split_at_index] = y->keys[T - 1];
    parent_of_splited->keys_count++;
}

void insertNotFull(B_node *node, int data)
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
        {
            i--;
        }
        i++;

        if (node->children[i]->keys_count == MAX_KEYS)
        {
            (*SplitFPtr)(node, i);
            if (data > node->keys[i])
            {
                i++;
            }
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

static B_search_result search_recursive(B_node *current_node, int data)
{
    if (current_node == NULL)
    {
        return MISSING;
    }

    int i = 0;
    while (i < current_node->keys_count && data > current_node->keys[i])
    {
        i++;
    }

    if (i < current_node->keys_count && data == current_node->keys[i])
    {
        return EXISTS;
    }

    if (current_node->is_leaf)
    {
        return MISSING;
    }

    return search_recursive(current_node->children[i], data);
}

B_search_result Search(B_tree *tree, int data)
{
    if (tree == NULL || tree->root == NULL)
    {
        return MISSING;
    }
    return search_recursive(tree->root, data);
}

void Insert(B_tree *tree, int data)
{
    if (tree == NULL)
        return;

    if (Search(tree, data) == EXISTS)
    {
        return;
    }

    B_node *root_node = tree->root;

    if (root_node == NULL)
    {
        tree->root = create_node(true, NULL);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
    }
    else
    {
        if (root_node->keys_count == MAX_KEYS)
        {
            B_node *new_root = create_node(false, NULL);
            new_root->children[0] = root_node;
            root_node->parent = new_root;
            tree->root = new_root;

            (*SplitFPtr)(new_root, 0);
            (*InsertNotFullPtr)(new_root, data);
        }
        else
        {
            (*InsertNotFullPtr)(root_node, data);
        }
    }
}

B_tree_iterator IteratorBegin(B_tree *tree)
{
    B_tree_iterator iter;
    iter.node = tree->root;
    iter.position = -1;
    return iter;
}

int Next(B_tree_iterator *iter)
{
    if (iter == NULL)
        return 0;
    if (iter->node == NULL && iter->position != -1)
        return 0;

    if (iter->position == -1)
    {
        B_node *current = iter->node;
        if (!current)
            return 0;

        while (current != NULL && !current->is_leaf)
        {
            if (current->keys_count == 0)
            {
                current = current->children[0];
            }
            else
            {
                current = current->children[0];
            }
        }

        iter->node = current;
        if (iter->node == NULL || iter->node->keys_count == 0)
        {
            iter->node = NULL;
            iter->position = 0;
            return 0;
        }
        iter->position = 0;
        return 1;
    }

    if (!iter->node->is_leaf && (iter->position + 1) <= iter->node->keys_count)
    {
        B_node *nextNodeInSubtree = iter->node->children[iter->position + 1];
        while (nextNodeInSubtree != NULL && !nextNodeInSubtree->is_leaf)
        {
            nextNodeInSubtree = nextNodeInSubtree->children[0];
        }
        if (nextNodeInSubtree != NULL && nextNodeInSubtree->keys_count > 0)
        {
            iter->node = nextNodeInSubtree;
            iter->position = 0;
            return 1;
        }
    }

    if (iter->position + 1 < iter->node->keys_count)
    {
        iter->position++;
        return 1;
    }

    B_node *currentNode = iter->node;
    B_node *parentNode = currentNode->parent;

    while (parentNode != NULL)
    {
        int child_idx = 0;
        for (child_idx = 0; child_idx <= parentNode->keys_count; ++child_idx)
        {
            if (parentNode->children[child_idx] == currentNode)
            {
                break;
            }
        }

        if (child_idx > parentNode->keys_count)
        {
#ifdef MY_DEBUG_PRINT
            fprintf(stderr, "Iterator Next: Child not found in parent's children array.\n");
#endif
            iter->node = NULL;
            return 0;
        }

        if (child_idx < parentNode->keys_count)
        {
            iter->node = parentNode;
            iter->position = child_idx;
            return 1;
        }

        currentNode = parentNode;
        parentNode = parentNode->parent;
    }

    iter->node = NULL;
    iter->position = 0;
    return 0;
}

int Key(B_tree_iterator *iter)
{
    if (iter == NULL || iter->node == NULL || iter->position < 0 || iter->position >= iter->node->keys_count)
    {

#ifdef MY_DEBUG_PRINT
        fprintf(stderr, "Error: Key() called on invalid iterator state.\n");
#endif

        if (iter && iter->node && iter->node->keys_count > 0 && iter->position >= 0 && iter->position < iter->node->keys_count)
        {
            return iter->node->keys[iter->position];
        }
        return -1;
    }
    return iter->node->keys[iter->position];
}
