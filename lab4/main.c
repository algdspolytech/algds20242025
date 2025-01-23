#define _CRT_SECURE_NO WARNINGS
#include <stdio.h>
#include "sum_sizes.h"

int main() {
    int B, N;
    int arr[MAX_N];
    int res[MAX_N];
    int resSize = 0;

    if (!readInput("input.txt", &B, arr, &N)) {
        return 1;
    }

    if (sumSizes(arr, N, B, res, &resSize)) {
        writeOutput("output.txt", res, resSize);
    }
    else {
        writeOutput("output.txt", NULL, 0);
    }

    return 0;
}
