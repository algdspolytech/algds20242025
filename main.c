#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#pragma warning(disable:4996)
#define MAX_ITEMS 1000


void backtracking(int index, int currentWeight, int currentValue, int* solution, int* bestSolution,
    int* weights, int* values, int numItems, int capacity, int minValue,
    int* bestItemCount, int* found);

int compareSolutions(int* sol1, int* sol2, int numItems);

int main() {
    int U, B, K; 
    int weights[MAX_ITEMS], values[MAX_ITEMS];
    int solution[MAX_ITEMS] = { 0 }, bestSolution[MAX_ITEMS] = { 0 };


    FILE* inputFile = fopen("input.txt", "r");
    if (!inputFile) {
        fprintf(stderr, "Error: Cannot open input file.\n");
        return 1;
    }


    fscanf(inputFile, "%d %d %d", &U, &B, &K);


    for (int i = 0; i < U; i++) {
        fscanf(inputFile, "%d", &weights[i]);
    }


    for (int i = 0; i < U; i++) {
        fscanf(inputFile, "%d", &values[i]);
    }

    fclose(inputFile);

    int found = 0;
    int bestItemCount = U + 1; 


    backtracking(0, 0, 0, solution, bestSolution, weights, values, U, B, K, &bestItemCount, &found);

 
    FILE* outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fprintf(stderr, "Error: Cannot open output file.\n");
        return 1;
    }

    if (found) {
        for (int i = 0; i < U; i++) {
            if (bestSolution[i]) {
                fprintf(outputFile, "%d ", i + 1); 
            }
        }
        fprintf(outputFile, "\n");
    }
    else {
        fprintf(outputFile, "0\n");
    }

    fclose(outputFile);

    return 0;
}


void backtracking(int index, int currentWeight, int currentValue, int* solution, int* bestSolution,
    int* weights, int* values, int numItems, int capacity, int minValue,
    int* bestItemCount, int* found) {

    if (currentWeight > capacity) {
        return; 
    }

    if (currentValue >= minValue) {
        int itemCount = 0;
        for (int i = 0; i < numItems; i++) {
            if (solution[i]) {
                itemCount++;
            }
        }

        if (!(*found) || itemCount < *bestItemCount ||
            (itemCount == *bestItemCount && compareSolutions(solution, bestSolution, numItems) < 0)) {
            for (int i = 0; i < numItems; i++) {
                bestSolution[i] = solution[i];
            }
            *bestItemCount = itemCount;
            *found = 1;
        }
    }

    if (index >= numItems) {
        return; 
    }

    solution[index] = 1;
    backtracking(index + 1, currentWeight + weights[index], currentValue + values[index],
        solution, bestSolution, weights, values, numItems, capacity, minValue, bestItemCount, found);

    solution[index] = 0;
    backtracking(index + 1, currentWeight, currentValue, solution, bestSolution,
        weights, values, numItems, capacity, minValue, bestItemCount, found);
}


int compareSolutions(int* sol1, int* sol2, int numItems) {
    for (int i = 0; i < numItems; i++) {
        if (sol1[i] != sol2[i]) {
            return sol2[i] - sol1[i];
        }
    }
    return 0;
}