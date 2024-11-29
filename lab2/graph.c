#include "graph.h"
#include <stdio.h>
#include <stdbool.h>

// ������������� ����� � �������� ����������� ������
void initGraph(Graph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0; // ��� ���� �� ���������
        }
    }
}

// ���������� ���� � ���� (����������������� ����)
void addEdge(Graph* graph, int u, int v) {
    graph->adjMatrix[u][v] = 1;
    graph->adjMatrix[v][u] = 1;  // ��� ������������������ �����
}

// ����� � �������
bool dfs(Graph* graph, int start, int end, bool visited[]) {
    if (start == end) {
        return true;
    }

    visited[start] = true;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[start][i] == 1 && !visited[i]) {
            if (dfs(graph, i, end, visited)) {
                return true;
            }
        }
    }

    return false;
}

// �������� ������� ���� ����� ���������
bool hasPath(Graph* graph, int start, int end) {
    bool visited[MAX_VERTICES] = { false };
    return dfs(graph, start, end, visited);
}