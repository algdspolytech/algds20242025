
#define QUEENS_H
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

// Функция для решения задачи N ферзей.
// На вход подаётся размер доски N и массив solution размером N.
// Если решение найдено, возвращает true и заполняет массив solution,
// где solution[i] — это номер столбца ферзя в строке i.
// Если решения нет, возвращает false.
bool solve_n_queens(int N, int* solution);

// Функция для чтения значения N из файла input.txt.
// Возвращает прочитанное значение N.
int read_input(const char* filename);

// Функция для записи решения в файл output.txt.
// Принимает массив solution размером N и размер доски N.
bool write_output(const char* filename, int* solution, int N);

