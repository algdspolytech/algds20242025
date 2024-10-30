#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include "lib.h"
#include "tests.h"

int main() 
{
    runAllTests();

    const char *filename = "graph.txt";
    Graph g = readGraphFromFile(filename);
    
    int startVertex, endVertex;
    printf("Input start vertex: ");
    scanf("%d", &startVertex);
    printf("Input end vertex: ");
    scanf("%d", &endVertex);
    int result = bfs(&g, startVertex, endVertex);
    if (result == INF) 
    {
        printf("There is no path.\n");
    } 
    else 
    {
        printf("The shortest path: %d", result);
    }

    return 0;
}
