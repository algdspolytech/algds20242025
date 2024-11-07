#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NUMBERS 100

bool isSubsetSum(int arr[], int n, int S, bool dp[MAX_NUMBERS+1][MAX_NUMBERS + 1]) {
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }
    for (int j = 1; j <= S; j++) {
        dp[0][j] = false;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= S; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= arr[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }
    return dp[n][S];
}

void getSubset(int arr[], int n, int S, bool dp[MAX_NUMBERS + 1][MAX_NUMBERS + 1], int subset[], int* subset_size) {
    int sum = S;
    *subset_size = 0;
    for (int i = n; i > 0 && sum > 0; i--) {
        if (!dp[i - 1][sum]) {
            subset[*subset_size] = arr[i - 1];
            (*subset_size)++;
            sum -= arr[i - 1];
        }
    }
}

int dfs(int arr[], int n, int v, int index, int current_sum, int subset[], int* subset_size) {
    if (current_sum == v) {
        return 1;
    }
    if (index >= n || current_sum > v || *subset_size >= n) {
        return 0;
    }
    subset[*subset_size] = arr[index];
    (*subset_size)++;
    if (dfs(arr, n, v, index + 1, current_sum + arr[index], subset, subset_size)) {
        return 1;
    }
    (*subset_size)--;
    if (dfs(arr, n, v, index + 1, current_sum, subset, subset_size)) {
        return 1;
    }
    return 0;
}

int compareArrays(int arr1[], int size1, int arr2[], int size2) {
    if (size1 != size2) {
        return 0;
    }
    for (int i = 0; i < size1; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}

void readDataFromFile(const char* filename, int* n, int* S, int arr[]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла для чтения\n");
        exit(1);
    }

    fscanf(file, "%d", n); 
    fscanf(file, "%d", S);  
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
}

void writeResultToFile(const char* filename, int subset[], int subset_size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи\n");
        exit(1);
    }

    fprintf(file, "Подмножество с заданной суммой:\n");
    for (int i = 0; i < subset_size; i++) {
        fprintf(file, "%d ", subset[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}