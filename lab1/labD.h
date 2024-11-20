#ifndef LABD_H
#define LABD_H

#define MAX_VERTICES 1000

int n;
int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int path[MAX_VERTICES];

void clearGraph();

void resetGraph();

void addGraphEdge(int u, int v);

int isHamiltonianPath(int position);

int findHamiltonianPath();

void readGraphFromFile(const char* filename);

void writeResult(const char* filename);

#endif
