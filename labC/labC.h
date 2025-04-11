#ifndef LABC_H
#define LABC_H

int** read_graph(const char* filename, int* size);
int find_shortest_path(int** graph, int size, int start, int end);
void free_graph(int** graph, int size);

#endif
