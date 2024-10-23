#include <gtest/gtest.h>
extern "C" {
#include "list.h"
}

//Тесты функций, работающих со структурой
TEST(ListTest, push_front_EmptyList_returnValidVal) {
  Node *head = NULL;

  push_front(&head, "Test");

  ASSERT_TRUE(head != NULL);
  ASSERT_STREQ(head->data, "Test");

  free_list(&head);
}

TEST(ListTest, push_front_NonEmptyList_returnValidVal) {
  Node *head = NULL;

  push_front(&head, "First");
  push_front(&head, "Second");

  ASSERT_TRUE(head != NULL);
  ASSERT_STREQ(head->data, "Second");
  ASSERT_STREQ(head->next->data, "First");

  free_list(&head);
}


TEST(ListTest, push_back_EmptyList_returnValidVal) {
  Node *head = NULL;

  push_back(&head, "Test");

  ASSERT_TRUE(head != NULL);
  ASSERT_STREQ(head->data, "Test");

  free_list(&head);
}

TEST(ListTest, push_back_NonEmptyList_returnValidVal) {
  Node *head = NULL;

  push_back(&head, "First");
  push_back(&head, "Second");

  ASSERT_TRUE(head != NULL);
  ASSERT_STREQ(head->next->data, "Second");

  free_list(&head);
}


TEST(ListTest, pop_front_EmptyList_returnNull) {
  Node *head = NULL;

  pop_front(&head);

  ASSERT_TRUE(head == NULL);
}

TEST(ListTest, pop_front_NonEmptyList_returnValidVal) {
  Node *head = create_node("Test");

  pop_front(&head);

  ASSERT_TRUE(head == NULL);
}

TEST(ListTest, pop_back_EmptyList_returnNull) {
  Node *head = NULL;

  pop_back(&head);

  ASSERT_TRUE(head == NULL);
}

TEST(ListTest, pop_back_NonEmptyList_returnValidVal) {
  Node *head = create_node("Test");

  pop_back(&head);

  ASSERT_TRUE(head == NULL);
}

//Тесты на сортировку merge_sort
TEST(SortTest, merge_sort_EmptyList_returnNull) {
  Node *head = NULL;

  merge_sort(&head);

  ASSERT_TRUE(head == NULL);
}

TEST(SortTest, merge_sort_OneElementList_returnValidVal) {
  Node *head = create_node("Single");

  merge_sort(&head);

  ASSERT_TRUE(head != NULL);
  ASSERT_STREQ(head->data, "Single");

  free_list(&head);
}

TEST(SortTest, merge_sort_SortedList_returnValidVal) {
  Node *head = NULL;

  push_back(&head, "Apple");
  push_back(&head, "Banana");
  merge_sort(&head);

  ASSERT_STREQ(head->data, "Apple");
  ASSERT_STREQ(head->next->data, "Banana");

  free_list(&head);
}

TEST(SortTest, merge_sort_ReversedList_returnValidVal) {
  Node *head = NULL;

  push_back(&head, "Banana");
  push_back(&head, "Apple");
  merge_sort(&head);

  ASSERT_STREQ(head->data, "Apple");
  ASSERT_STREQ(head->next->data, "Banana");

  free_list(&head);
}

TEST(SortTest, merge_sort_LargeList_returnValidVal) {
  Node *head = NULL;

  push_back(&head, "Zebra");
  push_back(&head, "Apple");
  push_back(&head, "Banana");
  push_back(&head, "Orange");
  push_back(&head, "Grapes");
  merge_sort(&head);

  ASSERT_STREQ(head->data, "Apple");
  ASSERT_STREQ(head->next->data, "Banana");
  ASSERT_STREQ(head->next->next->data, "Grapes");
  ASSERT_STREQ(head->next->next->next->data, "Orange");
  ASSERT_STREQ(head->next->next->next->next->data, "Zebra");

  free_list(&head);
}


TEST(SortTest, merge_sort_LargeElementStrings_returnValidVal) {
  Node *head = NULL;
  // Можно было вынести вынести в константы стороки, но мне показалось, что это уже будет оверинжиниринг, уже натыкался
  push_back(&head, "Zzzzzzzzzzzzzzzzzzzzzzz");
  push_back(&head, "Aaaaaaaaaaaaaaaaaaaaaaa");
  push_back(&head, "Mmmmmmmmmmmmmmmmmmmmmm");
  merge_sort(&head);

  ASSERT_STREQ(head->data, "Aaaaaaaaaaaaaaaaaaaaaaa");
  ASSERT_STREQ(head->next->data, "Mmmmmmmmmmmmmmmmmmmmmm");
  ASSERT_STREQ(head->next->next->data, "Zzzzzzzzzzzzzzzzzzzzzzz");

  free_list(&head);
}

TEST(SortTest, merge_sort_LargeListOfEqualStrings_returnValidVal) {
  Node *head = NULL;

  for (int i = 0; i < 1000; ++i) {
    push_back(&head, "EqualString");
  }
  merge_sort(&head);

  Node *temp = head;

  while (temp != NULL) {
    ASSERT_STREQ(temp->data, "EqualString");
    temp = temp->next;
  }

  free_list(&head);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
