#include "LabD_lib.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");

    int num_vertices, K;
    VertexNode* graph = read_graph_from_file("input.txt", &num_vertices, &K);
    if (!graph) {
        return 1;
    }

    if (!vertex_cover(graph, num_vertices, K)) {
        printf("Ќе удалось найти покрытие дл€ заданных параметров.\n");
    }

    free_graph(graph);

    return 0;
}