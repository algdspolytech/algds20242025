#pragma once

typedef struct
{
	int** List; //массив из списков
	int* sizes; //массив, который указывает, сколько смежных вершин у каждой вершины
	int N; //количество вершин графа
}Adj_list;


Adj_list ReadList(FILE* F);
int** Init_matrix(Adj_list m);
int** Construction_matrix(Adj_list m, int** matrix);

void Runtests();
