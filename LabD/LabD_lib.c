#include "LabD_lib.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#pragma warning(disable: 4996)

VertexNode* create_vertex(int vertex) {
    VertexNode* new_vertex = (VertexNode*)malloc(sizeof(VertexNode));
    new_vertex->vertex = vertex;
    new_vertex->edges = NULL;
    new_vertex->next = NULL;
    return new_vertex;
}

void add_edge(VertexNode* vertex, int adjacent_vertex) {
    EdgeNode* new_edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    new_edge->vertex = adjacent_vertex;
    new_edge->next = vertex->edges;
    vertex->edges = new_edge;
}

void add_vertex(VertexNode** graph, int vertex) {
    VertexNode* new_vertex = create_vertex(vertex);
    new_vertex->next = *graph;
    *graph = new_vertex;
}

VertexNode* find_vertex(VertexNode* graph, int vertex) {
    while (graph != NULL) {
        if (graph->vertex == vertex) {
            return graph;
        }
        graph = graph->next;
    }
    return NULL;
}

void free_graph(VertexNode* graph) {
    while (graph != NULL) {
        VertexNode* temp_vertex = graph;
        graph = graph->next;

        EdgeNode* edge = temp_vertex->edges;
        while (edge != NULL) {
            EdgeNode* temp_edge = edge;
            edge = edge->next;
            free(temp_edge);
        }

        free(temp_vertex);
    }
}

int build_vertex_cover(VertexNode* graph, int* cover, int K) {
    int cover_size = 0;
    VertexNode* v = graph;

    while (v != NULL && cover_size < K) {
        EdgeNode* edge = v->edges;
        while (edge != NULL) {
            if (cover_size < K) {
                cover[cover_size++] = v->vertex;
                break;
            }
            edge = edge->next;
        }
        v = v->next;
    }

    return cover_size;
}

bool are_all_edges_covered(VertexNode* graph, int* cover, int cover_size) {
    VertexNode* v = graph;

    while (v != NULL) {
        EdgeNode* edge = v->edges;
        int edge_covered = 0;

        while (edge != NULL) {
            for (int i = 0; i < cover_size; i++) {
                if (cover[i] == v->vertex || cover[i] == edge->vertex) {
                    edge_covered = 1;
                    break;
                }
            }
            if (!edge_covered) {
                return false;
            }
            edge = edge->next;
        }
        v = v->next;
    }

    return true;
}

void write_output(const char* filename, int* cover, int cover_size, bool all_edges_covered) {
    FILE* output = fopen(filename, "w");
    if (!output) {
        printf("Ошибка открытия файла %s для записи.\n", filename);
        return;
    }

    if (all_edges_covered) {
        for (int i = 0; i < cover_size; i++) {
            fprintf(output, "%d ", cover[i]);
        }
        fprintf(output, "\n");
    }
    else {
        fprintf(output, "0\n");
    }

    fclose(output);
}

int vertex_cover(VertexNode* graph, int num_vertices, int K) {
    int* cover = (int*)malloc(sizeof(int) * num_vertices);
    if (!cover) {
        printf("Ошибка выделения памяти для массива cover.\n");
        return 0;
    }

    int cover_size = build_vertex_cover(graph, cover, K);

    bool all_edges_covered = are_all_edges_covered(graph, cover, cover_size);

    write_output("output.txt", cover, cover_size, all_edges_covered);

    free(cover);
    return all_edges_covered;
}

VertexNode* read_graph_from_file(const char* filename, int* num_vertices, int* K) {
    FILE* input = fopen(filename, "r");
    if (!input) {
        printf("Не удалось открыть файл %s\n", filename);
        return NULL;
    }

    fscanf(input, "%d %d", num_vertices, K);

    VertexNode* graph = NULL;

    for (int i = 1; i <= *num_vertices; i++) {
        int vertex = i;

        VertexNode* v = find_vertex(graph, vertex);
        if (!v) {
            add_vertex(&graph, vertex);
            v = graph;
        }

        int adjacent_vertex;
        while (fscanf(input, "%d", &adjacent_vertex) == 1 && adjacent_vertex != -1) {
            add_edge(v, adjacent_vertex);
        }
    }

    fclose(input);
    return graph;
}