#include "matrix.h"

int **initMA(int n) {
  if (n <= 0) {
    return NULL;
  }

  int **res = calloc(sizeof(int *), n);
  for (int i = 0; i < n; i++) {
    res[i] = calloc(sizeof(int), n);
  }
  return res;
}

int **readMatrix(FILE *f, int **matrix, int n, int m) {

  int temp;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      fscanf(f, "%d", &temp);
      matrix[i][j] = temp;
    }
  }

  return matrix;
}

void showMa(int **ma, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", ma[i][j]);
    }
    printf("\n");
  }
}

int killMatrix(int **ma, int n) {
  if (ma != NULL) {
    for (int i = 0; i < n; i++) {
      ma[i] = NULL;
      free(ma[i]);
    }
    ma = NULL;
    free(ma);
    return 0;
  }
  return 1;
}

int compareMatrixes(int **A, int **B, int n) {
  int flag = 1;
  for (int i = 0; i < n; i++ && flag) {
    for (int j = 0; j < n; j++ && flag) {
      if (A[i][j] != B[i][j])
        flag = 0;
    }
  }

  return flag;
}