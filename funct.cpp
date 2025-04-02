#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace std;

struct Node {
    int value;
    int height;
    int size;
    Node* left;
    Node* right;
    Node(int v) : value(v), height(1), size(1), left(nullptr), right(nullptr) {}
};

int height(Node* node) {
    return node ? node->height : 0;
}

int size(Node* node) {
    return node ? node->size : 0;
}

void update(Node* node) {
    node->height = 1 + max(height(node->left), height(node->right));
    node->size = 1 + size(node->left) + size(node->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    update(y);
    update(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    update(x);
    update(y);
    return y;
}

int balanceFactor(Node* node) {
    return height(node->left) - height(node->right);
}

Node* balance(Node* node) {
    if (!node) return nullptr;

    update(node);
    int bf = balanceFactor(node);

    if (bf > 1) {
        if (balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (bf < -1) {
        if (balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

Node* insert(Node* node, int index, int value) {
    if (!node)
        return new Node(value);

    int leftSize = size(node->left);

    if (index <= leftSize) {
        node->left = insert(node->left, index, value);
    }
    else {
        node->right = insert(node->right, index - leftSize - 1, value);
    }

    return balance(node);
}

Node* getMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

Node* remove(Node* node, int index) {
    if (!node) return nullptr;

    int leftSize = size(node->left);

    if (index < leftSize) {
        node->left = remove(node->left, index);
    }
    else if (index > leftSize) {
        node->right = remove(node->right, index - leftSize - 1);
    }
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        else {
            Node* temp = getMin(node->right);
            node->value = temp->value;
            node->right = remove(node->right, 0);
        }
    }

    return balance(node);
}

int get(Node* node, int index) {
    int leftSize = size(node->left);

    if (index < leftSize)
        return get(node->left, index);
    else if (index > leftSize)
        return get(node->right, index - leftSize - 1);
    else
        return node->value;
}

bool search(Node* node, int value) {
    if (!node)
        return false;

    if (node->value == value)
        return true;

    if (value < node->value)
        return search(node->left, value);

    return search(node->right, value);
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (height(left) > height(right)) {
        Node* merged = merge(left->right, right);
        left->right = merged;
        return balance(left);
    }
    else {
        Node* merged = merge(left, right->left);
        right->left = merged;
        return balance(right);
    }
}

class AVLList {
    Node* root;

public:
    AVLList() : root(nullptr) {}
    AVLList(Node* r) : root(r) {}

    void insert(int index, int value) {
        root = ::insert(root, index, value);
    }

    void remove(int index) {
        root = ::remove(root, index);
    }

    int get(int index) {
        if (index < 0 || index >= size())
            throw out_of_range("Index out of bounds");
        return ::get(root, index);
    }

    bool search(int value) {
        return ::search(root, value);
    }

    int size() {
        return ::size(root);
    }

    void concatenate(AVLList& other) {
        root = ::merge(root, other.root);
        other.root = nullptr;
    }

    void printInOrder() {
        cout << "List elements: ";
        printInOrder(root);
        cout << endl;
    }

private:
    void printInOrder(Node* node) {
        if (!node) return;
        printInOrder(node->left);
        cout << node->value << " ";
        printInOrder(node->right);
    }
};