#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include"Gamilton_path.h"
#include<assert.h>
#include<string.h>

void test_ReadLine_single_line_no1()
{
	FILE* f;

	if ((f = fopen("test2.txt", "w")) == NULL)
	{
		printf("The file test2.txt was not opened\n");
	}
	fprintf(f, "1\n1");
	fclose(f);

	if ((f = fopen("test2.txt", "r")) == NULL)
	{
		printf("The file test2.txt was not opened\n");
	}
	Adj_list result = ReadList(f);
	fclose(f);

	assert(result.N == 1);
	assert(result.sizes[0] == 1);
	assert(result.List[0][0] == 0);
}

void test_ReadLine_3vertex_no2()
{
	FILE* f;

	if ((f = fopen("test3.txt", "w")) == NULL)
	{
		printf("The file test3.txt was not opened\n");
	}

	fprintf(f, "3\n2\n3\n1");
	fclose(f);

	if ((f = fopen("test3.txt", "r")) == NULL)
	{
		printf("The file test3.txt was not opened\n");
	}
	Adj_list result = ReadList(f);
	fclose(f);

	assert(result.N == 3);
	assert(result.sizes[0] == 1 && result.sizes[1] == 1 && result.sizes[2] == 1);
	assert(result.List[0][0] == 1);
	assert(result.List[1][0] == 2);
	assert(result.List[2][0] == 0);
}

void test_ReadLine_12vertex_no3()
{
	FILE* f;

	if ((f = fopen("test4.txt", "w")) == NULL)
	{
		printf("The file test4.txt was not opened\n");
	}

	fprintf(f, "12\n2 7\n8 3\n9\n9\n12\n5 12\n2 8\n3\n10\n4 5 11\n5 12\n12");
	fclose(f);

	if ((f = fopen("test4.txt", "r")) == NULL)
	{
		printf("The file test4.txt was not opened\n");
	}
	Adj_list result = ReadList(f);
	fclose(f);

	assert(result.N == 12);
	assert(result.sizes[0] == 2 && result.sizes[1] == 2 && result.sizes[2] == 1 && result.sizes[3] == 1 && result.sizes[4] == 1 && result.sizes[5] == 2 && result.sizes[6] == 2 && result.sizes[7] == 1 && result.sizes[8] == 1 && result.sizes[9] == 3 && result.sizes[10] == 2 && result.sizes[11] == 1);
	assert(result.List[0][0] == 1);
	assert(result.List[0][1] == 6);
	assert(result.List[1][0] == 7);
	assert(result.List[1][1] == 2);
	assert(result.List[2][0] == 8);
	assert(result.List[3][0] == 8);
	assert(result.List[4][0] == 11);
	assert(result.List[5][0] == 4);
	assert(result.List[5][1] == 11);
	assert(result.List[6][0] == 1);
	assert(result.List[6][1] == 7);
	assert(result.List[7][0] == 2);
	assert(result.List[8][0] == 9);
	assert(result.List[9][0] == 3);
	assert(result.List[9][1] == 4);
	assert(result.List[9][2] == 10);
	assert(result.List[10][0] == 4);
	assert(result.List[10][1] == 11);
	assert(result.List[11][0] == 11);
}

void test_Construction_matrix_MultipleVertex_no4()
{
	Adj_list m;
	m.N = 3;
	m.sizes = malloc(3 * sizeof(int));
	m.List = malloc(3 * sizeof(int*));

	m.sizes[0] = 2;
	m.List[0] = malloc(2 * sizeof(int));
	m.List[0][0] = 1;
	m.List[0][1] = 2;

	m.sizes[1] = 1;
	m.List[1] = malloc(sizeof(int));
	m.List[1][0] = 2;

	m.sizes[2] = 1;
	m.List[2] = malloc(sizeof(int));
	m.List[2][0] = 0;

	int** matrix = Init_matrix(m);
	matrix = Construction_matrix(m, matrix);

	assert(matrix[0][1] == 1);
	assert(matrix[0][2] == 1);
	assert(matrix[1][2] == 1);
	assert(matrix[2][0] == 1);
}

void test_Construction_matrix_1vertex_no5()
{
	Adj_list m;
	m.N = 1;
	m.sizes = malloc(sizeof(int));
	m.List = malloc(sizeof(int*));

	m.sizes[0] = 1;
	m.List[0] = malloc(sizeof(int));
	m.List[0][0] = 0;

	int** matrix = Init_matrix(m);
	matrix = Construction_matrix(m, matrix);
	assert(matrix[0][0] == 1);
}

void test_Construction_matrix_NoEdges_no6()
{
	Adj_list m;
	m.N = 2;
	m.sizes = malloc(2 * sizeof(int));
	m.List = malloc(2 * sizeof(int*));

	m.sizes[0] = 0;
	m.List[0] = NULL;
	m.sizes[1] = 0;
	m.List[1] = NULL;
	int** matrix = Init_matrix(m);
	matrix = Construction_matrix(m, matrix);

	for (int i = 0; i < m.N; i++)
	{
		for (int j = 0; j < m.N; j++)
		{
			assert(matrix[i][j] == 0);
		}
	}

}

void test_Find_Gamiltonian_Path_Linear_no7()
{
	FILE* f;

	if ((f = fopen("test5.txt", "w")) == NULL)
	{
		printf("The file test5.txt was not opened\n");
	}

	fprintf(f, "4\n2\n1 3\n2 4\n3");
	fclose(f);

	if ((f = fopen("test5.txt", "r")) == NULL)
	{
		printf("The file test5.txt was not opened\n");
	}
	Adj_list m;
	m.N = 4;
	fclose(f);
	int** matrix = Init_matrix(m);
	matrix[0][1] = matrix[1][0] = matrix[1][2] = matrix[2][1] = matrix[2][3] = matrix[3][2] = 1;
	bool* visited = malloc(4 * sizeof(bool));
	if (visited == NULL)
	{
		printf("Ошибка выделения памяти.\n");
		return;
	}
	int* path = malloc(4 * sizeof(int));
	if (path == NULL)
	{
		printf("Ошибка выделения памяти.\n");
		return;
	}

	Find_Gamiltonian_Path(matrix, visited, path, 4);

	FILE* f1;
	if ((f1 = fopen("output.txt", "r")) == NULL)
	{
		printf("The file output.txt was not opened\n");
	}
	char buf[256];
	if (fgets(buf, sizeof(buf), f1) == NULL)
	{
		printf("Файл пуст или произошла ошибка чтения\n");
		fclose(f1);
		return 0;
	}
	fclose(f1);
	assert(strcmp(buf, "1 2 3 4 ") == 0);

}

void test_Find_Gamiltonian_Path_Triangle_no8()
{
	FILE* f;

	if ((f = fopen("test6.txt", "w")) == NULL)
	{
		printf("The file test6.txt was not opened\n");
	}

	fprintf(f, "3\n2 3\n1 3\n1 2");
	fclose(f);

	if ((f = fopen("test6.txt", "r")) == NULL)
	{
		printf("The file test6.txt was not opened\n");
	}
	Adj_list m;
	m.N = 3;
	fclose(f);
	int** matrix = Init_matrix(m);
	matrix[0][1] = matrix[0][2] = matrix[1][0] = matrix[1][2] = matrix[2][0] = matrix[2][1] = 1;
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

	FILE* f1;
	if ((f1 = fopen("output.txt", "r")) == NULL)
	{
		printf("The file output.txt was not opened\n");
	}
	char buf[256];
	if (fgets(buf, sizeof(buf), f1) == NULL)
	{
		printf("Файл пуст или произошла ошибка чтения\n");
		fclose(f1);
		return 0;
	}
	fclose(f1);
	assert(strcmp(buf, "1 2 3 ") == 0);
}

void test_Find_Gamiltonian_Path_Star_no9()
{
	FILE* f;

	if ((f = fopen("test7.txt", "w")) == NULL)
	{
		printf("The file test7.txt was not opened\n");
	}

	fprintf(f, "5\n2 3 4 5\n1\n1\n1\n1");
	fclose(f);

	if ((f = fopen("test7.txt", "r")) == NULL)
	{
		printf("The file test7.txt was not opened\n");
	}
	Adj_list m;
	m.N = 5;
	fclose(f);
	int** matrix = Init_matrix(m);
	matrix[0][1] = matrix[0][2] = matrix[0][3] = matrix[0][4] = matrix[1][0] = matrix[2][0] = matrix[3][0] = matrix[4][0] = 1;
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

	FILE* f1;
	if ((f1 = fopen("output.txt", "r")) == NULL)
	{
		printf("The file output.txt was not opened\n");
	}
	char buf[256];
	if (fgets(buf, sizeof(buf), f1) == NULL)
	{
		printf("Файл пуст или произошла ошибка чтения\n");
		fclose(f1);
		return 0;
	}
	fclose(f1);
	assert(strcmp(buf, "0") == 0);
}

void test_Find_Gamiltonian_Path_Tree_no10()
{
	FILE* f;

	if ((f = fopen("test8.txt", "w")) == NULL)
	{
		printf("The file test8.txt was not opened\n");
	}

	fprintf(f, "5\n2\n1 3\n2 4 5\n3\n3");
	fclose(f);

	if ((f = fopen("test8.txt", "r")) == NULL)
	{
		printf("The file test8.txt was not opened\n");
	}
	Adj_list m;
	m.N = 5;
	fclose(f);
	int** matrix = Init_matrix(m);
	matrix[0][1] = matrix[1][0] = matrix[1][2] = matrix[2][1] = matrix[2][3] = matrix[2][4] = matrix[3][2] = matrix[4][2] = 1;
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

	FILE* f1;
	if ((f1 = fopen("output.txt", "r")) == NULL)
	{
		printf("The file output.txt was not opened\n");
	}
	char buf[256];
	if (fgets(buf, sizeof(buf), f1) == NULL)
	{
		printf("Файл пуст или произошла ошибка чтения\n");
		fclose(f1);
		return 0;
	}
	fclose(f1);
	assert(strcmp(buf, "0") == 0);
}

void test_Find_Gamiltonian_Path_no11()
{
	FILE* f;

	if ((f = fopen("test9.txt", "w")) == NULL)
	{
		printf("The file test9.txt was not opened\n");
	}

	fprintf(f, "5\n2 3\n1 4\n1 4\n2 3 5\n4");
	fclose(f);

	if ((f = fopen("test9.txt", "r")) == NULL)
	{
		printf("The file test9.txt was not opened\n");
	}
	Adj_list m;
	m.N = 5;
	fclose(f);
	int** matrix = Init_matrix(m);
	matrix[0][1] = matrix[0][2] = matrix[1][0] = matrix[1][3] = matrix[2][0] = matrix[2][3] = matrix[3][1] = matrix[3][2] = matrix[3][4] = matrix[4][3] = 1;
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

	FILE* f1;
	if ((f1 = fopen("output.txt", "r")) == NULL)
	{
		printf("The file output.txt was not opened\n");
	}
	char buf[256];
	if (fgets(buf, sizeof(buf), f1) == NULL)
	{
		printf("Файл пуст или произошла ошибка чтения\n");
		fclose(f1);
		return 0;
	}
	fclose(f1);
	assert(strcmp(buf, "2 1 3 4 5 ") == 0);
}

void Runtests()
{
	test_ReadLine_single_line_no1();
	test_ReadLine_3vertex_no2();
	test_ReadLine_12vertex_no3();
	test_Construction_matrix_MultipleVertex_no4();
	test_Construction_matrix_1vertex_no5();
	test_Construction_matrix_NoEdges_no6();
	test_Find_Gamiltonian_Path_Linear_no7();
	test_Find_Gamiltonian_Path_Triangle_no8();
	test_Find_Gamiltonian_Path_Star_no9();
	test_Find_Gamiltonian_Path_Tree_no10();
	test_Find_Gamiltonian_Path_no11();

	printf("All tests were successful!\n");
}