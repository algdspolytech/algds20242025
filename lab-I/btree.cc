#include "btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Реализация функций остается без изменений
B_node* new_node(bool is_leaf) {
    B_node *node = (B_node*)malloc(sizeof(B_node));
    if (!node) return NULL;
    node->keys_count = 0;
    node->is_leaf = is_leaf;
    node->parent = NULL;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Реализация функции разделения узла
void split(B_node *parent, int child_index) {
    B_node *child = parent->children[child_index];
    B_node *right = new_node(child->is_leaf);
    right->parent = parent;
    right->keys_count = T - 1;

    // Копируем правую половину ключей
    for (int j = 0; j < T - 1; j++) {
        right->keys[j] = child->keys[j + T];
    }

    // Копируем правую половину детей (если не лист)
    if (!child->is_leaf) {
        for (int j = 0; j < T; j++) {
            right->children[j] = child->children[j + T];
            if (right->children[j]) {
                right->children[j]->parent = right;
            }
            child->children[j + T] = NULL;
        }
    }

    // Обновляем количество ключей в исходном узле
    child->keys_count = T - 1;

    // Сдвигаем детей родителя
    for (int j = parent->keys_count; j > child_index; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[child_index + 1] = right;

    // Сдвигаем ключи родителя
    for (int j = parent->keys_count - 1; j >= child_index; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    
    // Вставляем средний ключ в родителя
    parent->keys[child_index] = child->keys[T - 1];
    parent->keys_count++;
}

// Реализация вставки в неполный узел
void insertNotFull(B_node *node, int data) {
    int i = node->keys_count - 1;

    if (node->is_leaf) {
        // Ищем позицию для вставки
        while (i >= 0 && data < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        
        // Проверяем дубликат
        if (i >= 0 && node->keys[i] == data) {
            return;
        }
        
        // Вставляем ключ
        node->keys[i + 1] = data;
        node->keys_count++;
    } else {
        // Ищем дочерний узел для вставки
        while (i >= 0 && data < node->keys[i]) {
            i--;
        }
        i++;
        
        // Проверяем дубликат
        if (i > 0 && node->keys[i - 1] == data) {
            return;
        }
        
        // Если дочерний узел полон - разделяем
        if (node->children[i]->keys_count == MAX_KEYS) {
            (*SplitFPtr)(node, i);
            // После разделения проверяем, куда вставлять
            if (data > node->keys[i]) {
                i++;
            } else if (data == node->keys[i]) {
                return; // Ключ уже существует
            }
        }
        (*InsertNotFullPtr)(node->children[i], data);
    }
}

// Основная функция вставки
void Insert(B_tree *tree, int data) {
    if (tree->root == NULL) {
        tree->root = new_node(true);
        tree->root->keys[0] = data;
        tree->root->keys_count = 1;
        return;
    }

    if (tree->root->keys_count == MAX_KEYS) {
        // Создаем новый корень
        B_node *new_root = new_node(false);
        new_root->children[0] = tree->root;
        tree->root->parent = new_root;
        tree->root = new_root;
        
        // Разделяем старый корень
        (*SplitFPtr)(new_root, 0);
        
        // Вставляем ключ в новый корень
        (*InsertNotFullPtr)(new_root, data);
    } else {
        (*InsertNotFullPtr)(tree->root, data);
    }
}

// Функция поиска
B_search_result Search(B_tree *tree, int data) {
    if (tree->root == NULL) {
        return MISSING;
    }
    
    B_node *current = tree->root;
    while (current != NULL) {
        int i = 0;
        // Ищем позицию в текущем узле
        while (i < current->keys_count && data > current->keys[i]) {
            i++;
        }
        
        // Проверяем найденный ключ
        if (i < current->keys_count && data == current->keys[i]) {
            return EXISTS;
        }
        
        // Если лист - ключ не найден
        if (current->is_leaf) {
            return MISSING;
        }
        
        // Переходим к дочернему узлу
        current = current->children[i];
    }
    
    return MISSING;
}

// Вспомогательная функция для освобождения памяти
static void free_node(B_node *node) {
    if (node == NULL) return;
    
    // Рекурсивно освобождаем детей
    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_count; i++) {
            if (node->children[i]) {
                free_node(node->children[i]);
            }
        }
    }
    
    free(node);
}

// Функция освобождения дерева
void Free(B_tree *tree) {
    if (tree->root) {
        free_node(tree->root);
        tree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree *tree) {
    B_tree_iterator iter = {NULL, 0};
    
    if (tree->root == NULL) {
        return iter;
    }
    
    // Находим самый левый лист
    B_node *current = tree->root;
    while (!current->is_leaf) {
        current = current->children[0];
    }
    
    iter.node = current;
    iter.position = 0;
    return iter;
}

int Next(B_tree_iterator *iter) {
    if (iter->node == NULL) {
        return 0;
    }

    // Если узел листовой
    if (iter->node->is_leaf) {
        // Если есть ключи справа
        if (iter->position < iter->node->keys_count - 1) {
            iter->position++;
            return 1;
        } else {
            // Поднимаемся вверх для поиска следующего ключа
            B_node *current = iter->node;
            while (current->parent != NULL) {
                B_node *parent = current->parent;
                int child_index = -1;
                
                // Находим индекс текущего узла в родителе
                for (int i = 0; i <= parent->keys_count; i++) {
                    if (parent->children[i] == current) {
                        child_index = i;
                        break;
                    }
                }
                
                if (child_index == -1) {
                    break;
                }
                
                // Следующий ключ - это ключ родителя с индексом child_index
                if (child_index < parent->keys_count) {
                    iter->node = parent;
                    iter->position = child_index; // Исправлено: используем child_index как индекс ключа
                    return 1;
                }
                
                current = parent;
            }
            iter->node = NULL;
            return 0;
        }
    } else {
        // Для внутреннего узла переходим к следующему поддереву
        B_node *child = iter->node->children[iter->position + 1];
        while (child && !child->is_leaf) {
            child = child->children[0];
        }
        
        if (child) {
            iter->node = child;
            iter->position = 0;
            return 1;
        }
        return 0;
    }
}

int Key(B_tree_iterator *iter) {
    if (iter->node == NULL || 
        iter->position < 0 || 
        iter->position >= iter->node->keys_count) {
        return 0;
    }
    return iter->node->keys[iter->position];
}