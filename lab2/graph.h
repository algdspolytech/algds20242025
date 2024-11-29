#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_VERTICES 100

// ��������� ��� �����
typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES]; // ������� ���������
    int vertices; // ���������� ������
} Graph;

// ������� ��� ������ � ������
void initGraph(Graph* graph, int vertices);
void addEdge(Graph* graph, int u, int v);
bool dfs(Graph* graph, int start, int end, bool visited[]);
bool hasPath(Graph* graph, int start, int end);

#endif // GRAPH_H