
#include <stdio.h>
#include <stdlib.h>
#include "Lab_C.h"

int main() {
    int rows, cols;
    int** matrix = readMatrix("input.txt", &rows, &cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    if (matrix == NULL) {
        return 1;
    }

    int* adjacencySizes;
    int** adjacencyList = createAdjacencyList(matrix, rows, cols, &adjacencySizes);

    // Записываем список смежности в файл output.txt
    writeAdjacencyListToFile("output.txt", adjacencyList, adjacencySizes, rows);

    // Освобождаем выделенную память
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
        free(adjacencyList[i]);
    }
    free(matrix);
    free(adjacencyList);
    free(adjacencySizes);

    printf("Adjacency list has been written to output.txt\n");
    return 0;
}
