#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_V 1000

int graph[MAX_V][MAX_V];
int color[MAX_V];
int V, K;
int graph_coloring(int node);
int can_color(int node, int c);
void graph_coloring_cycle();
void graph_coloring_star();
void graph_coloring_complete();
void graph_coloring_tree();
void graph_coloring_path();
void graph_coloring_triangle();
void graph_coloring_bipartite();
void graph_coloring_combined();
void graph_coloring_disconnected();
void graph_coloring_complex();