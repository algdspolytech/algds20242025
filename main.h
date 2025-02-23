#ifndef MAIN_H
#define MAIN_H

#define MAX_ITEMS 1000

#ifdef __cplusplus
extern "C" {
#endif

    void backtracking(int index, int currentWeight, int currentValue, int* solution, int* bestSolution,
        int* weights, int* values, int numItems, int capacity, int minValue,
        int* bestItemCount, int* found);

    int compareSolutions(int* sol1, int* sol2, int numItems);

#ifdef __cplusplus
}
#endif

#endif // MAIN_H