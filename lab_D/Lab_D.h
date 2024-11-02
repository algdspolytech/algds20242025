#pragma once

#include <stdio.h>

typedef struct {
    int vertex;
    int depth;
} StackNode;

typedef struct {
    int V, s, t, K;
    int** adj;    // ������ ���������
    int* visited; // ������ ���������� ������
    int* path; // ������ ��� �������� �������� ����
    int path_length; // ����� �������� ����
} Graph;

// ������� ���������� ������ �� �����
char* Read_line(FILE* file);

// ������� ��� ������������ ������, ���������� ��� �������
void Free_Matrix_adj(int** Matrix, int vertices);

// ������� ���������� ���������� ������ (�����)
Graph* Parse_parameters(const char* filename, Graph* graph);

// ������� ��� �������� ������� ��������� � ������������� � ������
int** Create_Matrix_adj(int vertices);

// ������� �������� �����
Graph* Create_graph(char* filename);

// ������� ��� ������������� ����� � ������ ������
int Parse_Graph(Graph* graph, const char* filename);

// ����������� ������� DFS ��� ������ ���� ������ >= K
int Find_path(Graph* graph);

// ������� ��� ������ ���������� � ����
void Write_result(Graph* graph, const char* output_filename);

// ������� ��� ������������ ���������� ������
void Free_memory(Graph* graph);
