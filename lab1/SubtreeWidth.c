#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "SubtreeWidth.h"

/*
* Количество разрядов в числе - ширина данных в одном узле
*/
int DataWidth(int data) {
	int width = 1;
	while (data / 10 > 0) {
		data /= 10;
		width++;
	}
	return width;
}

/*
* Ширина поддеревьев 
* 
* Записывает в поле width каждого узла ширину соответствующего поддерева
*/
void TreeWidth(Tree_t* tree) {
	int lwidth, rwidth, datawidth;

	if (tree != NULL) {
		datawidth = DataWidth(tree->data);
	}
	else {
		return;
	}

	if (tree->left != NULL) {
		TreeWidth(tree->left);
		lwidth = tree->left->width;
	}
	else {
		lwidth = 0;
	}

	if (tree->right != NULL) {
		TreeWidth(tree->right);
		rwidth = tree->right->width;
	}
	else {
		rwidth = 0;
	}

	tree->width = datawidth + lwidth + rwidth;
}

/*
* Высота дерева
*/
int TreeHeight(Tree_t* tree) {
	int lheight, rheight;
	if (tree == NULL) {
		return 0;
	}
	lheight = TreeHeight(tree->left);
	rheight = TreeHeight(tree->right);
	if (lheight > rheight) {
		return lheight + 1;
	}
	else {
		return rheight + 1;
	}
}

/*
* Перевод цифры в символ
*/
char IntToChar(int digit) {
	if (digit > 9) {
		return 0;
	}
	return '0' + digit;
}

/*
* Запись числа в матрицу
* 
* Число data записывается в матрицу matrix по горизонтали начиная с matrix[y][x]
*/
void WriteData(int data, char** matrix, int x, int y) {
	int width = DataWidth(data);
	int power;
	for (int i = 0; i < width; i++) {
		power = pow(10, width - 1 - i);
		matrix[y][x + i] = IntToChar(data / power);
		data %= power;
	}
}

/*
* Запись дерева в матрицу
*/
void TreeToMatrix(Tree_t* tree, char** matrix, int* x, int y) {
	if (tree != NULL) {
		TreeToMatrix(tree->left, matrix, x, y + 2);
		int width = DataWidth(tree->data);
		int data = tree->data;
		int power;
		WriteData(tree->data, matrix, *x, y);
		WriteData(tree->width, matrix, *x, y + 1);
		*x += DataWidth(tree->data);
		TreeToMatrix(tree->right, matrix, x, y + 2);
	}
}

/*
* Печать дерева
* 
* Записывает дерево в матрицу, затем выводит ее на экран
*/
void PrintTree(Tree_t* tree) {
	TreeWidth(tree);
	int matrixHeight = TreeHeight(tree) * 2;
	char** matrix = (char**)malloc(sizeof(char*) * matrixHeight);
	for (int i = 0; i < matrixHeight; i++) {
		matrix[i] = (char*)malloc(sizeof(char) * tree->width);
	}
	for (int i = 0; i < matrixHeight; i++) {
		for (int j = 0; j < tree->width; j++) {
			matrix[i][j] = ' ';
		}
	}

	int x = 0;
	TreeToMatrix(tree, matrix, &x, 0);

	for (int i = 0; i < matrixHeight; i++) {
		for (int j = 0; j < tree->width; j++) {
			printf("%c", matrix[i][j]);
			if (j == tree->width - 1) {
				printf("\n");
			}
		}
	}

	for (int i = 0; i < matrixHeight; i++) {
		free(matrix[i]);
	}
	free(matrix);
}