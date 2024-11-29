#include <stdio.h>
#include <stdlib.h>

#include "lab.h"

tree *create_tree_node(int data) {
    tree *newNode = (tree *) malloc(sizeof(tree));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->width = 0;
    return newNode;
}

void delete_tree(tree *root) {
    if (root != NULL) {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}

unsigned get_num_width(int a) {
    int i = 0;
    if (a == 0) return 1;
    if (a < 0) i++;
    while (a != 0) {
        a /= 10;
        i++;
    }
    return i;
}

// Функция для вычисления ширины поддерева
unsigned count_widths(tree *root) {
    if (root == NULL) {
        return 0;
    }

    // Ширина узла - длина его представления в строковом виде
    int width = get_num_width(root->data);

    int leftWidth = count_widths(root->left);
    int rightWidth = count_widths(root->right);

    root->width = width + leftWidth + rightWidth;

    return root->width;
}

// Функция для печати узлов дерева по уровням
void printTree(tree *root, int space) {
    if (root == NULL) return;

    space += 4;

    printTree(root->right, space);

    for (int i = 4; i < space; i++) {
        printf(" ");
    }
    printf("%d (%d) \n", root->data, root->width);

    printTree(root->left, space);
}
