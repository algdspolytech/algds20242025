#include "UnrolledLinkedList.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void);

void tearDown(void);
void test_add_to_empty_list_no1(void);
void test_add_to_filled_list_no2(void);
void test_add_to_filled_list_no3(void);
void test_get_element_in_empty_list_no4(void);
void test_get_element_in_filled_list_no5(void);
void test_get_element_by_big_index_no6(void);
void test_get_index_in_empty_list_no7(void);
void test_get_index_in_filled_list_no8(void);
void test_get_index_of_nonexistent_element_no9(void);
void test_get_len_of_empty_list_no10(void);
void test_get_len_of_empty_list_no11(void);
void test_get_next_element_in_empty_list_no12(void);
void test_get_next_element_in_filled_list_no13(void);
void test_get_next_element_of_last_elment_no14(void);
void test_delet_element_in_filled_list_no15(void);
void test_delet_last_element_no16(void);

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_add_to_empty_list_no1);
  RUN_TEST(test_add_to_filled_list_no2);
  RUN_TEST(test_add_to_filled_list_no3);
  RUN_TEST(test_get_element_in_empty_list_no4);
  RUN_TEST(test_get_element_in_filled_list_no5);
  RUN_TEST(test_get_element_by_big_index_no6);
  RUN_TEST(test_get_index_in_empty_list_no7);
  RUN_TEST(test_get_index_in_filled_list_no8);
  RUN_TEST(test_get_index_of_nonexistent_element_no9);
  RUN_TEST(test_get_len_of_empty_list_no10);
  RUN_TEST(test_get_len_of_empty_list_no11);
  RUN_TEST(test_get_next_element_in_empty_list_no12);
  RUN_TEST(test_get_next_element_in_filled_list_no13);
  RUN_TEST(test_get_next_element_of_last_elment_no14);
  RUN_TEST(test_delet_element_in_filled_list_no15);
  RUN_TEST(test_delet_last_element_no16);
  return UNITY_END();
}

void setUp(void) {}

void tearDown(void) {}

void test_add_to_empty_list_no1(void) {
  ull *list = init();
  TEST_ASSERT_EQUAL_PTR(append(list, 3), list->head->arr);
  destroy(list);
}

void test_add_to_filled_list_no2(void) {
  ull *list = init();
  append(list, 4);
  TEST_ASSERT_EQUAL_PTR(append(list, 3), list->head->arr + 1);
  destroy(list);
}

void test_add_to_filled_list_no3(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  int *p = append(list, 3);
  TEST_ASSERT_EQUAL_PTR(p, list->head->next->arr);
  destroy(list);
}

void test_get_element_in_empty_list_no4(void) {
  ull *list = init();
  TEST_ASSERT_EQUAL_PTR(get_element_by_index(list, 0), NULL);
  destroy(list);
}

void test_get_element_in_filled_list_no5(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  TEST_ASSERT_EQUAL_PTR(get_element_by_index(list, 3), list->head->arr + 3);
  destroy(list);
}

void test_get_element_by_big_index_no6(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  TEST_ASSERT_EQUAL_PTR(get_element_by_index(list, 4), NULL);
  destroy(list);
}

void test_get_index_in_empty_list_no7(void) {
  ull *list = init();
  TEST_ASSERT_EQUAL(get_index_by_key(list, 2), -1);
  destroy(list);
}

void test_get_index_in_filled_list_no8(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  TEST_ASSERT_EQUAL(get_index_by_key(list, 6), 2);
  destroy(list);
}

void test_get_index_of_nonexistent_element_no9(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  TEST_ASSERT_EQUAL(get_index_by_key(list, 9), -1);
  destroy(list);
}

void test_get_len_of_empty_list_no10(void) {
  ull *list = init();
  TEST_ASSERT_EQUAL(get_len(list), 0);
  destroy(list);
}

void test_get_len_of_empty_list_no11(void) {
  ull *list = init();
  append(list, 4);
  append(list, 4);
  append(list, 4);
  append(list, 4);
  append(list, 4);
  TEST_ASSERT_EQUAL(get_len(list), 5);
  destroy(list);
}

void test_get_next_element_in_empty_list_no12(void) {
  ull *list = init();
  TEST_ASSERT_EQUAL_PTR(get_next_element(list, 0), NULL);
  destroy(list);
}

void test_get_next_element_in_filled_list_no13(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  append(list, 8);
  TEST_ASSERT_EQUAL_PTR(get_next_element(list, 4), &(list->head->arr[1]));
  destroy(list);
}

void test_get_next_element_of_last_elment_no14(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  append(list, 8);
  TEST_ASSERT_EQUAL_PTR(get_next_element(list, 8), NULL);
  destroy(list);
}

void test_delet_element_in_filled_list_no15(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  append(list, 8);
  delet_element(list, 1);
  TEST_ASSERT_EQUAL(6, list->head->arr[1]);
  destroy(list);
}

void test_delet_last_element_no16(void) {
  ull *list = init();
  append(list, 4);
  append(list, 5);
  append(list, 6);
  append(list, 7);
  append(list, 8);
  delet_element(list, 4);
  TEST_ASSERT_EQUAL(7, *(get_element_by_index(list, get_len(list) - 1)));
  destroy(list);
}
