#pragma once
#define MAX_N 1000

int readFile(const char* filename, int* B, int* N, int* A, int* flagArr);
void Write(const char* filename, int* res, int* flag, int* resSize);
void sum_size(int* B, int* N, int* A, int dp[], int presum, int* flag, int* res, int* resSize);