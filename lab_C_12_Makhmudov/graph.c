#pragma warning(disable : 4996)

#include "graph.h"

#include <stdio.h>
#include <stdlib.h>



void printGraph(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}


void readAdjMatrix(char filename[], int graph[MAX_VERTICES][MAX_VERTICES], int* vertices) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        exit(EXIT_FAILURE);
    }
    else {
        fscanf(file, "%d", vertices);

        for (int i = 0; i < *vertices; i++) {
            for (int j = 0; j < *vertices; j++) {
                fscanf(file, "%d", &graph[i][j]);
            }
        }
        fclose(file);
    }
}

void readAdjList(char filename[], int graph[MAX_VERTICES][MAX_VERTICES], int* vertices) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        exit(EXIT_FAILURE);
    }
    else {
        fscanf(file, "%d\n", vertices);

        int vert_num;
        int vert_ind;


        for (int i = 0; i < *vertices; i++) {
            fscanf(file, "%d:", &vert_num);
            for (int j = 0; j < vert_num; j++) {
                fscanf(file, "%d", &vert_ind);
                graph[i][vert_ind] = 1; //устанавливаем связь
            }
        }

        fclose(file);
    }
}

int compareGraphs(int graph1[MAX_VERTICES][MAX_VERTICES], int graph2[MAX_VERTICES][MAX_VERTICES], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (graph1[i][j] != graph2[i][j]) {
                return 0; // один из элементов не совпал
            }
        }
    }
    return 1; // все элементы совпали, функция не вышла раньше
}





