#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "LabC_lib.h"

int main() {
    setlocale(LC_ALL, "Rus");
    int size;
    int** matrix = read_adjacency_matrix("input.txt", &size);
    Graph* this_graph = build_adjacency_list(matrix, size);
    write_adjacency_list("output.txt", this_graph);

    free_adjacency_matrix(matrix, size);
    free_graph(this_graph);
    return 0;
}