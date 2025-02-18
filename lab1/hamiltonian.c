#include "hamiltonian.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000

int num_vertices;
int adj_matrix[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES];
bool visited[MAX_VERTICES];

bool is_safe(int vertex, int pos) {
    if (visited[vertex]) {
        return false;
    }

    if (pos > 0 && adj_matrix[path[pos - 1]][vertex] == 0) {
        return false;
    }

    return true;
}

bool hamiltonian_util(int pos) {
    if (pos == num_vertices) {
        return true;
    }

    for (int vertex = 0; vertex < num_vertices; vertex++) {
        if (is_safe(vertex, pos)) {
            path[pos] = vertex;
            visited[vertex] = true;

            if (hamiltonian_util(pos + 1)) {
                return true;
            }

            visited[vertex] = false;
        }
    }

    return false;
}

bool hamiltonian_path() {
    for (int start_vertex = 0; start_vertex < num_vertices; start_vertex++) {
        for (int i = 0; i < num_vertices; i++) {
            visited[i] = false;
        }

        path[0] = start_vertex;
        visited[start_vertex] = true;

        if (hamiltonian_util(1)) {
            return true;
        }
    }

    return false;
}