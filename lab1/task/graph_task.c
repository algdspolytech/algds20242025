#include <stdio.h>
#include <graph.c>

#define FILENAME "../input.txt"

int main(){
    Graph* gr=initGraph(FILENAME);
    printAdjacencyList(gr->adjList);
    freeGraph(gr);
    return 0;
}
