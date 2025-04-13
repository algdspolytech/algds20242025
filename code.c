#include "code.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Vertex* read(const char* filename, int* num_vertices, int* K) {
    FILE* input = fopen(filename, "r");
    fscanf(input, "%d %d", num_vertices, K);

    Vertex* graph = NULL;

    for (int i = 1; i <= *num_vertices; i++) {
        int vertex = i;

        Vertex* v = find(graph, vertex);
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

// Записывает результат в файл 
void write(const char* filename, const int* cover, int cover_size, bool covered) {
    FILE* output = fopen(filename, "w");

    if (covered) {
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

// Создает новую вершину с заданным номером
Vertex* create(int vertex) {
    Vertex* new_vertex = (Vertex*)malloc(sizeof(Vertex));
    new_vertex->vertex = vertex;
    new_vertex->edges = NULL; // Инициализируем список смежных вершин как пустой
    new_vertex->next = NULL; // Инициализируем указатель на следующую вершину как NULL
    return new_vertex;
}

// Добавляет ребро между текущей вершиной и смежной вершиной
void add_edge(Vertex* vertex, int adjacent_vertex) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->vertex = adjacent_vertex;
    new_edge->next = vertex->edges; // Добавляем новое ребро в начало списка смежных вершин
    vertex->edges = new_edge;
}

// Добавляет новую вершину в граф
void add_vertex(Vertex** graph, int vertex) {
    Vertex* new_vertex = create(vertex);
    new_vertex->next = *graph; // Вставляем новую вершину в начало списка графа
    *graph = new_vertex;
}

// Находит вершину по номеру в графе
Vertex* find(Vertex* graph, int vertex) {
    while (graph) {
        if (graph->vertex == vertex) {
            return graph; // Возвращаем найденную вершину
        }
        graph = graph->next; // Переходим к следующей вершине
    }
    return NULL; // Если не нашли - возвращаем NULL
}

// Освобождает память, занятую графом
void free(Vertex* graph) {
    while (graph) {
        Vertex* temp_vertex = graph;
        graph = graph->next;

        Edge* edge = temp_vertex->edges;
        while (edge) {
            Edge* temp_edge = edge;
            edge = edge->next;
            free(temp_edge); // Освобождаем память для каждого ребра
        }

        free(temp_vertex); // Освобождаем память для каждой вершины
    }
}

// Строит покрытие вершин графа и возвращает его размер
int build_vertex_cover(Vertex* graph, int* cover, int K) {
    int cover_size = 0;

    for (Vertex* v = graph; v != NULL && cover_size < K; v = v->next) {
        while (edge != NULL) {
            if (cover_size < K) {
                cover[cover_size++] = v->vertex;
                break;
            }
            edge = edge->next;
        }
    }

    return cover_size; // Возвращаем размер покрытия вершин
}

// Проверяет, покрыты ли все рёбра графа заданным покрытием вершин 
bool are_all_edges_covered(const Vertex* graph, const int* cover, int size) {
    for (const Vertex* v = graph; v != NULL; v = v->next) {
        for (const Edge* edge = v->edges; edge != NULL; edge = edge->next) {
            bool covered = false;

            for (int i = 0; i < size; i++) {
                if (cover[i] == v->vertex || cover[i] == edge->vertex) {
                    covered = true;
                    break; // Если хотя бы одна из вершин покрыта - выходим из цикла 
                }
            }

            if (!covered) return false; // Если хотя бы одно ребро не покрыто - возвращаем false 
        }
    }

    return true; // Все рёбра покрыты 
}

// Основная функция для нахождения покрытия вершин графа 
bool vertex_cover(Vertex* graph, int num, int K) {
    if (!graph || num <= 0 || K <= 0) return false;

    int* cover = (int*)malloc(sizeof(int) * num);

    if (!cover)
        return false;

    int cover_size = build_vertex_cover(graph, cover, K);

    bool covered = are_all_edges_covered(graph, cover, cover_size);

    write("output.txt", cover, cover_size, covered);

    free(cover);

    return covered;
}