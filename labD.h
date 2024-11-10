
#define QUEENS_H
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

// ������� ��� ������� ������ N ������.
// �� ���� ������� ������ ����� N � ������ solution �������� N.
// ���� ������� �������, ���������� true � ��������� ������ solution,
// ��� solution[i] � ��� ����� ������� ����� � ������ i.
// ���� ������� ���, ���������� false.
bool solve_n_queens(int N, int* solution);

// ������� ��� ������ �������� N �� ����� input.txt.
// ���������� ����������� �������� N.
int read_input(const char* filename);

// ������� ��� ������ ������� � ���� output.txt.
// ��������� ������ solution �������� N � ������ ����� N.
bool write_output(const char* filename, int* solution, int N);

