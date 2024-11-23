#include "code.h"


GraphAdjList* createGraphAdjList(int vertices) {
	GraphAdjList* graph = malloc(sizeof(GraphAdjList));
	graph->numVertices = vertices;
	for (int i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
	}
	return graph;
}


void addEdgeAdjList(GraphAdjList* graph, int src, int dest) {
	Node* newNode = malloc(sizeof(Node));
	newNode->vertex = dest;
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;
}


GraphAdjMatrix* createGraphAdjMatrix(int vertices) {
	GraphAdjMatrix* graph = malloc(sizeof(GraphAdjMatrix));
	graph->numVertices = vertices;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			graph->matrix[i][j] = 0;
		}
	}
	return graph;
}


void addEdgeAdjMatrix(GraphAdjMatrix* graph, int src, int dest) {
	graph->matrix[src][dest] = 1;
}


int compareGraphs(GraphAdjList* adjListGraph, GraphAdjMatrix* adjMatrixGraph) {
	if (adjListGraph->numVertices != adjMatrixGraph->numVertices) {
		return 0;
	}

	for (int i = 0; i < adjListGraph->numVertices; i++) {
		Node* temp = adjListGraph->adjLists[i];
		int count = 0;

		while (temp != NULL) {
			count++;
			temp = temp->next;
		}


		for (int j = 0; j < adjMatrixGraph->numVertices; j++) {
			if (adjMatrixGraph->matrix[i][j] == 1) {
				count--;
			}
		}

		if (count != 0) {
			return 0;
		}
	}

	return 1;
}




GraphAdjList* readAdjList(const char* filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		exit(1);
	}
	int vertices;
	fscanf(file, "%d", &vertices);
	GraphAdjList* graph = createGraphAdjList(vertices);
	int a, b;
	while (fscanf(file, "%d %d", &a, &b) == 2) {
		addEdgeAdjList(graph, a, b);
	}
	fclose(file);
	return graph;
}


GraphAdjMatrix* readAdjMatrix(const char* filename) {
	FILE* file = fopen(filename, "r");;
	if (!file) {
		exit(1);
	}
	int vertices;
	fscanf(file, "%d", &vertices);
	GraphAdjMatrix* graph = createGraphAdjMatrix(vertices);
	int element;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			fscanf(file, "%d", &element);
			if (element) {
				addEdgeAdjMatrix(graph, i, j);
			}
		}
	}

	fclose(file);
	return graph;
}