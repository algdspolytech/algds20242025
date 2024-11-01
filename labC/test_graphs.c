#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include"Graphs.h"
#include<assert.h>

void test_ReadLine_empty_graph_no1()
{
	FILE* f;

	if ((f = fopen("test1.txt", "r")) == NULL)
	{
		printf("The file test1.txt was not opened\n");
	}

	Adj_list result = ReadList(f);
	fclose(f);

	assert(result.N == 1);
	assert(result.sizes[0] == 0);
	assert(result.List != NULL);
}

void test_ReadLine_single_line_no2()
{
	FILE* f;

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

void test_ReadLine_3vertex_no3()
{
	FILE* f;

	if ((f = fopen("test3.txt", "w")) == NULL)
	{
		printf("The file test3.txt was not opened\n");
	}

	fprintf(f, "1\n2\n0");
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

void test_ReadLine_12vertex_no4()
{
	FILE* f;

	if ((f = fopen("test4.txt", "w")) == NULL)
	{
		printf("The file test4.txt was not opened\n");
	}

	fprintf(f, "1 6\n7 2\n8\n8\n11\n4 11\n1 7\n2\n9\n3 4 10\n4 11\n11");
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

void test_Init_matrix_1vertex_no5()
{
	Adj_list m;
	m.N = 1;

	int** matrix = Init_matrix(m);

	assert(matrix != NULL);
	assert(matrix[0] != NULL);
	assert(matrix[0][0] == 0);
}


void test_Init_matrix_MultipleVertex_no6()
{
	Adj_list m;
	m.N = 3;

	int** matrix = Init_matrix(m);

	assert(matrix != NULL);
	assert(matrix[0] != NULL);
	assert(matrix[0][0] == 0 && matrix[0][1] == 0 && matrix[0][2] == 0);
	assert(matrix[1][0] == 0 && matrix[1][1] == 0 && matrix[1][2] == 0);
	assert(matrix[2][0] == 0 && matrix[2][1] == 0 && matrix[2][2] == 0);
}

void test_Construction_matrix_MultipleVertex_no7()
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

void test_Construction_matrix_1vertex_no8()
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

void test_Construction_matrix_NoEdges_no9()
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

void test_ReadLine_NoEdges_no10()
{
	FILE* f;

	if ((f = fopen("test5.txt", "w")) == NULL)
	{
		printf("The file test5.txt was not opened\n");
	}

	fprintf(f, "\n\n\n");
	fclose(f);

	if ((f = fopen("test5.txt", "r")) == NULL)
	{
		printf("The file test5.txt was not opened\n");
	}
	Adj_list result = ReadList(f);
	fclose(f);

	assert(result.N == 4);
	for (int i = 0; i < result.N; i++)
	{
		assert(result.sizes[i] == 0);
	}
}

void Runtests()
{
	test_ReadLine_empty_graph_no1();
	test_ReadLine_single_line_no2();
	test_ReadLine_3vertex_no3();
	test_ReadLine_12vertex_no4();
	test_Init_matrix_1vertex_no5();
	test_Init_matrix_MultipleVertex_no6();
	test_Construction_matrix_MultipleVertex_no7();
	test_Construction_matrix_1vertex_no8();
	test_Construction_matrix_NoEdges_no9();
	test_ReadLine_NoEdges_no10();
	
	printf("All tests were successful!\n");
}