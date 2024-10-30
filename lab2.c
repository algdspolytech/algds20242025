#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lab2.h"

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjList = (int**)malloc(vertices * sizeof(int*));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjList[i][j] = 0; // �������������� 0 (��� �����)
        }
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    graph->adjList[src][dest] = 1; // ��������� ������������ �����
    //graph->adjList[dest][src] = 1; // ��������� ������� ��� ������������������ �����
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjList[i]);
    }
    free(graph->adjList);
    free(graph);
}

bool dfsUtil(Graph* graph, int vertex, bool* visited, int targetVertex) {
    if (vertex == targetVertex) {
        return true; // ���� �������� ������ �������
    }
    visited[vertex] = true;

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjList[vertex][i] == 1 && !visited[i]) {
            if (dfsUtil(graph, i, visited, targetVertex)) {
                return true; // ���� ������ ���� � ������� �������
            }
        }
    }
    return false; // ���� �� ������
}
bool depthFirstSearch(Graph* graph, int startVertex, int targetVertex) {
    if (graph->numVertices == 0) {
        return false; // �������� �� ���� � 0 ���������
    }
    if (startVertex >= graph->numVertices || targetVertex >= graph->numVertices) {
        return false; // ���� ������� �� ��������� �����
    }

    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    if (visited == NULL) {
        fprintf(stderr, "������: �� ������� �������� ������ ��� ������� ���������� ������.\n");
        return false;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false; // ������������� ������� ���������� ������
    }

    bool result = dfsUtil(graph, startVertex, visited, targetVertex);

    free(visited);
    return result;
}
