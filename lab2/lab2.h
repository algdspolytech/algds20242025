#include <stdio.h>
#include <stdlib.h>
#define MAX_TOPs 1000
#pragma warning(disable : 4996)

int num; 
int matrix[MAX_TOPs][MAX_TOPs]; 
int visited[MAX_TOPs]; 

int MatrixCheck(int matrix) {
    if (matrix != 0 && matrix != 1) { 
        return 0;
    }
    else {
        return 1;
    }
}

int TopCheck(int num, int i, int j) {
    if (i < 0 || i >= num || j < 0 || j >= num) {
        return 0;
    }
    else {
        return 1;
    }
}

int CorrectNum(int num) { 
    if (num <= MAX_TOPs) {  
        return 1;
    }
    else {
        return 0;
    }
}

int DFS(int top, int goal) {  
    visited[top] = 1; 
    for (int i = 0; i < num; i++) { 
        if (matrix[top][i] == 1) { 
            if (i == goal) {  
                return 1;
            }
            if (!visited[i]) {
                if (DFS(i, goal)) { 
                    return 0;
                }
            }
        }
    }
    return 0;
}