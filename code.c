#include "code.h"

//������� ���� � ���� ������ ���������
Graph_l* createGraph_l(int vertices) {
	Graph_l* graph = malloc(sizeof(Graph_l));
	graph->num_v = vertices;
	for (int i = 0; i < vertices; i++) {
		graph->list[i] = NULL;
	}
	return graph;
}

//��������� ����� ����� ��������� � ���� � ���� ������ ���������
void add_l(Graph_l* graph, int src, int dest) {
	Node* newNode = malloc(sizeof(Node));
	newNode->vertex = dest;
	newNode->next = graph->list[src];
	graph->list[src] = newNode;
}

//������ ���� �� ����� � ������� ������ ���������
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

//������� ���� � ���� ������� ���������
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

//��������� ����� ����� ��������� � ���� � ���� ������� ���������
void add_m(Graph_m* graph, int src, int dest) {
	graph->matrix[src][dest] = 1;
}

//������ ���� �� ����� � ������� ������� ���������
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

//���������� ��� ����� (���� � ���� ������ ���������, ������ � ���� �������)
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
