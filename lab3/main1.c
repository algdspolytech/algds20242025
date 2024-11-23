//
//  main.c
//  Lab_D
//
//  Created by Фёдор Филь on 21.11.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "main.h"
#include "tests.h"

#define MAX_T 1000

void initArrayList(ArrayList *a, size_t initialSize) {
    a->array = (int *)malloc(initialSize * sizeof(int));
    a->used = 0;
    a->size = initialSize;
}

void insertArrayList(ArrayList *a, int element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (int *)realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void freeArrayList(ArrayList *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

void readInput(const char *filename, int *T, int *K, int **Z, ArrayList **graph) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", T, K);
    *Z = (int *)malloc((*T) * sizeof(int));
    for (int i = 0; i < *T; ++i) {
        fscanf(file, "%d", &(*Z)[i]);
    }

    *graph = (ArrayList *)malloc((*T + 1) * sizeof(ArrayList));
    for (int i = 1; i <= *T; ++i) {
        initArrayList(&(*graph)[i], 10);
    }

    int i, j;
    while (fscanf(file, "%d %d", &i, &j) == 2 && i != 0 && j != 0) {
        insertArrayList(&(*graph)[i], j);
    }

    fclose(file);
}

void freeGraph(ArrayList *graph, int T) {
    for (int i = 1; i <= T; ++i) {
        freeArrayList(&graph[i]);
    }
    free(graph);
}

ArrayList* topologicalSort(ArrayList *graph, int T) {
    int *inDegree = (int *)calloc(T + 1, sizeof(int));
    for (int i = 1; i <= T; ++i) {
        for (int j = 0; j < graph[i].used; ++j) {
            inDegree[graph[i].array[j]]++;
        }
    }

    ArrayList *queue = (ArrayList *)malloc(sizeof(ArrayList));
    initArrayList(queue, T);
    for (int i = 1; i <= T; ++i) {
        if (inDegree[i] == 0) {
            insertArrayList(queue, i);
        }
    }

    ArrayList *result = (ArrayList *)malloc(sizeof(ArrayList));
    initArrayList(result, T);

    while (queue->used > 0) {
        int u = queue->array[--queue->used];
        insertArrayList(result, u);

        for (int i = 0; i < graph[u].used; ++i) {
            int v = graph[u].array[i];
            inDegree[v]--;
            if (inDegree[v] == 0) {
                insertArrayList(queue, v);
            }
        }
    }

    free(inDegree);
    freeArrayList(queue);

    if (result->used != T) {
        freeArrayList(result);
        return NULL;
    }

    return result;
}

int checkCondition(ArrayList *sortedTasks, int *Z, int K) {
    int currentSum = 0;
    for (int i = 0; i < sortedTasks->used; ++i) {
        currentSum += Z[sortedTasks->array[i] - 1];
        if (currentSum > K) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int T, K;
    int *Z;
    ArrayList *graph;

    readInput("input.txt.rtf", &T, &K, &Z, &graph);

    ArrayList *sortedTasks = topologicalSort(graph, T);
    if (sortedTasks) {
        if (checkCondition(sortedTasks, Z, K)) {
            FILE *outFile = fopen("output.txt.rtf", "w");
            for (int i = 0; i < sortedTasks->used; ++i) {
                fprintf(outFile, "%d ", sortedTasks->array[i]);
            }
            fclose(outFile);
        } else {
            FILE *outFile = fopen("output.txt.rtf", "w");
            fprintf(outFile, "0");
            fclose(outFile);
        }
    } else {
        FILE *outFile = fopen("output.txt.rtf", "w");
        fprintf(outFile, "0");
        fclose(outFile);
    }

    free(Z);
    freeGraph(graph, T);
    freeArrayList(sortedTasks);

    return 0;
}
