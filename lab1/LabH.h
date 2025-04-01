#pragma once

#include <cstdlib>
#include <algorithm>

// Узел дерева. int - ключ, double - данные.
struct Node {
    int key;          // Ключ узла
    double data;      // Данные узла
    int size;         // Размер поддерева
    Node* left;       // Левый потомок
    Node* right;      // Правый потомок

    Node(int key, double data)
        : key(key), data(data), size(1), left(nullptr), right(nullptr) {}
};

// Функции для работы с деревом.
double get(Node* tree, int key);          // Получение значения по ключу
Node* add(Node* tree, int key, double data);  // Добавление узла
Node* remove(Node* tree, int key);       // Удаление узла
int height(Node* tree);                  // Высота дерева
int size(Node* tree);                    // Размер дерева
