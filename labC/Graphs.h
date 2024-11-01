#pragma once

typedef struct
{
	int** List; //������ �� �������
	int* sizes; //������, ������� ���������, ������� ������� ������ � ������ �������
	int N; //���������� ������ �����
}Adj_list;


Adj_list ReadList(FILE* F);
int** Init_matrix(Adj_list m);
int** Construction_matrix(Adj_list m, int** matrix);

void Runtests();
