#include <stdio.h>
#include <stdlib.h>
#include "redblack.h"

// создание новго узла
static Node* new_node(int data, Color color, Node* nil) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = color;
    node->left = node->right = node->parent = nil;
    return node;
}

// инициализация дерева
void init_rbtree(RBTree* tree) {
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->color = BLACK; // лист должен быть чёрным
    tree->nil->left = tree->nil->right = tree->nil->parent = tree->nil;
    tree->root = tree->nil; // у пустого дерева есть только листовой (пустой) элемент
}

// освобождение памяти узлов
static void free_node(RBTree* tree, Node* node) {
    if (node == tree->nil) return;
    free_node(tree, node->left);
    free_node(tree, node->right);
    free(node);
}

void free_tree(RBTree* tree) {
    free_node(tree, tree->root);
    free(tree->nil);
}

// поиск элемента
Node* search(const RBTree* tree, int data) {
    Node* current = tree->root;
    while (current != tree->nil) {
        if (data == current->data)
            return current;
        current = (data < current->data) ? current->left : current->right;
    }
    return NULL;
}

// левый поворот
static void left_rotate(RBTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == tree->nil)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// правый поворот
static void right_rotate(RBTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != tree->nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == tree->nil)
        tree->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

// коррекция дерева посел вставки
static void insert_fixup(RBTree* tree, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// вставка элемента
void insert(RBTree* tree, int data) {
    Node* z = new_node(data, RED, tree->nil);
    Node* y = tree->nil;
    Node* x = tree->root;

    while (x != tree->nil) {
        y = x;
        x = (z->data < x->data) ? x->left : x->right;
    }

    z->parent = y;
    if (y == tree->nil)
        tree->root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insert_fixup(tree, z);
}

// поиск минимального узла
static Node* minimum(RBTree* tree, Node* x) {
    while (x->left != tree->nil)
        x = x->left;
    return x;
}

// корректировка после удаления
static void delete_fixup(RBTree* tree, Node* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

// удаление элемента
void delete(RBTree* tree, int data) {
    Node* z = search(tree, data);
    if (!z) return;

    Node* y = z;
    Node* x;
    Color y_original_color = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        if (z->parent == tree->nil)
            tree->root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        x->parent = z->parent;
    }
    else if (z->right == tree->nil) {
        x = z->left;
        if (z->parent == tree->nil)
            tree->root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        x->parent = z->parent;
    }
    else {
        y = minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            if (y->parent == tree->nil)
                tree->root = x;
            else if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
            x->parent = y->parent;
            y->right = z->right;
            y->right->parent = y;
        }
        if (z->parent == tree->nil)
            tree->root = y;
        else if (z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
        y->parent = z->parent;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK)
        delete_fixup(tree, x);
    free(z);
}

// вспомогательная функция для печати
static void print_helper(const RBTree* tree, Node* node, int indent) {
    if (node == tree->nil) return;
    printf("%*s%d(%s)\n", indent, "", node->data,
        node->color == RED ? "R" : "B");
    print_helper(tree, node->left, indent + 4);
    print_helper(tree, node->right, indent + 4);
}

// рекурсивная печать
void print_tree(const RBTree* tree) {
    print_helper(tree, tree->root, 0);
    printf("\n");
}