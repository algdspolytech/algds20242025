#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

extern int adj[MAX_VERTICES][MAX_VERTICES];
extern int visited[MAX_VERTICES];
extern int path[MAX_VERTICES];
extern int n;

// ������� ��� ������ ����� �� �����
void readGraphFromFile(const char* filename);

// �������� ������� ��� ������ ������������ ����, ������� � ������ �������
int findHamiltonianPath();

// ��������������� ����������� ������� ��� ������ ������������ ���� � ���������� ��������� �������
int hamiltonianPath(int pos);

// ������� ��� ������ ���������� � ����
void outputResult(const char* filename);

// ������� ��� ���������� ����� � ������� �����
void addEdge(int u, int v);
void clearGraph();
void resetGraph();
#endif // HEADER_H
