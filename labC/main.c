#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "functions.h"
#include "tests.h"

int main() {
	test_create_node_OrdinaryNumber_return0_no1();
	test_init_graph_OrdinarySettings_return0_no2();
	test_add_edge_OrdinaryEdge_return0_no3();
	test_add_edge_TwoSideEdge_return0_no4();
	test_add_edge_SomeEdges_return0_no5();
	test_read_graph_ReadFromFile_return0_no6();
	test_find_path_WithPath_returnValidVal_no7();
	test_find_path_WithoutPath_returnValidVal_no8();
	test_find_path_OneVertex_returnValidVal_no9();

	printf("All tests passed!\n");

	Graph* g = (Graph*)malloc(sizeof(Graph));
	g = read_graph("source.txt");
	print_graph(g);

	find_path(g, 0, 5);

	return 0;
}