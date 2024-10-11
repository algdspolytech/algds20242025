#include "test.h"

void runAllTests() {
  compareWords_Equal_return0();
  compareWords_LeftBigger_returnMinus1();
  compareWords_LeftLowwer_return1();
  compareWords_LeftEmpty_returnMinus1();

  push_Standart_InsertHelloWorld();
  pop_Standart_InsertHelloWorld();
  pop_ListWithOnlyHeader_InsertTerminator();

  insertAfter_Standart_CorrectNext();
  insertAfter_Standart_CorrectPrevious();

  sortList_Standart_IsertSortedList();
}

void compareWords_LeftBigger_returnMinus1() {
  assert(compareWords("apple", "banna") == -1);
}

void compareWords_LeftLowwer_return1() {
  assert(compareWords("banna", "apple") == 1);
}

void compareWords_Equal_return0() {
  assert(compareWords("apple", "apple") == 0);
}

void compareWords_LeftEmpty_returnMinus1() {
  assert(compareWords("", "apple") == -1);
}

void push_Standart_InsertHelloWorld() {
  Node head = {NULL, NULL};
  char str[20] = "Hello world\0";
  push(&head, str);
  assert(strcmp(head.next->val, str) == 0);
}

void pop_Standart_InsertHelloWorld() {
  Node head = {NULL, NULL};
  char str[20] = "Hello world\0";
  Node next = {str, NULL};
  head.next = &next;
  char res[20];
  pop(&head, res);
  assert(strcmp(res, str) == 0);
}

void pop_ListWithOnlyHeader_InsertTerminator() {
  Node head = {NULL, NULL};
  char res[20] = "";
  pop(&head, res);
  assert(strcmp(res, "\0") == 0);
}

void insertAfter_Standart_CorrectNext() {
  Node A = {"A", NULL};
  Node C = {"C", NULL};
  A.next = &C;

  insertAfter(&A, "B");
  assert(strcmp(A.next->val, "B") == 0);
}

void insertAfter_Standart_CorrectPrevious() {
  Node A = {"A", NULL};
  Node C = {"C", NULL};
  A.next = &C;

  insertAfter(&A, "B");
  assert(A.next->next == &C);
}

void sortList_Standart_IsertSortedList() {

  Node C = {"C", NULL};
  Node D = {"D", &C};
  Node A = {"A", &D};
  Node B = {"B", &A};

  Node head = {NULL, &B};
  sortList(&head);
  char result[4] = "";
  result[0] = head.next->val[0];
  result[1] = head.next->next->val[0];
  result[2] = head.next->next->next->val[0];
  result[3] = head.next->next->next->next->val[0];

  char *tocomp = "ABCD";
  assert(strcmp(result, tocomp) == 0);
}