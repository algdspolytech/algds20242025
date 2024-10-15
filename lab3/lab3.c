#include <stdio.h>
#include <malloc.h>

#include "lab3.h"

//Dijkstra algorithm
int minlen(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NOT_FOUND;
    int n, start, stop;
    if (fscanf(f, "%d", &n) != 1) {
        fclose(f);
        return NOT_FOUND;
    }
    if (n <= 0) {
        fclose(f);
        return NOT_FOUND;
    }
    int *data = (int *) malloc(n * n * sizeof(int));;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (fscanf(f, "%d", &(data[y * n + x])) != 1) {
                fclose(f);
                free(data);
                return NOT_FOUND;
            }
            if (y > x && data[y * n + x] != data[x * n + y]) {
                //not symmetric matrix
                fclose(f);
                free(data);
                return NOT_FOUND;
            }
        }
    }

    if (fscanf(f, "%d %d", &start, &stop) != 2) {
        fclose(f);
        free(data);
        return NOT_FOUND;
    }

    if (start < 0 || start >= n || stop < 0 || stop >= n) {
        free(data);
        fclose(f);
        return NOT_FOUND;
    }

    int *lengths = (int *) malloc(sizeof(int) * n);
    char *visited = (char *) malloc(sizeof(char) * n);
    for (int x = 0; x < n; x++) {
        lengths[x] = NOT_FOUND;
        visited[x] = 0;
    }
    lengths[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        // Find the vertex with the minimum distance
        int minDist = NOT_FOUND;
        int minIndex;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && lengths[j] <= minDist) {
                minDist = lengths[j];
                minIndex = j;
            }
        }

        // Visit the vertex with the minimum distance found
        visited[minIndex] = 1;

        // Update the distance of the adjacent vertices of the visited vertex
        for (int j = 0; j < n; j++) {
            if (!visited[j] && data[minIndex * n + j] != 0 &&
                lengths[minIndex] != NOT_FOUND &&
                lengths[minIndex] + data[minIndex * n + j] < lengths[j]) {
                lengths[j] = lengths[minIndex] + data[minIndex * n + j];
            }
        }
    }

    fclose(f);
    int result = lengths[stop];
    free(lengths);
    free(visited);
    free(data);
    return result;
}