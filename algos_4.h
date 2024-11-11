
#pragma once
#ifndef SUBSET_SUM_H
#define SUBSET_SUM_H

#define MAX_N 1000

int readInput(const char* filename, int* B, int* arr, int* N);
void writeOutput(const char* filename, int* result, int resultSize);
int subsetSum(int arr[], int n, int B, int result[], int* resultSize);

#endif // SUBSET_SUM_H
