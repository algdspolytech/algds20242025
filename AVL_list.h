#include <iostream>
#include <algorithm>
#include <stdexcept>

struct Node {
    int value;
    int height;
    int size;
    Node* left;
    Node* right;
    Node(int v) : value(v), height(1), size(1), left(nullptr), right(nullptr) {}
};

class AVLList {
    Node* root;

public:
    AVLList() : root(nullptr) {}
    AVLList(Node* r) : root(r) {}

    void insert(int index, int value);
    void remove(int index);
    int get(int index);
    bool search(int value);
    int size();
    void concatenate(AVLList& other);
    void printInOrder();

private:
    void printInOrder(Node* node);
};