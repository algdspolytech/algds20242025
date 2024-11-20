#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int isAvaible(int element, int **connections, int *used, int n) {

  for (int i = 0; i < n; i++) {

    if (connections[i][0] == element) {
      if (used[connections[i][1]] == 1) {
        return 0;
      }
    }
  }
  return 1;
}

void stepBack(int *amount, int *sum_time, int *used, int *times, int index) {
  *amount -= 1;
  *sum_time -= times[index];
  used[index] = 0;
}

void addToString(char **str, char element) {

  if (*str == NULL) {
    *str = malloc(1);
    *str[0] = '\0';
  }

  int new_size = strlen(*str) + 2;

  char *temp = malloc(new_size);
  strcpy(temp, *str);
  temp[new_size - 2] = element;
  temp[new_size - 1] = '\0';
  free(*str);
  *str = temp;
}

void printReverse(char *str) {
  int len = strlen(str);
  for (int i = len - 2; i >= 0; i--) {
    printf("%c", str[i]);
  }
}

void intToStr(int N, char *str) {
  int i = 0;

  N = abs(N);

  while (N > 0) {

    str[i++] = N % 10 + '0';
    N /= 10;
  }

  str[i] = '\0';
  for (int j = 0, k = i - 1; j < k; j++, k--) {
    char temp = str[j];
    str[j] = str[k];
    str[k] = temp;
  }
}

int findComb(int W, int D, int K, int n, int **depends, int *used, int *times,
             int current, int *ammount, int *sum_time, int *max, char **res) {

  used[current] = 1;
  *ammount += 1;
  *sum_time += times[current];
  if (*sum_time > D) {
    stepBack(ammount, sum_time, used, times, current);
    return 0;
  }

  if (isAvaible(current, depends, used, n)) {
    for (int i = 0; i < W; i++) {
      if (used[i] == 0) {

        findComb(W, D, K, n, depends, used, times, i, ammount, sum_time, max,
                 res);
      }
    }
    if (*ammount < (W - K)) {
      stepBack(ammount, sum_time, used, times, current);
      return 0;
    }
  } else {
    stepBack(ammount, sum_time, used, times, current);
    return 0;
  }

  char buf[8];
  intToStr(current + 1, buf);
  int len = strlen(buf);
  // printf("%d\n",len);
  for (int i = 0; i < len; i++) {
    addToString(res, buf[i]);
  }
  addToString(res, ' ');

  return 1;
}

// TEST ZONE

void intToStr_Standart_CorrectStr() {
  char *res;
  intToStr(123, res);

  assert(strcmp(res, "123") == 0);
}

void intToStr_Negative_AbsVal() {
  char *res;
  intToStr(-123, res);

  assert(strcmp(res, "123") == 0);
}

void addToString_Sandart_CorrectAddition() {
  char *string = malloc(3);
  string[0] = '1';
  string[1] = '2';
  string[2] = '\0';

  addToString(&string, '3');
  assert(strcmp(string, "123") == 0);
}

void addToString_EmptyString_CorrectAddition() {
  char *string = malloc(1);
  string[0] = '\0';

  addToString(&string, '1');
  assert(strcmp(string, "1") == 0);
}

void addToString_NullPointer_CreateAndAddition() {
  char *string = NULL;
  addToString(&string, '1');
  assert(strcmp(string, "1") == 0);
}

void isAvaible_WithoutChangedOrder_return1() {

  int element = 1;
  int n = 0;

  int **connections = NULL;

  int *used = calloc(3, sizeof(int));
  used[0] = 1;
  used[1] = 0;
  used[2] = 1;

  assert(isAvaible(element, connections, used, n) == 1);
}

void isAvaible_OneBiggerThenTwoAndOneIsnotUsed_return1() {

  int element = 0;
  int n = 1;

  int **connections = calloc(n, sizeof(int *));
  for (int i = 0; i < 2; i++) {
    connections[i] = calloc(2, sizeof(int));
  }

  connections[0][0] = 1;
  connections[0][1] = 0;

  int *used = calloc(n, sizeof(int));
  used[1] = 1;

  assert(isAvaible(element, connections, used, n) == 1);
}

void isAvaible_OneBiggerThenTwoAndOneIsAlreadyUsed_return0() {

  int element = 1;
  int n = 1;

  int **connections = calloc(n, sizeof(int *));
  for (int i = 0; i < 2; i++) {
    connections[i] = calloc(2, sizeof(int));
  }

  connections[0][0] = 1;
  connections[0][1] = 0;

  int *used = calloc(n, sizeof(int));
  used[0] = 1;

  assert(isAvaible(element, connections, used, n) == 0);
}

void findComb_Standart_IsCorrectWay() {
  int W, D, K;

  W = 3;
  D = 6;
  K = 0;

  int *times = calloc(W, sizeof(int));

  times[0] = 1;
  times[1] = 2;
  times[2] = 3;

  int n = 2;
  // fscanf(data, "%d", &n);

  int **connections = calloc(n, sizeof(int *));
  for (int i = 0; i < n; i++) {
    connections[i] = calloc(2, sizeof(int));
  }

  connections[0][0] = 2;
  connections[1][0] = 3;

  connections[0][1] = 1;
  connections[1][1] = 1;

  int *used = calloc(W, sizeof(int));

  char *result = malloc(1);
  result[0] = '\0';

  int SumTime = 0;
  int Ammount = 0;
  int maxTime = 0;
  int res = findComb(W, D, K, n, connections, used, times, 0, &Ammount,
                     &SumTime, &maxTime, &result);

  // printf("%s",result);
  assert(strcmp(result, "2 3 1 ") == 0);
}

void findComb_LackOfTime_EmptyString() {
  int W, D, K;

  W = 3;
  D = 5;
  K = 0;

  int *times = calloc(W, sizeof(int));

  times[0] = 1;
  times[1] = 2;
  times[2] = 3;

  int n = 2;
  // fscanf(data, "%d", &n);

  int **connections = calloc(n, sizeof(int *));
  for (int i = 0; i < n; i++) {
    connections[i] = calloc(2, sizeof(int));
  }

  connections[0][0] = 2;
  connections[1][0] = 3;

  connections[0][1] = 1;
  connections[1][1] = 1;

  int *used = calloc(W, sizeof(int));

  char *result = malloc(1);
  result[0] = '\0';

  int SumTime = 0;
  int Ammount = 0;
  int maxTime = 0;
  int res = findComb(W, D, K, n, connections, used, times, 0, &Ammount,
                     &SumTime, &maxTime, &result);

  // printf("%s",result);
  assert(strcmp(result, "") == 0);
}

void runAllTest() {

  intToStr_Standart_CorrectStr();
  intToStr_Negative_AbsVal();

  addToString_Sandart_CorrectAddition();
  addToString_EmptyString_CorrectAddition();
  // addToString_StringWithoutTerminator_IgnoreAndCorrectAddition();
  addToString_NullPointer_CreateAndAddition();

  isAvaible_WithoutChangedOrder_return1();

  isAvaible_OneBiggerThenTwoAndOneIsnotUsed_return1();
  isAvaible_OneBiggerThenTwoAndOneIsAlreadyUsed_return0();

  findComb_Standart_IsCorrectWay();
  findComb_LackOfTime_EmptyString();
}
/////////////////

int main() {

  int W, D, K;

  FILE *data = fopen("input.txt", "r");
  fscanf(data, "%d %d %d", &W, &D, &K);

  int *times = calloc(W, sizeof(int));

  for (int i = 0; i < W; i++) {
    fscanf(data, "%d", &times[i]);
  }

  int n;
  fscanf(data, "%d", &n);

  int **connections = calloc(n, sizeof(int *));
  for (int i = 0; i < n; i++) {
    connections[i] = calloc(2, sizeof(int));
  }

  for (int i = 0; i < n; i++) {
    int a, b;
    fscanf(data, "%d %d", &a, &b);
    connections[i][0] = a - 1;
    connections[i][1] = b - 1;
  }

  int *used = calloc(W, sizeof(int));

  char *result = malloc(1);
  result[0] = '\0';

  int SumTime = 0;
  int Ammount = 0;
  int maxTime = 0;
  int res = findComb(W, D, K, n, connections, used, times, 0, &Ammount,
                     &SumTime, &maxTime, &result);

  if (strcmp(result, "") == 0) {
    printf("%d", 0);
  } else {
    printReverse(result);
  }

  runAllTest();
  return 0;
}