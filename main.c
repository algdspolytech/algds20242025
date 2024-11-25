#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "graph.h"

int run_graph_app(const char* filename) {
    Graph* graph = createGraphFromFile(filename);
    if (graph == NULL) {
        return 1;
    }

    int startNode, endNode;
    printf("������� ��������� �������: ");
    if (scanf("%d", &startNode) != 1) {
        fprintf(stderr, "������ ����� ��������� �������.\n");
        freeGraph(graph);
        return 1;
    }
    printf("������� �������� �������: ");
    if (scanf("%d", &endNode) != 1) {
        fprintf(stderr, "������ ����� �������� �������.\n");
        freeGraph(graph);
        return 1;
    }


    int shortestDist = shortestPath(graph, startNode, endNode);

    if (shortestDist == -1) {
        printf("���� ����� ��������� �� ����������.\n");
    }
    else {
        printf("���������� ���������� ����� ���������: %d\n", shortestDist);
    }

    freeGraph(graph);
    return 0;
}