#pragma warning (disable:4996)
#include "lab2.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_TOPs 1000

int main() {

    FILE* file;
    int i, j; 
    int correct = 1;

    file = fopen("graph.txt", "r");

    if (file == NULL) {
        printf("Error\n");
        return 1;
    }

    fscanf(file, "%d", &num);

    if (CorrectNum(num)) {
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                fscanf(file, "%d", &matrix[i][j]);  
                
                if (!MatrixCheck(matrix[i][j])) { 
                    correct = 0;
                }
            }
        }

        if (correct == 0) {
            printf("Incorrect matrix");
        }
        else {
            printf("Enter two tops (0-%d): ", num - 1); 
            scanf("%d %d", &i, &j);

            if (TopCheck(num, i, j)) {  
                for (int i = 0; i < num; i++) {
                    visited[i] = 0;
                }

                if (DFS(i, j)) { 
                    printf("Path exist\n", i, j);
                }
                else {
                    printf("Path not exist\n", i, j);
                }
            }
            else {
                printf("Incorrect tops");
            }
        }

    }
    else {
        printf("Num of tops too big");
    }

    fclose(file);

    return 0;
}