#pragma once
#include <random>
#include <cmath>


// int - тип ключа, double - тип данных
struct Node {
    int key;
    double data;

    int size;

    Node* left;
    Node* right;

    Node(int key, double data) : key(key), data(data), size(1), left(nullptr), right(nullptr) {}
};


// Возвращает значение по ключу
double get(Node* tree, int key);
// Добавляет узел 
Node* add(Node* tree, int key, double data);

// Удаляет узел
Node* remove(Node* tree, int key);
// Высота дерева
int height(Node* tree);

// Размер дерева
int size(Node* tree);
