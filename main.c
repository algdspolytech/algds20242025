#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#pragma warning(disable:4996)
#define MAX_ITEMS 1000


// Function prototypes
void backtracking(int index, int currentWeight, int currentValue, int* solution, int* bestSolution,
    int* weights, int* values, int numItems, int capacity, int minValue,
    int* bestItemCount, int* found);

int compareSolutions(int* sol1, int* sol2, int numItems);

// Entry point
int main() {
    int U, B, K; // Number of items, capacity, minimum value
    int weights[MAX_ITEMS], values[MAX_ITEMS];
    int solution[MAX_ITEMS] = { 0 }, bestSolution[MAX_ITEMS] = { 0 };

    // Open input file
    FILE* inputFile = fopen("input.txt", "r");
    if (!inputFile) {
        fprintf(stderr, "Error: Cannot open input file.\n");
        return 1;
    }

    // Read U, B, K
    fscanf(inputFile, "%d %d %d", &U, &B, &K);

    // Read weights
    for (int i = 0; i < U; i++) {
        fscanf(inputFile, "%d", &weights[i]);
    }

    // Read values
    for (int i = 0; i < U; i++) {
        fscanf(inputFile, "%d", &values[i]);
    }

    fclose(inputFile);

    int found = 0;
    int bestItemCount = U + 1; // Initially set to max possible + 1

    // Solve using backtracking
    backtracking(0, 0, 0, solution, bestSolution, weights, values, U, B, K, &bestItemCount, &found);

    // Write result to output file
    FILE* outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fprintf(stderr, "Error: Cannot open output file.\n");
        return 1;
    }

    if (found) {
        for (int i = 0; i < U; i++) {
            if (bestSolution[i]) {
                fprintf(outputFile, "%d ", i + 1); // Output 1-based index
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

// Backtracking function
void backtracking(int index, int currentWeight, int currentValue, int* solution, int* bestSolution,
    int* weights, int* values, int numItems, int capacity, int minValue,
    int* bestItemCount, int* found) {

    if (currentWeight > capacity) {
        return; // Over capacity, backtrack
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
            // Update best solution
            for (int i = 0; i < numItems; i++) {
                bestSolution[i] = solution[i];
            }
            *bestItemCount = itemCount;
            *found = 1;
        }
        // Continue searching for potentially better solutions
    }

    if (index >= numItems) {
        return; // No more items to process
    }

    // Include current item
    solution[index] = 1;
    backtracking(index + 1, currentWeight + weights[index], currentValue + values[index],
        solution, bestSolution, weights, values, numItems, capacity, minValue, bestItemCount, found);

    // Exclude current item
    solution[index] = 0;
    backtracking(index + 1, currentWeight, currentValue, solution, bestSolution,
        weights, values, numItems, capacity, minValue, bestItemCount, found);
}

// Function to compare two solutions lexicographically
int compareSolutions(int* sol1, int* sol2, int numItems) {
    for (int i = 0; i < numItems; i++) {
        if (sol1[i] != sol2[i]) {
            return sol2[i] - sol1[i]; // Инвертируем вычитание для предпочтения ранних индексов
        }
    }
    return 0;
}
