#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 
#include "LabH.h"


Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1;
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}


int getHeight(Node* node) {
    return node ? node->height : 0;
}


int getSize(Node* node) {
    return node ? node->size : 0;
}


void update(Node* node) {
    if (node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        node->size = 1 + getSize(node->left) + getSize(node->right);
    }
}


Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* balance(Node* node) {
    if (!node) return node;
    update(node);
    int b = getBalance(node);
    if (b > 1) {
        if (getBalance(node->left) < 0)
            node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (b < -1) {
        if (getBalance(node->right) > 0)
            node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}


Node* find_kth(Node* root, int k) {
    if (!root || k <= 0 || k > getSize(root))
        return NULL;
    int leftSize = getSize(root->left);
    if (k == leftSize + 1)
        return root;
    else if (k <= leftSize)
        return find_kth(root->left, k);
    else
        return find_kth(root->right, k - leftSize - 1);
}


Node* search_by_key(Node* root, int key) {
    if (!root)
        return NULL;
    if (root->key == key)
        return root;
    Node* found = search_by_key(root->left, key);
    if (found)
        return found;
    return search_by_key(root->right, key);
}


Node* insert_at(Node* root, int pos, int key) {
    if (!root)
        return create_node(key);
    int leftSize = getSize(root->left);
    if (pos <= leftSize)
        root->left = insert_at(root->left, pos, key);
    else
        root->right = insert_at(root->right, pos - leftSize - 1, key);
    return balance(root);
}

Node* delete_at(Node* root, int pos) {
    if (!root)
        return NULL;
    int leftSize = getSize(root->left);
    if (pos < leftSize) {
        root->left = delete_at(root->left, pos);
    }
    else if (pos > leftSize) {
        root->right = delete_at(root->right, pos - leftSize - 1);
    }
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        else {
            Node* temp = root->right;
            while (temp->left)
                temp = temp->left;
            root->key = temp->key;
            root->right = delete_at(root->right, 0);
        }
    }
    return balance(root);
}


Node* extract_max(Node* root, Node** max_node) {
    if (!root->right) {
        *max_node = root;
        return root->left;
    }
    else {
        root->right = extract_max(root->right, max_node);
        return balance(root);
    }
}


Node* join_trees(Node* t1, Node* t2) {
    if (!t1) return t2;
    if (!t2) return t1;
    if (getHeight(t1) > getHeight(t2) + 1) {
        t1->right = join_trees(t1->right, t2);
        return balance(t1);
    }
    else if (getHeight(t2) > getHeight(t1) + 1) {
        t2->left = join_trees(t1, t2->left);
        return balance(t2);
    }
    else {
        Node* max = NULL;
        t1 = extract_max(t1, &max);
        max->left = t1;
        max->right = t2;
        return balance(max);
    }
}

void inorder_print(Node* root) {
    if (!root) return;
    inorder_print(root->left);
    printf("%d ", root->key);
    inorder_print(root->right);
}

int main(void) {
    setlocale(LC_CTYPE, "Russian");
    Node* list = NULL;

    list = insert_at(list, 0, 10);
    list = insert_at(list, 1, 20);
    list = insert_at(list, 2, 30);
    list = insert_at(list, 1, 15);

    inorder_print(list);
    printf("\n");

    Node* kth = find_kth(list, 3);

    Node* found = search_by_key(list, 20);

    list = delete_at(list, 1);
    inorder_print(list);
    printf("\n");

    Node* list2 = NULL;
    list2 = insert_at(list2, 0, 40);
    list2 = insert_at(list2, 1, 50);

    Node* joined = join_trees(list, list2);
    inorder_print(joined);
    printf("\n");

    return 0;
}