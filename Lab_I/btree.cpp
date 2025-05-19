#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "btree.h"


// Вспомогательная функция создания узла
B_node* create_node(bool is_leaf) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    node->keys_count = 0;
    node->is_leaf = is_leaf;
    node->parent = NULL;
    for (int i = 0; i < MAX_CHILDREN; i++) node->children[i] = NULL;
    return node;
}

B_search_result Search(B_tree* tree, int data) {
    B_node* node = tree->root;
    while (node != NULL) {
        int i = 0;
        while (i < node->keys_count && data > node->keys[i]) i++;
        if (i < node->keys_count && data == node->keys[i]) return EXISTS;
        if (node->is_leaf) return MISSING;
        node = node->children[i];
    }
    return MISSING;
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
        while (i >= 0 && data < node->keys[i]) i--;
        i++;
        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            if (data > node->keys[i]) i++;
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

void split(B_node* parent, int index) {
    B_node* full_child = parent->children[index];
    B_node* new_node = create_node(full_child->is_leaf);
    new_node->parent = parent;

    new_node->keys_count = MIN_CHILDREN;
    for (int j = 0; j < MIN_CHILDREN; j++)
        new_node->keys[j] = full_child->keys[j + T];

    if (!full_child->is_leaf) {
        for (int j = 0; j <= MIN_CHILDREN; j++) {
            new_node->children[j] = full_child->children[j + T];
            if (new_node->children[j]) new_node->children[j]->parent = new_node;
        }
    }

    for (int j = parent->keys_count; j > index; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[index + 1] = new_node;

    for (int j = parent->keys_count - 1; j >= index; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[index] = full_child->keys[MIN_CHILDREN];
    parent->keys_count++;

    full_child->keys_count = MIN_CHILDREN;
}

void Insert(B_tree* tree, int data) {
    if (Search(tree, data) == EXISTS) return;

    if (tree->root == NULL) {
        tree->root = create_node(true);
    }

    B_node* root = tree->root;
    if (root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false);
        new_root->children[0] = root;
        root->parent = new_root;
        tree->root = new_root;
        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, data);
    }
    else {
        (*InsertNotFullPtr)(root, data);
    }
}

void free_node(B_node* node) {
    if (!node) return;
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

// Стек для итератора
typedef struct StackItem {
    B_node* node;
    int pos;
} StackItem;

#define STACK_MAX 256

typedef struct {
    StackItem data[STACK_MAX];
    int top;
} Stack;

static void stack_push(Stack* stack, B_node* node, int pos) {
    if (stack->top < STACK_MAX) {
        stack->data[stack->top].node = node;
        stack->data[stack->top].pos = pos;
        stack->top++;
    }
}

static StackItem stack_pop(Stack* stack) {
    if (stack->top == 0) {
        StackItem empty = { NULL, 0 };
        return empty;
    }
    return stack->data[--stack->top];
}

static bool stack_is_empty(Stack* stack) {
    return stack->top == 0;
}

static void push_leftmost(Stack* stack, B_node* node) {
    while (node != NULL) {
        stack_push(stack, node, 0);
        if (node->is_leaf) break;
        node = node->children[0];
    }
}

static Stack global_stack;

B_tree_iterator IteratorBegin(B_tree* tree) {
    global_stack.top = 0;
    B_tree_iterator iter = { NULL, -1 };
    if (tree->root) {
        push_leftmost(&global_stack, tree->root);
    }
    return iter;
}

int Next(B_tree_iterator* iter) {
    if (stack_is_empty(&global_stack)) {
        iter->node = NULL;
        return 0;
    }
    StackItem top = stack_pop(&global_stack);
    B_node* node = top.node;
    int pos = top.pos;

    // Ставим итератор на текущую позицию
    iter->node = node;
    iter->position = pos;

    // Подготавливаем следующий
    if (pos < node->keys_count - 1) {
        stack_push(&global_stack, node, pos + 1);
        if (!node->is_leaf) {
            push_leftmost(&global_stack, node->children[pos + 1]);
        }
    }
    else if (!node->is_leaf) {
        push_leftmost(&global_stack, node->children[pos + 1]);
    }
    return 1;
}
int Key(B_tree_iterator* iter) {
    if (!iter->node || iter->position < 0 || iter->position >= iter->node->keys_count) {
        return -1;
    }
    return iter->node->keys[iter->position];
}
