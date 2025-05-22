#include "btree.h"
#include <stdlib.h>
#include <stdbool.h>


// Вспомогательная функция для создания нового узла
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

// Вспомогательная функция для освобождения памяти узла и его потомков
static void free_node(B_node* node) {
    if (!node) return;

    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            free_node(node->children[i]);
        }
    }

    free(node);
}

// Вспомогательная функция для поиска ключа в узле
static int find_key(B_node* node, int data) {
    int i = 0;
    while (i < node->keys_count && data > node->keys[i]) {
        i++;
    }
    return i;
}

void Insert(B_tree* tree, int data) {
    if (!tree) return;

    // Если дерево пустое, создаем корень
    if (!tree->root) {
        tree->root = create_node(true);
        if (!tree->root) return;
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    // Если корень полный, нужно его разделить
    if (tree->root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false);
        if (!new_root) return;

        new_root->children[0] = tree->root;
        tree->root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
    }

    // Вставляем ключ в неполный узел
    (*InsertNotFullPtr)(tree->root, data);
}

void Free(B_tree* tree) {
    if (!tree) return;
    free_node(tree->root);
    tree->root = NULL;
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

void insertNotFull(B_node* node, int data) {
    if (!node) return;

    int i = node->keys_count - 1;

    if (node->is_leaf) {
        // Находим позицию для вставки и сдвигаем ключи
        while (i >= 0 && data < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        // Проверяем, не дублируется ли ключ
        if (i >= 0 && data == node->keys[i]) {
            return;
        }

        // Вставляем новый ключ
        node->keys[i + 1] = data;
        node->keys_count++;
    } else {
        // Находим дочерний узел для вставки
        while (i >= 0 && data < node->keys[i]) {
            i--;
        }

        // Проверяем на дубликат
        if (i >= 0 && data == node->keys[i]) {
            return;
        }

        i++;

        // Если дочерний узел полный, разделяем его
        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);

            // После разделения определяем, в какой из двух новых узлов вставлять
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

    // Копируем ключи и дети (если есть) из полного узла в новый
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

    // Сдвигаем дети и ключи в родительском узле для нового ключа и указателя
    for (int i = parent_of_splited->keys_count; i > split_at_index; i--) {
        parent_of_splited->keys[i] = parent_of_splited->keys[i - 1];
        parent_of_splited->children[i + 1] = parent_of_splited->children[i];
    }

    // Вставляем средний ключ из полного узла в родительский
    parent_of_splited->keys[split_at_index] = full_node->keys[MIN_CHILDREN];
    parent_of_splited->children[split_at_index + 1] = new_node;
    parent_of_splited->keys_count++;
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = {NULL, 0};
    if (!tree || !tree->root) return iter;

    // Находим самый левый узел (с наименьшим ключом)
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

    // Если есть еще ключи в текущем узле
    if (iter->position + 1 < iter->node->keys_count) {
        iter->position++;
        return 1;
    }

    // Если это был последний ключ в узле, переходим к следующему узлу
    B_node* current = iter->node;
    int key = current->keys[iter->position];

    // Поднимаемся вверх по дереву, пока не найдем узел с большим ключом
    while (current->parent) {
        int pos = find_key(current->parent, key);

        if (pos < current->parent->keys_count) {
            // Переходим к следующему дочернему узлу
            current = current->parent->children[pos + 1];
            // Спускаемся до самого левого узла
            while (!current->is_leaf) {
                current = current->children[0];
            }
            iter->node = current;
            iter->position = 0;
            return 1;
        }

        current = current->parent;
    }

    // Если мы дошли до корня и не нашли больше ключей
    iter->node = NULL;
    return 0;
}

int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || iter->position >= iter->node->keys_count) {
        return 0;
    }
    return iter->node->keys[iter->position];
}


