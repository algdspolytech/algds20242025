#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** matrix;
    int size;
} Graph;

void initMatrix(Graph* graph) {
    graph->matrix = (int**)malloc(sizeof(int*) * graph->size);
    for (int i = 0; i < graph->size; ++i) {
        graph->matrix[i] = (int*)malloc(sizeof(int) * graph->size);
        for (int j = 0; j < graph->size; ++j) {
            graph->matrix[i][j] = 0;
        }
    }
}

void freeMatrix(Graph* graph) {
    for (int i = 0; i < graph->size; ++i) free(graph->matrix[i]);
    free(graph);
}

void copyRow(int* row, int* input, int size) {
    for (int i = 0; i < size; ++i) {
        row[i] = input[i];
    }
}

void printMatrix(Graph* graph, FILE* outputFile) {
    for (int i = 0; i < graph->size; ++i) {
        for (int j = 0; j < graph->size; ++j) {
            fprintf(outputFile, "%d ", graph->matrix[i][j]);
        }
        fprintf(outputFile, "\n");
    }
}

void readList(Graph* graph, FILE* file) {
    if (file != NULL) {
        char line[256];
        fgets(line, sizeof(line), file);
        sscanf(line, "%d", &graph->size);
        initMatrix(graph);
        while (fgets(line, sizeof(line), file)) {
                int* neighbours = (int*)malloc(sizeof(int) * graph->size);
                for (int i = 0; i < graph->size; ++i) neighbours[i] = 0;

                int vertex;
                if (sscanf(line, "%d:", &vertex)) {
                    char* ptr = line;
                    while (*ptr && *ptr != ':') ++ptr;
                    ++ptr;
                    ++ptr;
                    int currentNeighbour;
                    while (*ptr != '\0') {
                        if (sscanf(ptr, "%d", &currentNeighbour)) {
                            neighbours[currentNeighbour - 1] = 1;
                            while (*ptr && *ptr != ' ') ptr++;
                        }
                        while (*ptr == ' ') ptr++;
                    }
                    copyRow(graph->matrix[vertex - 1], neighbours, graph->size);
                    free(neighbours);
                }
        }
    }
}
