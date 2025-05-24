#include "btree.h"
#include <stdlib.h>
#include <string.h>

// Определение указателей на функции
extern split_t const* SplitFPtr;
extern insertNotFull_t const* InsertNotFullPtr;

// Вспомогательная функция для создания нового узла
static B_node* init_btree_node(void) {
    B_node* new_element = (B_node*)malloc(sizeof(B_node));
    if (!new_element) return NULL;

    // Инициализация полей узла
    for (int idx = 0; idx < MAX_CHILDREN; ++idx) {
        new_element->children[idx] = NULL;
    }
    for (int idx = 0; idx < MAX_KEYS; ++idx) {
        new_element->keys[idx] = 0;
    }
    new_element->keys_count = 0;
    new_element->is_leaf = true;
    new_element->parent = NULL;
    return new_element;
}

// Разделение переполненного узла
void split(B_node* parent, int child_idx) {
    // Проверка входных данных
    if (!parent || child_idx < 0 || child_idx >= MAX_CHILDREN) {
        return;
    }

    B_node* target_node = parent->children[child_idx];
    if (!target_node) return;

    // Создание нового узла для правой части
    B_node* right_part = init_btree_node();
    if (!right_part) return;

    // Настройка нового узла
    right_part->is_leaf = target_node->is_leaf;
    right_part->parent = parent;
    right_part->keys_count = T - 1;

    // Копирование ключей в правую часть
    for (int idx = 0; idx < T - 1; idx++) {
        right_part->keys[idx] = target_node->keys[idx + T];
    }

    // Обработка дочерних узлов для внутреннего узла
    if (!target_node->is_leaf) {
        for (int idx = 0; idx < T; idx++) {
            right_part->children[idx] = target_node->children[idx + T];
            if (right_part->children[idx]) {
                right_part->children[idx]->parent = right_part;
            }
        }
    }

    // Обновление размера исходного узла
    target_node->keys_count = T - 1;

    // Сдвиг элементов родительского узла
    for (int idx = parent->keys_count; idx > child_idx; idx--) {
        parent->keys[idx] = parent->keys[idx - 1];
        parent->children[idx + 1] = parent->children[idx];
    }

    // Вставка среднего элемента и связывание узлов
    parent->keys[child_idx] = target_node->keys[T - 1];
    parent->children[child_idx + 1] = right_part;
    parent->keys_count++;
}

// Вставка в неполный узел
void insertNotFull(B_node* target, int value) {
    if (!target) return;

    int pos = target->keys_count - 1;

    if (target->is_leaf) {
        // Вставка в лист
        while (pos >= 0 && target->keys[pos] > value) {
            target->keys[pos + 1] = target->keys[pos];
            pos--;
        }
        target->keys[pos + 1] = value;
        target->keys_count++;
    } else {
        // Поиск позиции в нелистовом узле
        while (pos >= 0 && target->keys[pos] > value) {
            pos--;
        }
        pos++;

        // Проверка и вставка в дочерний узел
        if (pos >= 0 && pos < MAX_CHILDREN && target->children[pos]) {
            if (target->children[pos]->keys_count == MAX_KEYS) {
                (*SplitFPtr)(target, pos);
                if (value > target->keys[pos]) pos++;
            }
            if (pos >= 0 && pos < MAX_CHILDREN && target->children[pos]) {
                (*InsertNotFullPtr)(target->children[pos], value);
            }
        }
    }
}

// Основная функция вставки
void Insert(B_tree* tree, int value) {
    if (!tree) return;

    // Проверка на дубликаты
    if (Search(tree, value) == EXISTS) return;

    // Создание корня для пустого дерева
    if (!tree->root) {
        tree->root = init_btree_node();
        if (!tree->root) return;
        tree->root->keys[0] = value;
        tree->root->keys_count = 1;
        return;
    }

    // Обработка переполнения корня
    if (tree->root->keys_count == MAX_KEYS) {
        B_node* new_root = init_btree_node();
        if (!new_root) return;
        
        new_root->is_leaf = false;
        new_root->children[0] = tree->root;
        tree->root->parent = new_root;
        tree->root = new_root;
        
        (*SplitFPtr)(new_root, 0);
        (*InsertNotFullPtr)(new_root, value);
    } else {
        (*InsertNotFullPtr)(tree->root, value);
    }
}

// Поиск значения в дереве
B_search_result Search(B_tree* tree, int value) {
    if (!tree || !tree->root) return MISSING;

    B_node* current_node = tree->root;
    while (current_node) {
        int pos = 0;
        while (pos < current_node->keys_count && value > current_node->keys[pos]) {
            pos++;
        }

        if (pos < current_node->keys_count && value == current_node->keys[pos]) {
            return EXISTS;
        }

        if (current_node->is_leaf) break;

        if (pos >= 0 && pos < MAX_CHILDREN) {
            current_node = current_node->children[pos];
        } else {
            break;
        }
    }
    return MISSING;
}

// Освобождение памяти
void Free(B_tree* tree) {
    if (!tree || !tree->root) return;

    const size_t INITIAL_STACK_SIZE = 16;
    size_t current_stack_size = 0;
    size_t max_stack_size = INITIAL_STACK_SIZE;
    
    B_node** node_stack = (B_node**)malloc(sizeof(B_node*) * max_stack_size);
    if (!node_stack) return;

    // Добавляем корень в стек
    node_stack[current_stack_size++] = tree->root;

    while (current_stack_size > 0) {
        B_node* current = node_stack[--current_stack_size];

        if (!current->is_leaf) {
            // Добавляем дочерние узлы в стек
            for (int idx = 0; idx <= current->keys_count; idx++) {
                if (current->children[idx]) {
                    if (current_stack_size == max_stack_size) {
                        max_stack_size *= 2;
                        B_node** temp_stack = (B_node**)realloc(node_stack, sizeof(B_node*) * max_stack_size);
                        if (!temp_stack) {
                            free(node_stack);
                            return;
                        }
                        node_stack = temp_stack;
                    }
                    node_stack[current_stack_size++] = current->children[idx];
                }
            }
        }
        free(current);
    }

    free(node_stack);
    tree->root = NULL;
}

// Инициализация итератора
B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iterator = { NULL, -1 };
    if (!tree || !tree->root || tree->root->keys_count == 0) {
        return iterator;
    }

    // Поиск самого левого листа
    B_node* current = tree->root;
    while (!current->is_leaf && current->children[0]) {
        current = current->children[0];
    }

    iterator.node = current;
    iterator.position = -1;
    return iterator;
}

// Переход к следующему элементу
int Next(B_tree_iterator* iter) {
    if (!iter || !iter->node) return 0;

    B_node* current = iter->node;
    int current_pos = iter->position;

    if (current->is_leaf) {
        // Обработка листового узла
        if (current_pos + 1 < current->keys_count) {
            iter->position++;
            return 1;
        }

        // Подъем по дереву
        while (current->parent) {
            int child_pos = 0;
            while (child_pos <= current->parent->keys_count && 
                   current->parent->children[child_pos] != current) {
                child_pos++;
            }

            if (child_pos < current->parent->keys_count) {
                iter->node = current->parent;
                iter->position = child_pos;
                return 1;
            }
            current = current->parent;
        }
    } else {
        // Обработка внутреннего узла
        if (current_pos == -1) {
            B_node* leftmost = current->children[0];
            while (!leftmost->is_leaf) {
                leftmost = leftmost->children[0];
            }
            iter->node = leftmost;
            iter->position = 0;
            return 1;
        }

        B_node* next = current->children[current_pos + 1];
        if (next) {
            while (!next->is_leaf) {
                next = next->children[0];
            }
            iter->node = next;
            iter->position = 0;
            return 1;
        }
    }

    // Достигнут конец дерева
    iter->node = NULL;
    iter->position = -1;
    return 0;
}

// Получение текущего значения
int Key(B_tree_iterator* iter) {
    if (!iter || !iter->node || 
        iter->position < 0 || 
        iter->position >= iter->node->keys_count) {
        return 0;
    }
    return iter->node->keys[iter->position];
}