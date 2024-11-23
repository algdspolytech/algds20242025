#include "code.h"


void readInput(const char* filename, int* B, int** A, int* N) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}

	fscanf(file, "%d", B);
	fscanf(file, "%d", N);

	*A = (int*)malloc((*N) * sizeof(int));
	for (int i = 0; i < *N; i++) {
		fscanf(file, "%d", &((*A)[i]));
	}

	fclose(file);
}

void writeOutput(const char* filename, int* result, int size) {
	FILE* file = fopen(filename, "w");
	if (!file) {
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}

	if (size == 0) {
		fprintf(file, "0");
	}
	else {
		for (int i = 0; i < size; i++) {
			fprintf(file, "%d ", result[i]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

int subsetSum(int B, int* A, int N, int** result) {
	int** dp = (int**)malloc((N + 1) * sizeof(int*));
	for (int i = 0; i <= N; i++) {
		dp[i] = (int*)calloc(B + 1, sizeof(int));
	}


	for (int i = 0; i <= N; i++) {
		dp[i][0] = 1;
	}


	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= B; j++) {
			if (A[i - 1] > j) {
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = dp[i - 1][j] || dp[i - 1][j - A[i - 1]];
			}
		}
	}

	if (!dp[N][B]) {
		for (int i = 0; i <= N; i++) {
			free(dp[i]);
		}
		free(dp);
		return 0;
	}

	int* res = (int*)malloc(N * sizeof(int));
	int idx = 0;
	int w = B;

	for (int i = N; i > 0 && w >= 0; i--) {
		if (!dp[i - 1][w]) {
			res[idx++] = A[i - 1];
			w -= A[i - 1];
		}
	}

	for (int i = 0; i < idx / 2 + 1; i++) {
		int tmp = res[i];
		res[i] = res[idx - i - 1];
		res[idx - i - 1] = tmp;
	}

	*result = res;
	for (int i = 0; i <= N; i++) {
		free(dp[i]);
	}
	free(dp);
	return idx;
}
