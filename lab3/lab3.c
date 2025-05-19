#include "lab3.h"
#include <stdio.h>
#include <stdlib.h>

int *main_program(char *input, char *output) {
  int B, N, *A;
  get_data(input, &B, &N, &A);
  int *res = malloc(sizeof(int) * N);
  int *nums = malloc(sizeof(int) * B);
  for (int i = 0; i < N; i++) {
    res[i] = -1;
  }
  res[0] = 0;
  for (int i = 0; i < B; i++) {
    nums[i] = 0;
  }
  for (int i = 0; i < N; i++) {
    if ((A[i] == A[i] % B)) {
      nums[A[i]]++;
    } else if (A[i] == B) {
      nums[0]++;
    }
  }
  int stop = 0;
  if (nums[0] > 0) {
    res[0] = B;
  } else {
    for (int i = 1; (i < B / 2 + 1) && !stop; i++) {
      if (find_subset(nums, i, B, res, 0)) {
        stop = 1;
      }
    }
  }
  print_to_file(output, res);
  free(nums);
  free(A);
  return res;
}

void get_data(char *name, int *B, int *N, int **A) {
  FILE *file = fopen(name, "r");
  fscanf(file, "%d\n", B);
  fscanf(file, "%d\n", N);
  char *str = malloc(200 * (*N));
  str = fgets(str, 100 * (*N), file);
  (*A) = malloc(sizeof(int) * (*N));
  int num, flag = 0, counter = 0;
  for (char *i = str; (*i) != '\0'; i++) {
    if (!flag) {
      sscanf(i, "%d", &num);
      (*A)[counter] = num;
      counter++;
      flag++;
    } else if ((*i) == ' ') {
      flag = 0;
    }
  }
  fclose(file);
  free(str);
}

int find_subset(int *nums, int num, int B, int *res, int pointer) {
  int flag = 0;
  int stop = 0;
  if (B % num == 0 && nums[num] >= (int)(B / num)) {
    flag = 1;
    for (int i = 0; i < (int)(B / num); i++) {
      res[pointer + i] = num;
    }
  } else {
    for (int count = 1; count < nums[num] + 1 && !stop; count++) {
      for (int i = num + 1; i < B; i++) {
        if (find_subset(nums, i, B - count * num, res, pointer + count)) {
          flag = 1;
          break;
        }
      }
      if (flag == 1) {
        stop = 1;
        for (int i = 0; i < count; i++) {
          res[pointer + i] = num;
        }
      }
    }
  }
  return flag;
}

void print_to_file(char *name, int *res) {
  FILE *file = fopen(name, "w");
  for (int *i = res; *i != -1; i++) {
    fprintf(file, "%d ", *i);
  }
  fclose(file);
}
