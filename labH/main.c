#include "labH.h"
#include "testH.h"

int GetSize(Node *node) {
    return node ? node->size : 0;
}

void UpdateSize(Node *node) {
    if (node) {
        node->size = GetSize(node->left) + GetSize(node->right) + 1;
    }
}

Node *Merge(Node *left, Node *right) {
    if (!left) return right;
    if (!right) return left;

    if (left->pr > right->pr) {
        left->right = Merge(left->right, right);
        UpdateSize(left);  // Обновляем размер поддерева
        return left;
    } else {
        right->left = Merge(left, right->left);
        UpdateSize(right);  // Обновляем размер поддерева
        return right;
    }
}

void Split(Node* root, int x, Node** left, Node** right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }

    if (root->x <= x) {
        Split(root->right, x, &(root->right), right);
        *left = root;
    } else {
        Split(root->left, x, left, &(root->left));
        *right = root;
    }
    UpdateSize(root);  // Обновляем размер поддерева
}

Node *NewNode(int x, int c) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node) {
        printf("Error allocating memory for new node.\n");
        exit(1);
    }
    node->x = x;
    node->c = c;
    node->pr = rand()%100;
    node->left = NULL;
    node->right = NULL;
    node->size = 1;
    return node;
}

Node* Insert(Node* root, int x, int c) {
    if (!root) {
        return NewNode(x, c);
    }
    Node* newNode = NewNode(x, c);
    Node *left, *right;
    Split(root, x, &left, &right);
    return Merge(Merge(left, newNode), right);
}

int FindMax(Node* root, int x, int y) {
    if (!root) return INT_MIN;
    int max_c = INT_MIN;

    // check the current node
    if (x <= root->x && root->x < y) {
        if (root->c > max_c) {
            max_c = root->c;
        }
    }

    // check left and right subtree in recursion
    if (root->x >= x) {
        int left_max = FindMax(root->left, x, y);
        if (left_max > max_c) {
            max_c = left_max;
        }
    }
    if (root->x < y) {
        int right_max = FindMax(root->right, x, y);
        if (right_max > max_c) {
            max_c = right_max;
        }
    }

    return max_c;
}

int main(){
    test();
}