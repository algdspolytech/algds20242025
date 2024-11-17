#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define CRT_SECURE_NO_WARNINGS
#define MAX_N 1000

void read_f(const char* ch, int* b, int* n, int arr[]);
void findSubsetWithSum(int set[], int n, int target, FILE* file);
bool findSubset(int set[], int n, int target);
void putToFile(const char* filename, int* sequence, int n, int b);






