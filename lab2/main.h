#pragma once
#ifndef GRAPH_LIB_H
#define GRAPH_LIB_H

#include <stdbool.h>

// ��������� ��� ������������� ������� � � ������� ���������
typedef struct {
	int vertex;
	int* neighbors;
	int neighbor_count;
} Vertex;

// ��������� ��� ������������� �����
typedef struct {
	Vertex* vertices;
	int vertex_count;
} Graph;

bool dfs(const Graph* graph, int start_vertex, int end_vertex, bool* visited);

Graph* create_graph_from_file(const char* filename);

void free_graph(Graph* graph);

#endif