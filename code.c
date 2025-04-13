#include "code.h"

//создает граф в виде списка смежности
Graph_l* createGraph_l(int vertices) {
	Graph_l* graph = malloc(sizeof(Graph_l));
	graph->num_v = vertices;
	for (int i = 0; i < vertices; i++) {
		graph->list[i] = NULL;
	}
	return graph;
}

//добавляет ребро между вершинами в граф в виде списка смежности
void add_l(Graph_l* graph, int src, int dest) {
	Node* newNode = malloc(sizeof(Node));
	newNode->vertex = dest;
	newNode->next = graph->list[src];
	graph->list[src] = newNode;
}

//читает граф из файла в формате списка смежности
Graph_l* read_l(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		exit(1);
	}
	int vertices;
	fscanf(file, "%d", &vertices);
	Graph_l* graph = createGraph_l(vertices);
	int a, b;
	while (fscanf(file, "%d %d", &a, &b) == 2) {
		add_l(graph, a, b);
	}
	fclose(file);
	return graph;
}

//создает граф в виде матрицы смежности
Graph_m* createGraph_m(int vertices) {
	Graph_m* graph = malloc(sizeof(Graph_m));
	graph->num_v = vertices;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			graph->matrix[i][j] = 0;
		}
	}
	return graph;
}

//добавляет ребро между вершинами в граф в виде матрицы смежности
void add_m(Graph_m* graph, int src, int dest) {
	graph->matrix[src][dest] = 1;
}

//читает граф из файла в формате матрицы смежности
Graph_m* read_m(const char* filename) {
	FILE* file = fopen(filename, "r");;
	if (!file) {
		exit(1);
	}
	int vertices;
	fscanf(file, "%d", &vertices);
	Graph_m* graph = createGraph_m(vertices);
	int element;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			fscanf(file, "%d", &element);
			if (element) {
				add_m(graph, i, j);
			}
		}
	}

	fclose(file);
	return graph;
}

//сравнивает два графа (один в виде списка смежности, другой в виде матрицы)
bool compareGraphs(Graph_l* L_graph, Graph_m* M_graph) {
	if (L_graph->num_v != M_graph->num_v) {
		return false;
	}

	for (int i = 0; i < L_graph->num_v; i++) {
		Node* temp = L_graph->list[i];
		int c = 0;

		while (temp != NULL) {
			c++;
			temp = temp->next;
		}


		for (int j = 0; j < M_graph->num_v; j++) {
			if (M_graph->matrix[i][j] == 1) {
				c--;
			}
		}

		if (c != 0) {
			return false;
		}
	}

	return true;
}
