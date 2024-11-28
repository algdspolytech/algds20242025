#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "functions.h"


int** create_matrix(int n) {
    if (n > 0) {

        int** ans = (int**)malloc(n * sizeof(int*));
        if (ans == NULL) {
            return NULL;
        }
        for (int i = 0; i < n; i++) {
            ans[i] = (int*)malloc(n * sizeof(int));
            if (ans[i] == NULL) {
                return NULL;
            }
            else {
                for (int j = 0; j < n; j++) {
                    ans[i][j] = 0;
                }
            }
        }
        return ans;
    }
    else if (n == 0) {
        return 0;
    }
    else if (n < 0) {
        return NULL;
    
    }
}

graph* create_graph(char* name) {
    graph* ans = (graph*)malloc(sizeof(graph));

    FILE* file = fopen(name, "r");
    fscanf(file, "%d %d %d %d", &ans->V, &ans->s, &ans->t, &ans->K);

    ans->len = 0;
    ans->matrix = create_matrix(ans->V);
    ans->visited = calloc(ans->V, sizeof(int));
    ans->path = malloc(ans->V * sizeof(int));

    int v1 = 0;
    int v2 = 0;

    while (fscanf(file, "%d--%d", &v1, &v2) != EOF) {
        ans->matrix[v1][v2] = 1;
        ans->matrix[v2][v1] = 1;
    }

    fclose(file);

    return ans;
}



int find_path(graph* g) {
    node* stack = malloc(g->V * sizeof(node));
    int head = -1; 

    stack[++head] = (node){ .v = g->s, .d = 0 };
    g->visited[g->s] = 1;
    int ind = 0;


    while (head >= 0) {
        node tmp = stack[head--];
        int v = tmp.v;
        int depth = tmp.d;

        g->path[ind++] = v;

        //printf("depth=%d, v=%d\n", depth, v);
        if (v == g->t && depth >= g->K) {
            g->len = ind;
            printf("\n");
            free(stack);
            return 1;
        }
        int neig = 0;
        for (int u = 0; u < g->V; u++) {
            if (g->matrix[v][u] == 1 && !g->visited[u]) {
                stack[++head] = (node){.v = u, .d = depth + 1 };
                g->visited[u] = 1;
                neig = 1;
            }
        }

        if (!neig) {
            ind--;
            g->visited[v] = 0;
        }
    }

    free(stack);
    return 0;
}

void write_res(graph* g, char* name) {
    FILE* file = fopen(name, "w");
   
    if (find_path(g)) {
        for (int i = 0; i < g->len; i++) {
            fprintf(file, "%d ", g->path[i] );
        }
        fprintf(file, "\n");
    }
    else {
        fprintf(file, "0\n");
    }

    fclose(file);
}


void print_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}