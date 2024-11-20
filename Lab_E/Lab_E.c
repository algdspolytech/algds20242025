#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Tree {
    char* value;        // значение узла
    struct Tree* left;  // левый ребёнок
    struct Tree* right; // правый ребёнок
    int width;          // ширина поддерева
} Tree;
// Функция заполнения поля width передаваемого дерева
void Fill_width(Tree* tree) {
    int value_width, left_width, right_width;
    if (tree == NULL) {
        return;
    }
    if (tree->left != NULL) {
        Fill_width(tree->left);
        left_width = tree->left->width;
    } else {
        left_width = 0;
    }
    if (tree->right != NULL) {
        Fill_width(tree->right);
        right_width = tree->right->width;
    } else {
        right_width = 0;
    }
    value_width = (int)strlen(tree->value);
    tree->width = value_width + left_width + right_width;
}

// Функция вывода дерева в консоль
void Print_Tree(Tree* tree, int depth) {
    if (tree == NULL) {
        return;
    }
    Print_Tree(tree->left, depth + 1);
    printf("%*s%s\n", depth * 4, "", tree->value);
    printf("%*s(%d)\n", depth * 4, "", tree->width);
    Print_Tree(tree->right, depth + 1);
}
