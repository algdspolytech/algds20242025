#include "header.h"

#include "header.h"

int can_color(int node, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[node][i] && color[i] == c) {
            return 0; 
        }
    }
    return 1; 
}

int graph_coloring(int node) {
    if (node == V)
        return 1; 

    for (int c = 1; c <= K; c++) { 
        if (can_color(node, c)) {  
            color[node] = c; 
            if (graph_coloring(node + 1)) 
                return 1; 
            color[node] = 0;
        }
    }
    return 0; 
}