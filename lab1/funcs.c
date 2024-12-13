#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include "funcs.h"


// Создание нового узла
TreeNode* createNode(const char* word) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->word = strdup(word); // Копируем слово
    node->width = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Вычисление ширины поддерева каждого узла
int computeWidth(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }

    // Рекурсивно вычисляем ширину левого и правого поддеревьев
    int leftWidth = computeWidth(node->left);
    int rightWidth = computeWidth(node->right);

    // Ширина текущего узла = длина его слова + ширины поддеревьев
    node->width = strlen(node->word) + leftWidth + rightWidth;
    return node->width;
}

// Печать дерева с ширинами под словами
void printTree(TreeNode* node, int depth) {
    if (node == NULL) {
        return;
    }

    // Печатаем правое поддерево
    printTree(node->right, depth + 1);

    // Печатаем слово и ширину
    for (int i = 0; i < depth; i++) {
        printf("   "); // Отступ для уровня глубины
    }
    printf("%s\n", node->word);
    for (int i = 0; i < depth; i++) {
        printf("   "); // Отступ для уровня глубины
    }
    printf("%*d\n", (int)(strlen(node->word) / 2 + 1), node->width);

    // Печатаем левое поддерево
    printTree(node->left, depth + 1);
}

// Освобождение памяти, занятой деревом
void freeTree(TreeNode* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node->word);
    free(node);
}