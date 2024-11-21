#include "main.h"

int main() {
    Graph graph;
    UsedVertexes array;
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", &graph.num_vertices);
    GraphInitialise(&graph);
    int k;
    fscanf(file, "%d", &k);
    for (int i = 0; i < graph.num_vertices; i++) {
        array.Vertexes[i] = 1;
    }
    int v, u;
    while (fscanf(file, "%d %d", &v, &u) != EOF) {
        graph.adj[u - 1][v - 1] = 1;
        graph.adj[v - 1][u - 1] = 1;
    }
    fclose(file);
    int StartVertex = 0;
    int result_found = 0;
    FILE* output = fopen("output.txt", "w");
    if (FindVertexCover(graph, result_found, StartVertex, &array) > k ||
        FindVertexCover(graph, result_found, StartVertex, &array) == 0) {
        fprintf(output, "0");
    }
    else {
        for (int i = 0; i < graph.num_vertices; i++) {
            if (array.Vertexes[i] == 0) {
                fprintf(output, "%d ", i + 1);
            }
        }
    }

    fclose(output);
    return 0;
}