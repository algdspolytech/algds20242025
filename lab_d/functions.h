#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_NUMBERS 100
#include <stdbool.h>


bool isSubsetSum(int arr[], int n, int S, bool dp[][MAX_NUMBERS+1]);
void findSubset(int arr[], int parent[], int v, int subset[], int* subset_size, int n);
int dfs(int arr[], int n, int v, int index, int current_sum, int subset[], int* subset_size);
int compareArrays(int arr1[], int size1, int arr2[], int size2);
void readDataFromFile(const char* filename, int* n, int* S, int arr[]);
void writeResultToFile(const char* filename, int subset[], int subset_size);

#endif
