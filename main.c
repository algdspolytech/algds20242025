#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "graph.h"

int run_graph_app(const char* filename) {
    Graph* graph = createGraphFromFile(filename);
    if (graph == NULL) {
        return 1;
    }

    int startNode, endNode;
    printf("Введите начальную вершину: ");
    if (scanf("%d", &startNode) != 1) {
        fprintf(stderr, "Ошибка ввода начальной вершины.\n");
        freeGraph(graph);
        return 1;
    }
    printf("Введите конечную вершину: ");
    if (scanf("%d", &endNode) != 1) {
        fprintf(stderr, "Ошибка ввода конечной вершины.\n");
        freeGraph(graph);
        return 1;
    }


    int shortestDist = shortestPath(graph, startNode, endNode);

    if (shortestDist == -1) {
        printf("Пути между вершинами не существует.\n");
    }
    else {
        printf("Кратчайшее расстояние между вершинами: %d\n", shortestDist);
    }

    freeGraph(graph);
    return 0;
}