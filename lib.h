#pragma once


char* ReadStringFromFile(FILE* file);
int Colichestvo(const char* filename);
int** Create_Matrixx(int kol);
void FillMatrix(const char* filename, int** adjacencyMatrix, int vertexCount);
void Free_matr(int** Matrix, int kol);
void Print_Matrix(int** Matrix, int n);