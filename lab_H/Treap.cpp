#include "Treap.hpp"

Node* CreateTreap() {
    return nullptr;
}

void ClearNode(Node* &element) {
    if (element) {
        ClearNode(element->left);
        ClearNode(element->right);
        delete element;
        element = nullptr;
    }
}

Node* merge(Node* first_treap_head, Node* second_treap_head) {
    if (first_treap_head == nullptr) {
        return second_treap_head;
    }
    if (second_treap_head == nullptr) {
        return first_treap_head;
    }
    if (first_treap_head->data.second > second_treap_head->data.second) {
        first_treap_head->right = merge(first_treap_head->right, second_treap_head);
        return first_treap_head;
    } else {
        second_treap_head->left = merge(first_treap_head, second_treap_head->left);
        return second_treap_head;
    }
}

std::pair<Node*, Node*> split(Node* treap_head, int key) {
    if (treap_head == nullptr) {
        return {nullptr, nullptr};
    }
    if (key > treap_head->data.first) {
        auto [first, second] = split(treap_head->right, key);
        treap_head->right = first;
        return {treap_head, second};
    } else {
        auto [first, second] = split(treap_head->left, key);
        treap_head->left = second;
        return {first, treap_head};
    }
}

void insert(Node*& treap_head, std::pair<int, int> data) {
    if (treap_head == nullptr) {
        treap_head = new Node();
        treap_head->data = data;
        return;
    }

    if (treap_head->data.second < data.second) {
        auto [left_treap, right_treap] = split(treap_head, data.first);
        Node* new_node = new Node();
        new_node->data = data;
        new_node->left = left_treap;
        new_node->right = right_treap;
        treap_head = new_node;
    } 
    else if (data.first < treap_head->data.first) {
        insert(treap_head->left, data);
    } 
    else {
        insert(treap_head->right, data);
    }
}

void remove(Node*& treap_head, int key) {
    if (treap_head == nullptr) return;

    if (key == treap_head->data.first) {
        Node* new_head = merge(treap_head->left, treap_head->right);
        delete treap_head;
        treap_head = new_head;
        return;
    } 
    else if (key < treap_head->data.first) {
        remove(treap_head->left, key);
    } 
    else {
        remove(treap_head->right, key);
    }
}
