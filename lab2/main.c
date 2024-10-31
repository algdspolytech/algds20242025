#include "main.h"

int main() {
    FILE* file;
    int u, v;
    int correct = 1;
    file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("Error open file\n");
        return 1;
    }

    fscanf(file, "%d", &numVertices);
    if (CorrectNumOfPointCheck(numVertices)) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                fscanf(file, "%d", &adjacencyMatrix[i][j]);
                if (!MatrixCheck(adjacencyMatrix[i][j])) {
                    correct = 0;
                }
            }
        }
        if (correct == 0) {
            printf("Incorrect matrix type");
        }
        else {
            printf("Enter two points (0-%d): ", numVertices - 1);
            scanf("%d %d", &u, &v);

            if (PointsCheck(numVertices, u, v)) {
                for (int i = 0; i < numVertices; i++) {
                    visited[i] = 0;
                }

                if (dfs(u, v)) {
                    printf("Path between points %d and %d exist\n", u, v);
                }
                else {
                    printf("Path between points %d and %d does not exist\n", u, v);
                }
            }
            else {
                printf("Incorrect points");
            }
        }

    }
    else {
        printf("Num of points too big");
    }

    fclose(file);

    return 0;
}