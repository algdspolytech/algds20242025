#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

typedef struct GraphStructure {
    int vertexCount; // ���-�� ������
    int** adjacencyList; // ������ ��������� �����
    char** vertexNames; // ��� ������ �������
} GraphStructure;

GraphStructure* create_graph(); // �������� �����
void insert_vertex(GraphStructure* graph, char* vertex); // ������� ���������� �������
void insert_edge(GraphStructure* graph, char* source, char* destination); // ��������� ����� �� source � destination
int find_vertex_index(GraphStructure* graph, char* vertex); // ������� ��� ��������� ������� ������� �� � ��������
char* fetch_vertex_name(GraphStructure* graph, int index); // ������� ��� ��������� ����� ������� �� �������
GraphStructure* read_graph(FILE* file); // �������� �� ����� ����
void perform_topological_sort(GraphStructure* graph, Stack* stack, int vertex, int* visited); // ������� �������������� ����������
int verify_acylclic(GraphStructure* graph); // ������� ��� �������� ����� �� ������������
