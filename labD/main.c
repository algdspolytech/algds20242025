#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "functions.h"


int main() {
	test_create_matrix_zero_dim_return0();
	test_create_matrix_negative_dim_return0();
	test_create_normal_matrix_return0();
	test_create_graph_empty_file_return0();
	test_create_graph_no_edges_return0();
	test_create_graph_cycle_return0();
	test_find_path_no_edges_return0();
	test_find_path_two_paths1_return0();
	test_find_path_two_paths2_return0();
	
	printf("All tests passed!\n");
}


