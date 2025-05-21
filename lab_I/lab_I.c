#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "btree.h"



void split(B_node* parent, int index);
void insertNotFull(B_node* node, int key);

extern split_t const * SplitFPtr;
extern insertNotFull_t const *InsertNotFullPtr;

static B_node* create_node(bool is_leaf) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    if (!node)  return NULL;
    node->is_leaf = is_leaf;
    node->keys_count = 0;
    node->parent = NULL;
    for (int i = 0; i < MAX_CHILDREN; i++) node->children[i] = NULL;
    return node;
}

B_search_result Search(B_tree* tree, int data) {
    if (!tree) return MISSING;
    B_node* node = tree->root;
    while (node) {
        int i = 0;
        while (i < node->keys_count && data > node->keys[i]) i++;
        if (i < node->keys_count && data == node->keys[i]) return EXISTS;
        if (node->is_leaf) return MISSING;
        node = node->children[i];
    }
    return MISSING;
}


void split(B_node* parent, int index) {
    B_node* y = parent->children[index];
    B_node* z = create_node(y->is_leaf);
    z->parent = parent;
    z->keys_count = T - 1;
   
    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];
    
    if (!y->is_leaf) {
        for (int j = 0; j < T; j++) {
            z->children[j] = y->children[j + T];
            if (z->children[j]) z->children[j]->parent = z;
        }
    }
    y->keys_count = T - 1;
    
    for (int j = parent->keys_count; j >= index + 1; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[index + 1] = z;
   
    for (int j = parent->keys_count - 1; j >= index; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[index] = y->keys[T - 1];
    parent->keys_count++;
}


void insertNotFull(B_node* node, int key) {
    if (!node) return;

    int i = node->keys_count - 1;

    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->keys_count++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        
        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        (*InsertNotFullPtr)(node->children[i], key);
    }
}

void Insert(B_tree* tree, int data) {
    if (!tree->root) tree->root = create_node(true);
    if (Search(tree, data) == EXISTS) return;
    B_node* r = tree->root;
    if (r->keys_count == MAX_KEYS) {
        B_node* s = create_node(false);
        tree->root = s;
        s->children[0] = r;
        r->parent = s;
        (*SplitFPtr)(s, 0);
        (*InsertNotFullPtr)(s, data);
    }
    else {
        (*InsertNotFullPtr)(r, data);
    }
}

void Free(B_tree* tree) {
    if (!tree->root) return;

    size_t stack_capacity = 32;
    size_t stack_size = 0;
    B_node** stack = (B_node**)malloc(stack_capacity * sizeof(B_node*));

    stack[stack_size++] = tree->root;

    while (stack_size > 0) {
        B_node* node = stack[--stack_size];
        if (!node->is_leaf) {
            for (int i = 0; i <= node->keys_count; ++i) {
                if (node->children[i]) {
                    if (stack_size == stack_capacity) {
                        stack_capacity *= 2;
                        B_node** new_stack = (B_node**)realloc(stack, stack_capacity * sizeof(B_node*));
                        stack = new_stack;
                    }
                    stack[stack_size++] = node->children[i];
                }
            }
        }
        free(node);
    }
    free(stack);
    tree->root = NULL;
}



B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { 0 };
    B_node* node = tree->root;
    if (!tree || !tree->root || tree->root->keys_count == 0){
        iter.node = NULL;
        iter.position = -1;
        return iter;
        };
    while (!node->is_leaf) node = node->children[0];
    iter.node = node;
    iter.position = -1; 
    return iter;
}


int Next(B_tree_iterator *iter) {
  if (!iter || !iter->node)
    return 0;

  B_node *current_node = iter->node;
  int current_pos = iter->position;

  if (!current_node->is_leaf && current_pos != -1) {
    B_node *child = current_node->children[current_pos + 1];
    while (!child->is_leaf)
      child = child->children[0];
    iter->node = child;
    iter->position = 0;
    return 1;
  }

  if (current_node->is_leaf) {
    if (current_pos + 1 < current_node->keys_count) {
      iter->position++;
      return 1;

    } else {
      B_node *child = current_node;
      B_node *parent = child->parent;
      int child_idx;
      while (parent) {

        for (child_idx = 0; child_idx <= parent->keys_count; child_idx++) {
          if (parent->children[child_idx] == child) {
            break;
          }
        }
    
        if (child_idx < parent->keys_count) {
          iter->node = parent;
          iter->position = child_idx;
          return 1;
        }
        child = parent;
        parent = parent->parent;
      }

      iter->node = NULL;
      iter->position = -1;
      return 0;
    }
  }
  
  if (!current_node->is_leaf && current_pos == -1) {
    B_node *child = current_node;
    while (!child->is_leaf)
      child = child->children[0];
    iter->node = child;
    iter->position = 0;
    return 1;
  }
  iter->node = NULL;
  iter->position = -1;
  return 0;
}


int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position < 0 || 
        iter->position >= iter->node->keys_count)
        return 0; 
    return iter->node->keys[iter->position];
}
