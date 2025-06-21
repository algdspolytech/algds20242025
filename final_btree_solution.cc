#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "btree.h"

// Создание нового узла
B_node* create_node(bool is_leaf, B_node* parent) {
    B_node* node = (B_node*)calloc(1, sizeof(B_node));
    if (!node) return NULL;
    
    node->is_leaf = is_leaf;
    node->parent = parent;
    node->keys_count = 0;
    
    // Инициализируем массивы
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    
    return node;
}

// Поиск ключа в B-дереве
B_search_result Search(B_tree* tree, int data) {
    if (!tree || !tree->root) {
        return MISSING;
    }

    B_node* current = tree->root;
    
    while (current) {
        int pos = 0;
        
        // Ищем позицию в текущем узле
        while (pos < current->keys_count && data > current->keys[pos]) {
            pos++;
        }
        
        // Проверяем, найден ли ключ
        if (pos < current->keys_count && data == current->keys[pos]) {
            return EXISTS;
        }
        
        // Переходим к дочернему узлу, если это не лист
        current = current->is_leaf ? NULL : current->children[pos];
    }
    
    return MISSING;
}

// Вставка в неполный узел
void insertNotFull(B_node* node, int data) {
    int idx = node->keys_count - 1;

    if (node->is_leaf) {
        // Сдвигаем элементы для вставки
        while (idx >= 0 && node->keys[idx] > data) {
            node->keys[idx + 1] = node->keys[idx];
            idx--;
        }
        
        node->keys[idx + 1] = data;
        node->keys_count++;
    } else {
        // Находим дочерний узел для вставки
        while (idx >= 0 && data < node->keys[idx]) {
            idx--;
        }
        idx++;

        // Проверяем, не заполнен ли дочерний узел
        if (node->children[idx]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, idx);
            
            // После разбиения может измениться нужный дочерний узел
            if (data > node->keys[idx]) {
                idx++;
            }
        }

        (*InsertNotFullPtr)(node->children[idx], data);
    }
}

// Разбиение узла
void split(B_node* parent, int index) {
    B_node* full = parent->children[index];
    B_node* right = create_node(full->is_leaf, parent);

    right->keys_count = MIN_CHILDREN;
    for (int i = 0; i < MIN_CHILDREN; ++i) {
        right->keys[i] = full->keys[i + T];
    }

    if (!full->is_leaf) {
        for (int i = 0; i <= MIN_CHILDREN; ++i) {
            right->children[i] = full->children[i + T];
            if (right->children[i]) {
                right->children[i]->parent = right;
            }
        }
    }

    for (int j = parent->keys_count; j > index; --j) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[index + 1] = right;

    for (int j = parent->keys_count - 1; j >= index; --j) {
        parent->keys[j + 1] = parent->keys[j];
    }

    parent->keys[index] = full->keys[MIN_CHILDREN];
    parent->keys_count++;

    full->keys_count = MIN_CHILDREN;
}

// Вставка ключа в B-дерево
void Insert(B_tree* tree, int data) {
    // Инициализируем указатели на функции при первом вызове
    if (!SplitFPtr) SplitFPtr = (split_t const*)&split;
    if (!InsertNotFullPtr) InsertNotFullPtr = (insertNotFull_t const*)&insertNotFull;

    if (!tree) return;
    
    // Проверяем, не существует ли уже такой ключ
    if (Search(tree, data) == EXISTS) {
        return;
    }

    // Если дерево пустое, создаем корень
    if (!tree->root) {
        tree->root = create_node(true, NULL);
        if (!tree->root) return;
        
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    B_node* root = tree->root;
    
    // Если корень заполнен, создаем новый корень
    if (root->keys_count == MAX_KEYS) {
        B_node* new_root = create_node(false, NULL);
        if (!new_root) return;
        
        new_root->children[0] = root;
        root->parent = new_root;
        tree->root = new_root;

        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, data);
    } else {
        (*InsertNotFullPtr)(root, data);
    }
}

// Освобождение памяти узла и всех его потомков
void free_node(B_node* node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; ++i) {
            free_node(node->children[i]);
        }
    }
    free(node);
}

// Освобождение памяти B-дерева
void Free(B_tree* tree) {
    if (tree && tree->root) {
        free_node(tree->root);
        tree->root = NULL;
    }
}

// Начало итерации по B-дереву
B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iter = { NULL, -1 };
    if (!tree || !tree->root) return iter;

    B_node* current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    iter.node = current;
    return iter;
}

// Переход к следующему элементу
int Next(B_tree_iterator* iter) {
    if (!iter || !iter->node) return 0;

    B_node* node = iter->node;
    int pos = iter->position;

    if (node->is_leaf) {
        if (++pos < node->keys_count) {
            iter->position = pos;
            return 1;
        }
    }
    else {
        if (++pos <= node->keys_count && node->children[pos]) {
            B_node* current = node->children[pos];
            while (!current->is_leaf) {
                current = current->children[0];
            }
            iter->node = current;
            iter->position = 0;
            return 1;
        }
    }

    B_node* current = node;
    while (current->parent) {
        B_node* parent = current->parent;
        int idx = 0;
        while (idx <= parent->keys_count && parent->children[idx] != current) {
            ++idx;
        }
        if (idx < parent->keys_count) {
            iter->node = parent;
            iter->position = idx;
            return 1;
        }
        current = parent;
    }

    iter->node = NULL;
    return 0;
}

// Получение текущего ключа итератора
int Key(B_tree_iterator* iter) {
    return iter->node->keys[iter->position];
} 