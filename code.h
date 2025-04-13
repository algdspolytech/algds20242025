#ifndef CODE_H
#define CODE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// ��������� ��� ������������� ����� �����
typedef struct Edge {
    int vertex; // ����� ������� �������
    struct Edge* next; // ��������� �� ��������� �����
} Edge;

// ��������� ��� ������������� ������� �����
typedef struct Vertex {
    int vertex; // ����� �������
    Edge* edges; // ������ ������� ������
    struct Vertex* next; // ��������� �� ��������� �������
} Vertex;

// ������� ��� ������ � ������
Vertex* read(const char* filename, int* num_vertices, int* K);

void write(const char* filename, const int* cover, int cover_size, bool covered);

Vertex* create(int vertex);

void add_edge(Vertex* vertex, int adjacent_vertex);

void add_vertex(Vertex** graph, int vertex);

Vertex* find(Vertex* graph, int vertex);

void free(Vertex* graph);

int build_vertex_cover(Vertex* graph, int* cover, int K);

bool are_all_edges_covered(const Vertex* graph, const int* cover, int size);

bool vertex_cover(Vertex* graph, int num, int K);

#endif // CODE_H
