#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "main.h"

RBNode* new_node(int key, Color color) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = color;
    node->left = node->right = node->parent = NULL;
    return node;
}

int black_height(RBNode* root) {
    int bh = 0;
    while (root != NULL) {
        if(root->color == BLACK)
            bh++;
        root = root->left;
    }
    return bh + 1;
}

void left_rotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(RBNode **root, RBNode *x) {
    RBNode *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void rb_insert_fixup(RBNode **root, RBNode *x) {
    while (x != *root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            RBNode *y = x->parent->parent->right;
            if (y != NULL && y->color == RED) {
                // случай 1: переокрашиваем
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    // случай 2: поворот влево
                    x = x->parent;
                    left_rotate(root, x);
                }
                // случай 3: поворот вправо
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                right_rotate(root, x->parent->parent);
            }
        } else {
            // симметричный случай
            RBNode *y = x->parent->parent->left;
            if (y != NULL && y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    right_rotate(root, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                left_rotate(root, x->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

RBNode* rb_join(RBNode *S1, RBNode *x, RBNode *S2) {
    int bh1 = black_height(S1);
    int bh2 = black_height(S2);

    if (bh1 == bh2) {
        x->left = S1;
        if (S1) S1->parent = x;
        x->right = S2;
        if (S2) S2->parent = x;
        x->color = BLACK;
        return x;
    }
    else if (bh1 < bh2) {
        // Спускаемся по левому пути S2
        RBNode *p = S2;
        while (p->left && black_height(p->left) >= bh1)
            p = p->left;
        // Отсоединяем поддерево T = p->left, чтобы x вставлялся как лист
        RBNode *T = p->left;
        p->left = NULL;
        // Формируем новое поддерево с корнем x
        x->left = S1;
        if (S1) S1->parent = x;
        x->right = T;
        if (T) T->parent = x;
        x->color = RED;
        // Прикрепляем x как левый ребёнок узла p
        p->left = x;
        x->parent = p;
        // Исправляем возможные нарушения (теперь x – листовая вставка)
        rb_insert_fixup(&S2, x);
        return S2;
    }
    else {  // bh1 > bh2
        // Спускаемся по правому пути S1
        RBNode *p = S1;
        while (p->right && black_height(p->right) >= bh2)
            p = p->right;
        // Отсоединяем поддерево T = p->right
        RBNode *T = p->right;
        p->right = NULL;
        // Формируем новое поддерево с корнем x
        x->right = S2;
        if (S2) S2->parent = x;
        x->left = T;
        if (T) T->parent = x;
        x->color = RED;
        // Прикрепляем x как правый ребёнок узла p
        p->right = x;
        x->parent = p;
        rb_insert_fixup(&S1, x);
        return S1;
    }
}

int validate_rb_recursive(RBNode *node) {
    if (node == NULL) {
        return 1; // пустые листья считаем чёрными (концептуально)
    }

    // Проверка BST свойства
    if (node->left && node->left->key > node->key) {
        return -1;
    }
    if (node->right && node->right->key < node->key) {
        return -1;
    }

    // Проверка: если узел красный, то его дети должны быть чёрными
    if (node->color == RED) {
        if ((node->left && node->left->color == RED) ||
            (node->right && node->right->color == RED))
            return -1;
    }

    int left_bh = validate_rb_recursive(node->left);
    int right_bh = validate_rb_recursive(node->right);

    if (left_bh == -1 || right_bh == -1 || left_bh != right_bh) {
        return -1;
    }

    return left_bh + (node->color == BLACK ? 1 : 0);
}

void validate_rb_tree(RBNode *root) {
    // Корень должен быть чёрным.
    if (root) {
        assert(root->color == BLACK);
    }
    int bh = validate_rb_recursive(root);
    assert(bh != -1);
}

void inorder_traversal(RBNode *root, int *arr, int *index) {
    if (root == NULL) {
        return;
    }
    inorder_traversal(root->left, arr, index);
    arr[(*index)++] = root->key;
    inorder_traversal(root->right, arr, index);
}

void free_tree(RBNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}