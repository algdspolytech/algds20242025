#pragma once

//флаги
typedef enum Flag_t {
	NO,
	YES
} Flag_t;

//проверить, можно ли поставить ферзя в данную позицию
int CheckPos(Flag_t** board, int i, int j, int size);

//найти решение задачи для доски n x n
int FindSolution(int n, Flag_t** board, int m);

//основная функция - найти решение с чтением n из файла и выводом решения в файл
int NQueens(char* inputFilename, char* outputFilename);