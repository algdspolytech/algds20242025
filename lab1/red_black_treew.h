#pragma once
#include <iostream>


using namespace std;

enum Color { RED, BLACK };

struct Node {
    double data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(double value) {
        data = value;
        color = RED;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};


Node* insert_node(Node* root, double data);

Node* search(Node* root, double data);

Node* delete_node(Node* tree, Node* node);