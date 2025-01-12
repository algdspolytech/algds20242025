#include <assert.h>>
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "LabD.h"


void test1_readFileAsGraph_extraSpace() {
	char* path = "test1.txt";
	struct graph gr = read_file_as_graph(path);
	free(gr.m);
	assert(gr.k == 1);
}

void test2_vertexCoverAccurate_completeTriangleK1_0() {
	char* path = "test1.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result == NULL);
}


void test3_vertexCoverAccurate_completeTriangleK2_array() {
	char* path = "test3.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result[0] > 0 && result[1] > 0);
	free(result);
}

void test4_vertexCoverAccurate_LinearGraphK2_array() {
	char* path = "test4.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result[0] > 0 && result[1] > 0);
	free(result);
}


void test5_vertexCoverAccurate_completeGraphK2_0() {
	char* path = "test5.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result == NULL);
}

void test6_vertexCoverAccurate_completeGraphK4_array() {
	char* path = "test6.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result[0] > 0 && result[1] > 0);
	free(result);
}

void test7_vertexCoverAccurate_starGraphK1_array() {
	char* path = "test7.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result[0] > 0);
	free(result);
}

void test8_vertexCoverAccurate_treeGraphK3_array() {
	char* path = "test8.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result[0] > 0 && result[1] > 0);
	free(result);
}

void test9_vertexCoverApproximately_treeGraphCountVertex15K4_0() {
	char* path = "test9.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result == NULL);
}

void test10_vertexCoverApproximately_SparseGraphCountVertex15K4_array() {
	char* path = "test10.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result[0] > 0 && result[1] > 0 && result[2] > 0 && result[3] > 0);
	free(result);
}

void test11_vertexCoverApproximately_CycleWithAdditionalEdgesCountVertex15K4_array() {
	char* path = "test11.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);
	free(gr.m);
	assert(result[0] > 0 && result[1] > 0 && result[2] > 0 && result[3] > 0 && result[4] > 0 && result[5] > 0);
	free(result);
}




void test_LabD() {
	test1_readFileAsGraph_extraSpace();
	test2_vertexCoverAccurate_completeTriangleK1_0();
	test3_vertexCoverAccurate_completeTriangleK2_array();
	test4_vertexCoverAccurate_LinearGraphK2_array();
	test5_vertexCoverAccurate_completeGraphK2_0();
	test6_vertexCoverAccurate_completeGraphK4_array();
	test7_vertexCoverAccurate_starGraphK1_array();
	test8_vertexCoverAccurate_treeGraphK3_array();
	test9_vertexCoverApproximately_treeGraphCountVertex15K4_0();
	test10_vertexCoverApproximately_SparseGraphCountVertex15K4_array();
	test11_vertexCoverApproximately_CycleWithAdditionalEdgesCountVertex15K4_array();

	printf("\ntests ok\n");
}
