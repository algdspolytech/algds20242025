#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "search.h"
#include "stack.h"
#include "tests.h"

int main() {

  int a, b;
  scanf("%d %d", &a, &b);

  FILE *f = fopen("input.txt", "r");

  int n;
  fscanf(f, "%d", &n);

  int **M = initMA(n);
  readMatrix(f, M, n, n);

  if (CheckWay(n, M, a, b)) {
    printf("The way has been found :)");
  } else {
    printf("Path not found :(");
  }

  runAllTests();

  killMatrix(M, n);
}