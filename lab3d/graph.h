#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_VERTICES 1000

typedef struct {
    int* adj[MAX_VERTICES]; // ������ ���������
    int size[MAX_VERTICES]; // ������ ������� ������
    int visited[MAX_VERTICES]; // ��� ������������ ���������� ������
} Graph;

// ������������� �����
void initGraph(Graph* graph, int V);

// ���������� ����� � ����
void addEdge(Graph* graph, int u, int v);

// ����������� ����� ����
bool dfs(Graph* graph, int v, int t, int K, int length, int* path, int* pathLength);

#endif // GRAPH_H