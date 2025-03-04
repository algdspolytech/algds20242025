#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Структура узла AVL-дерева, представляющего линейный список.
typedef struct Node {
    int key;         // Значение элемента.
    int height;      // Высота поддерева.
    int size;        // Количество узлов в поддереве.
    struct Node* left, * right;
} Node;

// Функция создания нового узла.
Node* create_node(int key);

// Возвращает высоту узла (0, если узел равен NULL).
int getHeight(Node* node);

// Возвращает размер поддерева (0, если узел равен NULL).
int getSize(Node* node);

// Обновление высоты и размера узла на основе его потомков.
void update(Node* node);

// Правый поворот вокруг узла y.
Node* rightRotate(Node* y);

// Левый поворот вокруг узла x.
Node* leftRotate(Node* x);

// Получение балансирующего фактора узла.
int getBalance(Node* node);

// Балансировка узла AVL-дерева.
Node* balance(Node* node);

// Поиск k-го элемента в списке (1-based нумерация).
Node* find_kth(Node* root, int k);

// Поиск элемента по значению key.
Node* search_by_key(Node* root, int key);

// Вставка элемента со значением key в позицию pos (0-based индекс).
Node* insert_at(Node* root, int pos, int key);

// Удаление элемента, занимающего позицию pos (0-based индекс).
Node* delete_at(Node* root, int pos);

// Функция extract_max извлекает (удаляет) максимальный элемент.
Node* extract_max(Node* root, Node** max_node);

// Операция сцепления двух списков, представленных AVL-деревьями.
Node* join_trees(Node* t1, Node* t2);

// Функция in-order обхода для вывода элементов дерева в виде списка.
void inorder_print(Node* root);

#endif // AVL_H