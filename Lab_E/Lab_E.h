#pragma once

typedef struct Tree {
    char* value;          // значение узла
    struct Tree* left;  // левый ребёнок
    struct Tree* right; // правый ребёнок
    int width;          // ширина поддерева
};

//Функция заполнения поля width передаваемого дерева
void Fill_width(Tree* tree);

// Функция вывода дерева в консоль. Корень слева, листья справа
void Print_Tree(Tree* tree, int depth);
