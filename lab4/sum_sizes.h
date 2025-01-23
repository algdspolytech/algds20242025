
#pragma once
#ifndef SUM_SIZES_H
#define SUM_SIZES_H

#define MAX_N 1000

int readInput(const char* filename, int* B, int* arr, int* N);
void writeOutput(const char* filename, int* res, int resSize);
int sumSizes(int arr[], int n, int B, int res[], int* resSize);

#endif 