#include <algorithm>
struct Node {
    std::pair<int, int> data; // 1 - key, 2 - priority
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* CreateTreap();
std::pair<Node*, Node*> split(Node* treap_head, int key);
Node* merge(Node* first_treap_head, Node* second_treap_head);
void insert(Node*& treap_head, std::pair<int, int> data);
void remove(Node*& treap_head, int key);
void ClearNode(Node* &element);