#include <assert.h>>
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "labD_tests.h"

#define NUMBER_OF_ACCURATE 10

#define SIZE_OF_LINE 9
//999 + ' ' + 999 + '\n' + '\0'

struct graph {
	int count_of_vertex;
	int k;
	int** m;
};

int i_res = 0;

void combinationUtil(int arr[], int data[], int start, int end,
	int index, int r, int* res);

void fill_combination(int arr[], int n, int r, int* res) {
	int* data = calloc(r, sizeof(int));
	if (data == NULL) {
		printf("\n couldn't allocate memory fill_combination\n");
		return;
	}
	combinationUtil(arr, data, 0, n - 1, 0, r, res);
}

void combinationUtil(int arr[], int data[], int start, int end,
	int index, int r, int* res) {
	if (index == r)
	{
		for (int j = 0; j < r; j++) {
			//printf("%d ", data[j]);
			res[i_res] = data[j];
			i_res++;
		}

		//printf("\n");
		return;
	}

	for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
		data[index] = arr[i];
		combinationUtil(arr, data, i + 1, end, index + 1, r, res);
	}
}


void get_combinations_n_r(int n, int r, int* res_arr) {

	int* arr = calloc(n, sizeof(int));
	if (arr == NULL) {
		printf("\n couldn't allocate memory get_combinations_n_r\n");
		return;
	}

	for (int i = 1; i <= n; i++) {
		arr[i - 1] = i;
	}

	fill_combination(arr, n, r, res_arr);

}

int factorial(int n) {
	return (n < 2) ? 1 : n * factorial(n - 1);
}

int combinations(int n, int m) {
	return factorial(n) / (factorial(m) * factorial(n - m));
}


void fill_matrix_0(int** matrix, int dimension) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			matrix[i][j] = 0;
		}
	}
}

void fill_array_0(int* arr, int dimention) {
	for (int i = 0; i < dimention; i++) {
		arr[i] = 0;
	}
}

void print_matrix(int** m, int dimension) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void parse_line(char* line, int* val1, int* val2) {
	int i = 0;
	int j = 0;
	char current = line[i];
	char str1[4];
	char str2[4];
	int flag = 1;

	while ((current != '\n') && (current != '\0')) {

		if (current == ' ') {
			flag = 0;
			j = 0;
			i++;
			current = line[i];
			continue;
		}

		if (flag) {
			str1[j] = current;
		}
		else {
			str2[j] = current;
		}

		i++;
		j++;
		current = line[i];
	}
	str1[3] = '\0';
	str2[3] = '\0';
	*val1 = strtol(str1, NULL, 10);
	*val2 = strtol(str2, NULL, 10);
}

int fill_graph_matrix(int*** matrix_of_graph, int count_of_vertex) {

	*matrix_of_graph = calloc(count_of_vertex, sizeof(int*));
	if (*matrix_of_graph == NULL) {
		return 0;
	}

	for (int i = 0; i < count_of_vertex; i++) {
		(*matrix_of_graph)[i] = calloc(count_of_vertex, sizeof(int));
		if ((*matrix_of_graph)[i] == NULL) {
			return 0;
		}
	}

	fill_matrix_0(*matrix_of_graph, count_of_vertex);
	return 1;
}

struct graph read_file_as_graph(char* file_name) {

	char buffer[SIZE_OF_LINE];
	int is_first_line = 1;

	FILE* fp = fopen(file_name, "r");

	int vertex1 = -1;
	int vertex2 = -1;
	int count_of_vertex = -1;
	int k = -1;

	int** matrix_of_graph = malloc(sizeof(int*));


	if (fp)
	{
		while ((fgets(buffer, SIZE_OF_LINE, fp)) != NULL)
		{
			if (is_first_line) {
				is_first_line = 0;

				parse_line(buffer, &count_of_vertex, &k);

				if (!fill_graph_matrix(&matrix_of_graph, count_of_vertex)) {
					printf("\ncouldn't allocate memory read_file_as_graph\n");
					return;
				}
			}
			else {
				parse_line(buffer, &vertex1, &vertex2);
				matrix_of_graph[vertex1 - 1][vertex2 - 1] = 1;
				matrix_of_graph[vertex2 - 1][vertex1 - 1] = 1;
			}

		}
		fclose(fp);
	}

	struct graph res;
	res.k = k;
	res.count_of_vertex = count_of_vertex;
	res.m = matrix_of_graph;

	return res;
}

int** create_matrix(int dimention) {
	int** matrix = calloc(dimention, sizeof(int*));
	if (matrix == NULL) {
		printf("couldn't allocate memory create_matrix");
		return;
	}
	for (int i = 0; i < dimention; i++) {
		matrix[i] = calloc(dimention, sizeof(int));
		if (matrix[i] == NULL) {
			printf("couldn't allocate memory create_matrix");
			return;
		}
	}
	return matrix;
}

void copy_matrix_a_to_b(int** a, int** b, int dimention) {
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			b[i][j] = a[i][j];
		}
	}
}

void print_arr(int* arr, int dimention) {
	printf("\n");
	for (int i = 0; i < dimention; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}


int is_zero_matrix(int** m, int dimention) {
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			if (m[i][j] != 0) {
				return 0;
			}
		}
	}
	return 1;
}


int* get_availible_pair(int** m, int dimention, int* res) {

	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			if (i == j) continue;
			if (m[i][j] != 0) {
				res[0] = i;
				res[1] = j;
				return;
			}
		}
	}
	res[0] = 0;
	res[1] = 0;

}

int all_pairs_in_matrix_is_zero(int** m, int dimention) {

	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {

			if (i == j)continue;
			if (m[i][j] != 0) {
				return 0;
			}
		}
	}
	return 1;
}

void remove_edges(int** m, int dimention, int* edges) {
	for (int i = 0; i < dimention; i++) {
		m[edges[0]][i] = 0;
		m[i][edges[0]] = 0;

		m[edges[1]][i] = 0;
		m[i][edges[1]] = 0;
	}

}

void remove_edge(int** m, int dimention, int edge) {
	for (int i = 0; i < dimention; i++) {
		m[i][edge] = 0;
		m[edge][i] = 0;
	}
}


void print_arr_vertex_cover(int* arr, int dimention) {
	printf("\n");

	for (int i = 0; i < dimention; i++) {
		if (arr[i] == 0) return;
		printf("%d ", arr[i]);
	}
}

int get_max_edge(int** m, int dimension) {
	int res_edge = -1;
	int res_edge_size_value = 0;
	for (int i = 0; i < dimension; i++) {
		int t = 0;
		for (int j = 0; j < dimension; j++) {
			t += m[i][j];
		}
		if (t > res_edge_size_value) {
			res_edge = i;
			res_edge_size_value = t;
		}
	}
	return res_edge;
}


int* vertex_cover_approximately(struct graph gr) {
	int result = 0;

	int* result_array = calloc(gr.k, sizeof(int));
	if (result_array == NULL) {
		printf("\n couldn't allocate memory vertex_cover_approximately");
		return;
	}
	fill_array_0(result_array, gr.k);
	int i = 0;
	while (1) {

		int max_edge = get_max_edge(gr.m, gr.count_of_vertex);
		if (max_edge < 0 || i > gr.k) break;
		remove_edge(gr.m, gr.count_of_vertex, max_edge);
		if (i < gr.k) result_array[i] = max_edge + 1;
		i++;
	}

	if (i <= gr.k) {
		return result_array;
	}
	else {
		free(result_array);
		return NULL;
	}
}



int* vertex_cover_accurate(struct graph gr) {

	int* result_array = calloc(gr.k, sizeof(int));
	if (result_array == NULL) {
		printf("couldn't allocate memory vertex_cover_accurate");
		return;
	}
	fill_array_0(result_array, gr.k);

	int** temp_matrix = create_matrix(gr.count_of_vertex);

	for (int k = 1; k <= gr.k; k++) {
		i_res = 0;
		int combinations_arr_size = combinations(gr.count_of_vertex, k) * k;
		int* combinations_arr = calloc(combinations_arr_size, sizeof(int));
		if (combinations_arr == NULL) {
			printf("couldn't allocate memory vertex_cover_accurate");
			return;
		}

		get_combinations_n_r(gr.count_of_vertex, k, combinations_arr);
		copy_matrix_a_to_b(gr.m, temp_matrix, gr.count_of_vertex);

		for (int i = 0; i < combinations_arr_size; i++) {

			remove_edge(temp_matrix, gr.count_of_vertex, combinations_arr[i] - 1);
			result_array[i % k] = combinations_arr[i];

			if ((1 + i) % k == 0) {

				if (all_pairs_in_matrix_is_zero(temp_matrix, gr.count_of_vertex)) {

					free(combinations_arr); free(temp_matrix);
					return result_array;
				}
				fill_array_0(result_array, gr.k);
				copy_matrix_a_to_b(gr.m, temp_matrix, gr.count_of_vertex);
			}

		}

		free(combinations_arr);
	}
	free(result_array); free(temp_matrix);
	return NULL;
}

int* vertex_cover(struct graph gr) {
	if (gr.count_of_vertex <= NUMBER_OF_ACCURATE) {
		return vertex_cover_accurate(gr);
	}
	return vertex_cover_approximately(gr);
}


int main() {
	char* path = "test10.txt";
	struct graph gr = read_file_as_graph(path);
	int* result = vertex_cover(gr);

	if (result == NULL) {
		printf("\n0");
	}
	else {
		print_arr_vertex_cover(result, gr.k);
	}
	free(result); free(gr.m);

	printf("\n");
	test_LabD();
}




