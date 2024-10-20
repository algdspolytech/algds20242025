#pragma once
#include "pch.h"
#include <stdio.h>

// ������� ��� ���������� ������ �� �����
char* Read_line(FILE* file);

// ������� ��� ������������ ������, ���������� ��� �������
void Free_Matrix_adj(int** adjMatrix, int vertices);

// ������� ��� ����������� ���������� ������ (�� ���������� ����� � �����)
int Count_Vertices(const char* filename);

// ������� ��� �������� ������� ��������� � ������������� � ������
int** Create_Matrix_adj(int vertices);

// ������� ��� ���������� ������� ��������� �� ������ �����
void Parsing_Matrix_adj(const char* filename, int** Matrix_adj, int vertices);

// ������� ��� ������ ���������� �������
void Print_Matrix(int** Matrix, int n);
