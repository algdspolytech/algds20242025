#include "assert.h"
#include "hash.h"
#include "stdlib.h"
#include "string.h"

// Insert Tests
void Insert_Standart_NewElement() {
  Table *t = CreateTable(3);

  Insert(t, "one", "number : 1");
  int index = ('o' + 'n' + 'e') % 3;
  assert(strcmp(t->elements[index]->val, "number : 1") == 0);

  KillTable(t);
}

void Insert_KeyAlreadyExists_Rewrite() {
  Table *t = CreateTable(3);

  Insert(t, "one", "number : 1");
  Insert(t, "one", "number : new 1");
  int index = ('o' + 'n' + 'e') % 3;

  assert(strcmp(t->elements[index]->val, "number : new 1") == 0);

  KillTable(t);
}

void Insert_Collision_NewElement() {
  Table *t = CreateTable(3);

  Insert(t, "one", "some value 1");
  Insert(t, "eno", "some value 2");

  int index = ('o' + 'n' + 'e') % 3;

  assert(strcmp(t->elements[index]->val, "some value 2") == 0);

  KillTable(t);
}
////////////

// Search Tests
void Search_Standart_CorrectValue() {
  Table *t = CreateTable(3);

  int id_for_new_element = hash_fun("one", 3);
  t->elements[id_for_new_element] = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next = NULL;
  t->elements[id_for_new_element]->key = "one";
  t->elements[id_for_new_element]->val = "value 1";

  const char *res = Search(t, "one");

  assert(strcmp(res, "value 1") == 0);

  KillTable(t);
}

void Search_NoneExisted_Null() {
  Table *t = CreateTable(3);

  const char *res = Search(t, "one");

  assert(res == NULL);

  KillTable(t);
}

void Search_Collision_CorrectValue() {
  Table *t = CreateTable(3);

  int id_for_new_element = hash_fun("one", 3);
  t->elements[id_for_new_element] = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next = NULL;
  t->elements[id_for_new_element]->key = "one";
  t->elements[id_for_new_element]->val = "value 1";

  id_for_new_element = hash_fun("eno", 3);
  t->elements[id_for_new_element]->next = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next->next = NULL;
  t->elements[id_for_new_element]->next->key = "eno";
  t->elements[id_for_new_element]->next->val = "value 2";

  const char *res = Search(t, "eno");

  assert(strcmp(res, "value 2") == 0);

  KillTable(t);
}
/////////

// Delete Test
void Delete_Standart_DeleteCorrectElemnt() {
  Table *t = CreateTable(3);

  int id_for_new_element = hash_fun("one", 3);
  t->elements[id_for_new_element] = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next = NULL;
  t->elements[id_for_new_element]->key = "one";
  t->elements[id_for_new_element]->val = "value 1";

  Delete(t, "one");

  assert(t->elements[id_for_new_element] == NULL);

  KillTable(t);
}

void Delete_CollisionElementAtEndOfList_DeleteCorrectElement() {
  Table *t = CreateTable(3);

  int id_for_new_element = hash_fun("one", 3);
  t->elements[id_for_new_element] = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next = NULL;
  t->elements[id_for_new_element]->key = "one";
  t->elements[id_for_new_element]->val = "value 1";

  id_for_new_element = hash_fun("eno", 3);
  t->elements[id_for_new_element]->next = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next->next = NULL;
  t->elements[id_for_new_element]->next->key = "eno";
  t->elements[id_for_new_element]->next->val = "value 2";

  Delete(t, "eno");

  assert(t->elements[id_for_new_element]->next == NULL);

  KillTable(t);
}

void Delete_CollisionElementAtStartOfList_DeleteCorrectElement() {
  Table *t = CreateTable(3);

  int id_for_new_element = hash_fun("one", 3);
  t->elements[id_for_new_element] = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next = NULL;
  t->elements[id_for_new_element]->key = "one";
  t->elements[id_for_new_element]->val = "value 1";

  id_for_new_element = hash_fun("eno", 3);
  t->elements[id_for_new_element]->next = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next->next = NULL;
  t->elements[id_for_new_element]->next->key = "eno";
  t->elements[id_for_new_element]->next->val = "value 2";

  Delete(t, "one");

  assert(t->elements[id_for_new_element]->next == NULL);

  KillTable(t);
}

void Delete_CollisionElementAtStartOfList_ChangedHeadElementOfList() {
  Table *t = CreateTable(3);

  int id_for_new_element = hash_fun("one", 3);
  t->elements[id_for_new_element] = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next = NULL;
  t->elements[id_for_new_element]->key = "one";
  t->elements[id_for_new_element]->val = "value 1";

  id_for_new_element = hash_fun("eno", 3);
  t->elements[id_for_new_element]->next = malloc(sizeof(Element));
  t->elements[id_for_new_element]->next->next = NULL;
  t->elements[id_for_new_element]->next->key = "eno";
  t->elements[id_for_new_element]->next->val = "value 2";

  Delete(t, "one");

  assert(strcmp(t->elements[id_for_new_element]->val, "value 2") == 0);

  KillTable(t);
}

void RunAllTests() {

  Insert_Standart_NewElement();
  Insert_KeyAlreadyExists_Rewrite();
  Insert_Collision_NewElement();

  Search_Standart_CorrectValue();
  Search_NoneExisted_Null();
  Search_Collision_CorrectValue();

  Delete_Standart_DeleteCorrectElemnt();
  Delete_CollisionElementAtEndOfList_DeleteCorrectElement();
  Delete_CollisionElementAtStartOfList_DeleteCorrectElement();
  Delete_CollisionElementAtStartOfList_ChangedHeadElementOfList();
}

int main() {

  RunAllTests();

  return 0;
}