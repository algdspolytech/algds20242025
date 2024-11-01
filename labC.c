#include <stdlib.h>
#include <stdio.h>
#include "labC.h"
#define _CRT_SECURE_NO_WARNINGS

int shortestPath(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("\nError opening file!\n\n");
		return -1;
	}

	Graph graph;
	if (fscanf(file, "%d", &graph.numVertices) != 1 || (graph.numVertices <= 0)) {
		fprintf(stderr, "\nError: Invalid format for number of vertices in file '%s'\n\n", filename);
		fclose(file);
		return -1;
	}

	for (int i = 0; i < graph.numVertices; i++) {
		for (int j = 0; j < graph.numVertices; j++) {
			if (fscanf(file, "%d", &graph.adjacencyMatrix[i][j]) != 1 || (graph.adjacencyMatrix[i][j] < 0)) {
				fprintf(stderr, "\nError: Invalid format for adjacency matrix in file '%s'\n\n", filename);
				fclose(file);
				return -1;
			}
		}
	}

	int start_vertex, end_vertex;
	if (fscanf(file, "%d %d", &start_vertex, &end_vertex) != 2 || (start_vertex < 0) || (end_vertex < 0)) {
		fprintf(stderr, "\nError: Invalid format for start and end vertices in file '%s'\n\n", filename);
		fclose(file);
		return -1;
	}

	fclose(file);

	int visited[MAX_VERTICES] = { 0 };
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	visited[start_vertex] = 1;
	queue[rear++] = start_vertex;

	int distance[MAX_VERTICES];
	for (int i = 0; i < MAX_VERTICES; i++) {
		distance[i] = -1;
	}
	distance[start_vertex] = 0;

	while (front < rear) {
		int current = queue[front++];

		if (current == end_vertex) {
			return distance[end_vertex];
		}

		for (int i = 0; i < graph.numVertices; i++) {
			if (graph.adjacencyMatrix[current][i] == 1 && !visited[i]) {
				visited[i] = 1;
				queue[rear++] = i;
				distance[i] = distance[current] + 1;
			}
		}
	}

	return -1;
}
