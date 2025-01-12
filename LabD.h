#pragma once
int* vertex_cover(struct graph gr);

struct graph read_file_as_graph(char* file_name);

struct graph {
	int count_of_vertex;
	int k;
	int** m;
};
