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


Node* find(Node* node, int key);

int get_size(Node* node);

void fix_size(Node* node);

Node* rotate_right(Node* node);

Node* rotate_left(Node* node);

Node* insert_root(Node* root, Node* node);

Node* insert(Node* root, Node* node);

Node* join(Node* node1, Node* node2); // объединение двух деревьев

Node* remove(Node* tree, Node* p, int k); // удаление из дерева p первого найденного узла с ключом k 

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
