#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct adjacency_matrix {
  int **matrix;
  int length;
} adjacency_matrix;

adjacency_matrix *GetMatrix(const char *filename);