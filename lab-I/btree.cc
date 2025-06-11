#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "btree.h"



static B_node* create_node(bool is_leaf, B_node* parent) {
    B_node* node = (B_node*)malloc(sizeof(B_node));
    node->is_leaf = is_leaf;
    node->keys_count = 0;
    node->parent = parent;
    for (int i = 0; i < MAX_CHILDREN; ++i) node->children[i] = NULL;
    for (int i = 0; i < MAX_KEYS; ++i) node->keys[i] = 0;
    return node;
}

static void free_node(B_node* node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i)
            free_node(node->children[i]);
    }
    free(node);
}


// Поиск ключа в дереве
B_search_result Search(B_tree *tree, int data) {
    B_node *cur = tree->root;
    while (cur) {
        int i = 0;
        while (i < cur->keys_count && data > cur->keys[i]) ++i;
        if (i < cur->keys_count && data == cur->keys[i]) return EXISTS;
        if (cur->is_leaf) return MISSING;
        cur = cur->children[i];
    }
    return MISSING;
}

// Вставка ключа в дерево
void Insert(B_tree *tree, int data) {
    if (!tree->root) {
        tree->root = create_node(true, NULL);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }
    if (Search(tree, data) == EXISTS) return;
    B_node *r = tree->root;
    if (r->keys_count == MAX_KEYS) {
        // Корень заполнен, создаём новый корень и делим старый
        B_node *s = create_node(false, NULL);
        s->children[0] = r;
        r->parent = s;
        tree->root = s;
        (*SplitFPtr)(s, 0);
        (*InsertNotFullPtr)(s, data);
    } else {
        (*InsertNotFullPtr)(r, data);
    }
}

// Вставка ключа в не полностью заполненный узел
void insertNotFull(B_node *node, int data) {
    int i = node->keys_count - 1;
    if (node->is_leaf) {
        // Сдвигаем ключи вправо для вставки
        while (i >= 0 && node->keys[i] > data) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = data;
        node->keys_count++;
    } else {
        // Находим, в какого потомка идти
        while (i >= 0 && node->keys[i] > data) --i;
        ++i;
        // Если потомок заполнен, делим его
        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            if (node->keys[i] < data) ++i;
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

// Деление заполненного дочернего узла по индексу
void split(B_node *parent_of_splited, int split_at_index) {
    B_node *y = parent_of_splited->children[split_at_index];
    B_node *z = create_node(y->is_leaf, parent_of_splited);
    z->keys_count = T - 1;

    // Копируем последние T-1 ключей из y в z
    for (int j = 0; j < T - 1; ++j)
        z->keys[j] = y->keys[j + T];

    // Копируем детей, если не лист
    if (!y->is_leaf) {
        for (int j = 0; j < T; ++j) {
            z->children[j] = y->children[j + T];
            if (z->children[j]) z->children[j]->parent = z;
        }
    }
    y->keys_count = T - 1;

    // Сдвигаем детей родителя вправо
    for (int j = parent_of_splited->keys_count; j >= split_at_index + 1; --j)
        parent_of_splited->children[j + 1] = parent_of_splited->children[j];
    parent_of_splited->children[split_at_index + 1] = z;

    // Сдвигаем ключи родителя вправо
    for (int j = parent_of_splited->keys_count - 1; j >= split_at_index; --j)
        parent_of_splited->keys[j + 1] = parent_of_splited->keys[j];
    // Поднимаем медианный ключ
    parent_of_splited->keys[split_at_index] = y->keys[T - 1];
    parent_of_splited->keys_count++;
}

// Освобождение памяти дерева
void Free(B_tree *tree) {
    if (!tree) return;
    free_node(tree->root);
    tree->root = NULL;
}

// ================== ИТЕРАТОР ==================

// Для итератора используем стек для обхода in-order
typedef struct StackNode {
    B_node* node;
    int pos;
    struct StackNode* next;
} StackNode;

static void stack_push(StackNode** top, B_node* node, int pos) {
    StackNode* s = (StackNode*)malloc(sizeof(StackNode));
    s->node = node; s->pos = pos; s->next = *top;
    *top = s;
}

static void stack_pop(StackNode** top) {
    if (!*top) return;
    StackNode* tmp = *top;
    *top = (*top)->next;
    free(tmp);
}

static StackNode* stack_top(StackNode* top) {
    return top;
}

// Итератор: инициализация (находит самый левый ключ)
B_tree_iterator IteratorBegin(B_tree *tree) {
    B_tree_iterator iter = {NULL, 0};
    B_node* node = tree->root;
    if (!node) return iter;
    // Спускаемся влево
    while (!node->is_leaf)
        node = node->children[0];
    iter.node = node;
    iter.position = -1; // Next сразу перейдёт к первому ключу
    return iter;
}

// Итератор: переход к следующему элементу (in-order обход)
int Next(B_tree_iterator *iter) {
    static StackNode* stack = NULL;
    if (!iter->node) return 0;

    if (iter->position == -1) {
        // Первый вызов Next
        B_node* node = iter->node;
        while (!node->is_leaf) {
            stack_push(&stack, node, 0);
            node = node->children[0];
        }
        iter->node = node;
        iter->position = 0;
        return iter->position < node->keys_count;
    }

    if (iter->node->is_leaf) {
        ++iter->position;
        if (iter->position < iter->node->keys_count)
            return 1;
        // Переходим к родителю по стеку
        while (stack_top(stack)) {
            StackNode* top = stack_top(stack);
            B_node* parent = top->node;
            int pos = top->pos;
            stack_pop(&stack);
            if (pos < parent->keys_count) {
                iter->node = parent;
                iter->position = pos;
                // После этого надо спуститься в самый левый потомок parent->children[pos+1]
                B_node* n = parent->children[pos + 1];
                while (n && !n->is_leaf) {
                    stack_push(&stack, n, 0);
                    n = n->children[0];
                }
                if (n) {
                    iter->node = n;
                    iter->position = 0;
                }
                return 1;
            }
        }
        iter->node = NULL;
        return 0;
    } else {
        // Внутренний узел
        B_node* n = iter->node->children[iter->position + 1];
        while (n && !n->is_leaf) {
            stack_push(&stack, n, 0);
            n = n->children[0];
        }
        if (n) {
            iter->node = n;
            iter->position = 0;
            return 1;
        }
        iter->node = NULL;
        return 0;
    }
}

// Итератор: получить текущий ключ
int Key(B_tree_iterator *iter) {
    if (!iter->node || iter->position < 0 || iter->position >= iter->node->keys_count)
        return 0;
    return iter->node->keys[iter->position];
}
