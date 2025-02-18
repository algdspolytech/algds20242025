#pragma once 

#include <stdbool.h>

#define MAX_VERTICES 1000


bool is_safe(int vertex, int pos, int num_vertices, int adj_matrix[][MAX_VERTICES], int path[], bool visited[]);
bool hamiltonian_util(int pos, int num_vertices, int adj_matrix[][MAX_VERTICES], int path[], bool visited[]);
bool hamiltonian_path(int num_vertices, int adj_matrix[][MAX_VERTICES], int path[]);