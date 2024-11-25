#pragma once

//Дерево с доп. информацией
typedef struct Tree {
	int data; //значение в узле
	struct Tree* left; //левый сын
	struct Tree* right; //правый сын
	int width; //ширина поддерева
} Tree_t;

//Количество разрядов в числе
int DataWidth(int data);

//Ширина поддеревьев
void TreeWidth(Tree_t* tree);

//Высота дерева
int TreeHeight(Tree_t* tree);

//Перевод цифры в символ
char IntToChar(int digit);

//Запись числа в матрицу
void WriteData(int data, char** matrix, int x, int y);

//Запись дерева в матрицу
void TreeToMatrix(Tree_t* tree, char** matrix, int* x, int y);

//Печать дерева
void PrintTree(Tree_t* tree);