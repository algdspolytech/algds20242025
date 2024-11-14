#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<locale.h>
#include"Gamilton_path.h"


Adj_list ReadList(FILE* F)
{
	char c;
	Adj_list m;
	m.N = 1;

	//количество вершин графа
	if (fscanf(F, "%i", &m.N) == EOF)
	{
		printf("Неправильно заполнен файл\n");
		return;
	}
	//while (fgetc(F) != '\n' && !feof(F));
	while (fgetc(F) != '\n');

	m.List = malloc(m.N * sizeof(int*));
	if (m.List == NULL)
	{
		printf("Ошибка выделения памяти.\n");
		return;
	}

	m.sizes = malloc(m.N * sizeof(int));
	if (m.sizes == NULL)
	{
		printf("Ошибка выделения памяти.\n");
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
			printf("Ошибка выделения памяти.\n");
			return;
		}
		m.List[i] = NULL;
		m.sizes[i] = 0;

		count = 0;
		if (fgets(s, 100, F) != NULL)
		{
			//проверка на пустую строку
			if (s[0] == '\n' || s[0] == '\0')
			{
				m.sizes[i] = count;
				m.List[i] = NULL;
				free(s);
				continue;
			}

			//считаем количество чисел в строке
			s2 = strdup(s);
			s1 = strtok(s2, " ");
			while (s1 != NULL)
			{
				count++;
				s1 = strtok(NULL, " ");
			}

			m.sizes[i] = count;
			free(s2);

			//выделяем память для строки
			m.List[i] = malloc(count * sizeof(int));
			if (m.List[i] == NULL)
			{
				printf("Ошибка выделения памяти.\n");
				return;
			}
			//считываем числа в массив
			j = 0;
			s1 = strtok(s, " ");
			while (s1 != NULL)
			{
				m.List[i][j] = atoi(s1) - 1;
				j++;
				s1 = strtok(NULL, " ");
			}
		}
		free(s);
	}

	return m;
}

//инициализация матрицы, заполнение её нулями
int** Init_matrix(Adj_list m)
{
	int** matrix = malloc(m.N * sizeof(int*));
	if (matrix == NULL)
	{
		printf("Ошибка выделения памяти.\n");
		return;
	}
	int i;
	int j = 0;

	for (i = 0; i < m.N; i++)
	{
		matrix[i] = malloc(m.N * sizeof(int));
		if (matrix[i] == NULL)
		{
			printf("Ошибка выделения памяти.\n");
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

bool Gamilton_Path2(int pos, int** matrix, bool* visited, int* path, int n)
{
	if (pos == n)
	{
		return true;
	}

	int last = path[pos - 1];
	int next;

	for (next = 0; next < n; next++)
	{
		if (matrix[last][next] == 1 && visited[next] != true)
		{
			path[pos] = next;
			visited[next] = true;
			if (Gamilton_Path2(pos + 1, matrix, visited, path, n))
			{
				return true;
			}
			visited[next] = false;
		}
	}

	return false;
}

void Find_Gamiltonian_Path(int** matrix, bool* visited, int* path, int n)
{
	int i, j, k;
	FILE* F;

	for (i = 0; i < n; i++)
	{
		path[0] = i;
		for (k = 0; k < n; k++)
		{
			visited[k] = false;
		}
		visited[i] = true;

		if (Gamilton_Path2(1, matrix, visited, path, n))
		{
			if ((F = fopen("output.txt", "w")) == NULL)
			{
				printf("The file output.txt was not opened\n");
			}
			for (j = 0; j < n; j++)
			{
				fprintf(F, "%i ", path[j] + 1);
			}
			fclose(F);
			return;
		}
		visited[i] = false;
	}
	if ((F = fopen("output.txt", "w")) == NULL)
	{
		printf("The file output.txt was not opened\n");
	}
	fprintf(F, "%i", 0);
	fclose(F);
}

void main(void)
{
	FILE* F;
	setlocale(LC_ALL, "Russian");

	if ((F = fopen("input.txt", "r")) == NULL)
	{
		printf("The file input.txt was not opened\n");
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


	bool* visited = malloc(m.N * sizeof(bool));
	if (visited == NULL)
	{
		printf("Ошибка выделения памяти.\n");
		return;
	}
	int* path = malloc(m.N * sizeof(int));
	if (path == NULL)
	{
		printf("Ошибка выделения памяти.\n");
		return;
	}

	Find_Gamiltonian_Path(matrix, visited, path, m.N);

	Runtests();
}

