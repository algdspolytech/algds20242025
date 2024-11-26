#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct EdgeNode {
    int vertex;
    struct EdgeNode* next;
} EdgeNode;

typedef struct VertexNode {
    int vertex;
    EdgeNode* edges;
    struct VertexNode* next;
} VertexNode;

VertexNode* create_vertex(int vertex);

void add_edge(VertexNode* vertex, int adjacent_vertex);

void add_vertex(VertexNode** graph, int vertex);

VertexNode* find_vertex(VertexNode* graph, int vertex);

void free_graph(VertexNode* graph);

int build_vertex_cover(VertexNode* graph, int* cover, int K);

bool are_all_edges_covered(VertexNode* graph, int* cover, int cover_size);

void write_output(const char* filename, int* cover, int cover_size, bool all_edges_covered);

int vertex_cover(VertexNode* graph, int num_vertices, int K);

VertexNode* read_graph_from_file(const char* filename, int* num_vertices, int* K);
//
// Created by User on 26.11.2024.
//
