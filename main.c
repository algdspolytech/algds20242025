#define _CRT_SECURE_NO WARNINGS
#include <stdio.h>
#include "algosD/algos_4.h"

int main() {
    int B, N;
    int arr[MAX_N];
    int result[MAX_N];
    int resultSize = 0;

    if (!readInput("input.txt", &B, arr, &N)) {
        return 1;
    }

    if (subsetSum(arr, N, B, result, &resultSize)) {
        writeOutput("output.txt", result, resultSize);
    }
    else {
        writeOutput("output.txt", NULL, 0);
    }

    return 0;
}
