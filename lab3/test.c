#include "lab3.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void);

void tearDown(void);

void test_get_data_n1();
void test_get_data_n2();
void test_get_data_n3();
void test_find_subset_n4();
void test_find_subset_n5();

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_get_data_n1);
  RUN_TEST(test_get_data_n2);
  RUN_TEST(test_get_data_n3);
  RUN_TEST(test_find_subset_n4);
  RUN_TEST(test_find_subset_n5);
  return UNITY_END();
}

void setUp(void) {}

void tearDown(void) {}

void test_get_data_n1() {
  int B, N, *A;
  get_data("input1.txt", &B, &N, &A);
  TEST_ASSERT_EQUAL(B, 11);
  free(A);
}
void test_get_data_n2() {

  int B, N, *A;
  get_data("input1.txt", &B, &N, &A);
  TEST_ASSERT_EQUAL(N, 10);
  free(A);
}
void test_get_data_n3() {

  int B, N, *A;
  get_data("input1.txt", &B, &N, &A);
  int original[10] = {100, 5, 3, 3, 9, 2, 10, 1, 90, 9};
  TEST_ASSERT_EQUAL_INT_ARRAY(A, original, N);
  free(A);
}

void test_find_subset_n4() {
  int *res = main_program("input1.txt", "output1.txt");
  int original[10] = {1, 2, 3, 5, -1, -1, -1, -1, -1, -1};
  TEST_ASSERT_EQUAL_INT_ARRAY(res, original, 10);
  free(res);
}

void test_find_subset_n5() {
  int *res = main_program("input2.txt", "output2.txt");
  int original[10] = {0, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  TEST_ASSERT_EQUAL_INT_ARRAY(res, original, 10);
  free(res);
}
