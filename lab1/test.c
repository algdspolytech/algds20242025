#include "test.h"

void runAllTests() {
  compareWords_Equal_return0();
  compareWords_LeftBigger_returnMinus1();
  compareWords_LeftLowwer_return1();
  compareWords_LeftEmpty_returnMinus1();

  push_Standart_CorretctInsert();

  pop_Standart_InsertHelloWorld();
  pop_ListWithOnlyHeader_InsertTerminator();

  insertAfter_Standart_CorrectNext();
  insertAfter_Standart_CorrectPrevious();

  merge_Standart_SortedFirstList();
  merge_LeftEmpty_SortedFirstList();
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

void push_Standart_CorretctInsert() {

  Node c = {"c", NULL};
  Node a = {"a", &c};

  Node head = {NULL, &a};
  push(&head, "b");
  assert(strcmp(a.next->val, "b") == 0);
}

void pop_Standart_InsertHelloWorld() {
  Node head = {NULL, NULL};
  char str[20] = "Hello world\0";

  head.next = (Node *)malloc(sizeof(Node));
  head.next->val = strdup(str);
  head.next->next = NULL;
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

void merge_Standart_SortedFirstList() {
  Node c = {"c", NULL};
  Node a = {"a", &c};
  Node h1 = {NULL, &a};

  Node *b = malloc(sizeof(Node));
  b->val = strdup("b");
  b->next = NULL;
  Node h2 = {NULL, b};

  merge(&h1, &h2);
  assert(strcmp(h1.next->next->val, "b") == 0);
}

void merge_LeftEmpty_SortedFirstList() {

  Node h1 = {NULL, NULL};

  Node h2 = {NULL, NULL};
  h2.next = malloc(sizeof(Node));
  h2.next->val = "a";
  h2.next->next = malloc(sizeof(Node));
  h2.next->next->val = "b";
  merge(&h1, &h2);
  assert(strcmp(h1.next->next->val, "b") == 0);
}