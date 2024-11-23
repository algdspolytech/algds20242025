#define _CRT_SECURE_NO_WARNINGS

#ifndef code_h
#define code_h

#include <stdio.h>
#include <stdlib.h>

void readInput(const char* filename, int* B, int** A, int* N);

void writeOutput(const char* filename, int* result, int size);

int subsetSum(int B, int* A, int N, int** result);

#endif