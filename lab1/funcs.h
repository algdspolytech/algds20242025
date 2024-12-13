#pragma once
#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура узла бинарного дерева
typedef struct TreeNode {
    char* word;                // Слово в узле
    int width;                 // Ширина поддерева
    struct TreeNode* left;     // Левый ребенок
    struct TreeNode* right;    // Правый ребенок
} TreeNode;

TreeNode* createNode(const char* word);
int computeWidth(TreeNode* node);
void printTree(TreeNode* node, int depth);
void freeTree(TreeNode* node);


#endif
