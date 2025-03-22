#pragma once
#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <memory>

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    std::shared_ptr<Node> left, right, parent;

    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED;
    }
};

class RBTree {
private:
    std::shared_ptr<Node> root;

protected:
    void rotateLeft(std::shared_ptr<Node>&, std::shared_ptr<Node>&);
    void rotateRight(std::shared_ptr<Node>&, std::shared_ptr<Node>&);
    void fixViolation(std::shared_ptr<Node>&, std::shared_ptr<Node>&);

public:
    RBTree() { root = nullptr; }
    void insert(const int& n);
    void inorder();
    void levelOrder();

private:
    void inorderHelper(std::shared_ptr<Node> root);
    void levelOrderHelper(std::shared_ptr<Node> root);
};

#endif // RBTREE_H
