#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"Graphs.h"


Adj_list ReadList(FILE* F)
{
	char c;
	Adj_list m;
	m.N = 1;

	//������� ���������� ����� (������ �����)
	while (fscanf(F, "%c", &c) != EOF)
	{
		if (c == '\n')
		{
			m.N++;
		}
	}
	rewind(F);//������������ � ������ �����

	m.List = malloc(m.N * sizeof(int*));
	if (m.List == NULL)
	{
		printf("������ ��������� ������.\n");
		return;
	}

	m.sizes = malloc(m.N * sizeof(int));
	if (m.sizes == NULL)
	{
		printf("������ ��������� ������.\n");
		return;
	}

	int i;
	int j = 0;
	char* s;
	char* s1;
	char* s2;
	int count;


	for (i = 0; i < m.N; i++)
	{
		s = malloc(100 * sizeof(char));
		if (s == NULL)
		{
			printf("������ ��������� ������.\n");
			return;
		}
		m.List[i] = NULL;
		m.sizes[i] = 0;

		count = 0;
		if (fgets(s, 100, F) != NULL)
		{
			//�������� �� ������ ������
			if (s[0] == '\n' || s[0] == '\0')
			{
				m.sizes[i] = count;
				m.List[i] = NULL;
				free(s);
				continue;
			}
			
			//������� ���������� ����� � ������
			s2 = strdup(s);
			s1 = strtok(s2, " ");
			while (s1 != NULL)
			{
				count++;
				s1 = strtok(NULL, " ");
			}
			
			m.sizes[i] = count;
			free(s2);
			
			//�������� ������ ��� ������
			m.List[i] = malloc(count * sizeof(int));
			if (m.List[i] == NULL)
			{
				printf("������ ��������� ������.\n");
				return;
			}
			//��������� ����� � ������
			j = 0;
			s1 = strtok(s, " ");
			while (s1 != NULL)
			{
				m.List[i][j] = atoi(s1);
				j++;
				s1 = strtok(NULL, " ");
			}
		}
		free(s);
	}

	return m;
}

//������������� �������, ���������� � ������
int** Init_matrix(Adj_list m)
{
	int** matrix = malloc(m.N * sizeof(int*));
	if (matrix == NULL)
	{
		printf("������ ��������� ������.\n");
		return;
	}
	int i;
	int j = 0;

	for (i = 0; i < m.N; i++)
	{
		matrix[i] = malloc(m.N * sizeof(int));
		if (matrix[i] == NULL)
		{
			printf("������ ��������� ������.\n");
			return;
		}
		for (j = 0; j < m.N; j++)
		{
			matrix[i][j] = 0;
		}
	}

	return matrix;
}


int** Construction_matrix(Adj_list m, int** matrix)
{
	int i;
	int j;

	for (i = 0; i < m.N; i++)
	{
		for (j = 0; j < m.sizes[i]; j++)
		{
			matrix[i][m.List[i][j]] = 1;
		}
	}

	return matrix;
}

void Print_matrix(int** matrix, Adj_list m)
{
	int i, j;

	for (i = 0; i < m.N; i++)
	{
		for (j = 0; j < m.N; j++)
		{
			printf("%i ", matrix[i][j]);
		}
		printf("\n");
	}
}


void main(void)
{
	FILE* F;
	setlocale(LC_ALL, "Russian");

	if ((F = fopen("List.txt", "r")) == NULL)
	{
		printf("The file List.txt was not opened\n");
	}
	
	Adj_list m;
	int** matrix;
	m = ReadList(F);
	printf("\n");
	printf("\n");
	matrix = Init_matrix(m);
	Print_matrix(matrix, m);
	printf("\n");
	printf("\n");
	matrix = Construction_matrix(m, matrix);
	Print_matrix(matrix, m);

	Runtests();
}