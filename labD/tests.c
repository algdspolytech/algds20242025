#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <assert.h>

#include "functions.h"
#include "tests.h"

#define NUM 3


void test_create_matrix_zero_dim_return0() {
	int** matrix = create_matrix(0);
	assert(matrix == 0 );
}

void test_create_matrix_negative_dim_return0() {
	int** matrix = create_matrix(-1);
	assert(matrix == NULL);
}

void test_create_normal_matrix_return0() {
	int** matrix = create_matrix(NUM);

	int check = 1;

	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			if (matrix[i][j] != 0) {
				check = 0;
			}
		}
	}


	assert(check == 1);
}

void test_create_graph_empty_file_return0() {
	graph* g = create_graph("empty.txt");	
	assert(g->matrix == NULL && g->visited == NULL && g->path == NULL);
}


void test_create_graph_no_edges_return0() {
	graph* g = create_graph("noedges.txt");

	int check = 1;

	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			if (g->matrix[i][j] != 0) {
				check = 0;
			}
		}
	}

	assert(check == 1);
}


void test_create_graph_cycle_return0() {
	graph* g = create_graph("cycle.txt");

	assert(g->matrix[0][1] == 1 && g->matrix[1][2] == 1 && g->matrix[2][0] == 1);
}

void test_find_path_no_edges_return0() {
	graph* g = create_graph("noedges.txt");

	assert(find_path(g) == 0);
}


void test_find_path_two_paths1_return0() {
	graph* g = create_graph("twopaths.txt");

	assert(find_path(g) == 1);
}

void test_find_path_two_paths2_return0() {
	graph* g = create_graph("twopaths.txt");
	g->K = 4;

	assert(find_path(g) == 0);
}