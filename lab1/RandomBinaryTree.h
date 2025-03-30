#pragma once
#include <random>
#include <cmath>


// int - ��� �����, double - ��� ������
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

Node* join(Node* node1, Node* node2); // ����������� ���� ��������

Node* remove(Node* tree, Node* p, int k); // �������� �� ������ p ������� ���������� ���� � ������ k 

// ���������� �������� �� �����
double get(Node* tree, int key);
// ��������� ���� 
Node* add(Node* tree, int key, double data);

// ������� ����
Node* remove(Node* tree, int key);
// ������ ������
int height(Node* tree);

// ������ ������
int size(Node* tree);
