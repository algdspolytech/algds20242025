﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "NQueens.h"

/*
* Проверить, можно ли поставить ферзя в данную позицию
*
* Проверяется, не стоит ли ферзь в какой-то клетке по горизонтали, по диагонали вниз-влево и
* по диагонали вверх-влево. Остальные направления проверять нет необходимости по построению.
*
* Параметры:
* board - таблица с флагами. Значение флага NO означает, что в данной клетке доски ничего не
* не стоит, YES - что стоит ферзь.
* i, j - координаты клетки
* size - размер доски
*/
int CheckPos(Flag_t** board, int i, int j, int size) {
	for (int k = 0; k < size; k++) { //строка
		if (board[i][k] == YES) {
			return 0;
		}
	}

	for (int k = 1; (i - k >= 0) && (j - k >= 0); k++) { //по диаг вниз и влево
		if (board[i - k][j - k] == YES) {
			return 0;
		}
	}

	for (int k = 1; (i + k < size) && (j - k >= 0); k++) { //по диаг вверх и влево
		if (board[i + k][j - k] == YES) {
			return 0;
		}
	}

	return 1;
}

/*
* Найти решение задачи для доски n x n
*
* Параметры:
* board - таблица с флагами
* n - размер доски
* m - количество уже поставленных ферзей
*
* m-ый ферзь ставится в m-ую строку
*
* Возвращает: 1 - если решение найдено, 0 - если в какую-то строку оказалось невозможно
* поставить ферзя.
*/
int FindSolution(int n, Flag_t** board, int m) {
	if (m >= n) {
		return 1;
	}
	else {
		for (int i = 0; i < n; i++) {
			if (CheckPos(board, i, m, n) == 1) {
				board[i][m] = YES;
				int sol = FindSolution(n, board, m + 1);
				if (sol == 1) {
					return 1;
				}
				else {
					board[i][m] = NO;
				}
			}
		}
		return 0;
	}
}

/*
* Основная функция - найти решение с чтением n из файла и выводом решения в файл
*
* Параметры:
* inputFilename - название файла, где записан размер доски
* outputFilename - название файла, куда записывается решение
*
* Возращает: 1 - если решение найдено, 0 - если произошла ошибка при открытии какого-либо из
* файлов, размер доски некорректен или решение не существует для данного размера доски
*
* При записи решения в файл отсчет координат ферзя ведется от нижнего левого угла
*/
int NQueens(char* inputFilename, char* outputFilename) {
	FILE* inputFile = fopen(inputFilename, "r");
	if (inputFile == NULL) {
		printf("error opening input file!\n");
		return 0;
	}
	int n;
	fscanf(inputFile, "%d", &n);
	if (n <= 0) {
		printf("invalid board size!\n");
		return 0;
	}
	fclose(inputFile);

	Flag_t** board = (Flag_t**)malloc(sizeof(Flag_t*) * n);
	for (int i = 0; i < n; i++) {
		board[i] = (Flag_t*)malloc(sizeof(Flag_t) * n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = NO;
		}
	}

	int sol = FindSolution(n, board, 0);

	FILE* outputFile = fopen(outputFilename, "w");
	if (outputFile == NULL) {
		for (int i = 0; i < n; i++) {
			free(board[i]);
		}
		free(board);
		printf("error opening output file!\n");
		return 0;
	}
	if (sol == 0) {
		for (int i = 0; i < n; i++) {
			free(board[i]);
		}
		free(board);
		printf("no solution!\n");
		fprintf(outputFile, "no solution!\n");
		fclose(outputFile);
		return 0;
	}

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == YES) {
				fprintf(outputFile, "%d %d\n", n - 1 - i, j);
			}
		}
	}
	fclose(outputFile);

	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);
	return 1;
}