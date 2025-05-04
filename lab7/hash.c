#include "hash.h"
#include "stdlib.h"
#include "string.h"

int hash_fun(const char *key, int size) {
  int sum = 0;
  for (int i = 0; i < strlen(key); i++) {
    sum += key[i];
  }

  return sum % size;
}

Table *CreateTable(int size) {
  Table *t = malloc(sizeof(Table));
  t->size = size;
  t->elements = calloc(size, sizeof(Element *));
  return t;
}

const char *Search(Table *table, const char *key) {
  int index = hash_fun(key, table->size);

  Element *current = table->elements[index];

  const char *result = NULL;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      result = current->val;
      break;
    } else {
      current = current->next;
    }
  }

  return result;
}

void Insert(Table *table, const char *key, const char *val) {
  int index = hash_fun(key, table->size);

  Element *current = table->elements[index];

  int can_be_added = 1;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      can_be_added = 0;
      break;
    } else {
      current = current->next;
    }
  }

  if (can_be_added) {
    Element *new_el = malloc(sizeof(Element));
    new_el->key = key;
    new_el->val = val;
    new_el->next = table->elements[index];
    table->elements[index] = new_el;
  } else {
    table->elements[index]->val = val;
  }
}

void Delete(Table *table, const char *key) {
  int index = hash_fun(key, table->size);

  Element *current = table->elements[index];
  Element *prev = NULL;

  char *result = NULL;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      if (prev == NULL) {
        table->elements[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      break;
    } else {
      prev = current;
      current = current->next;
    }
  }
}

void KillTable(Table *table) {
  for (int i = 0; i < table->size; i++) {
    Element *cur = table->elements[i];
    while (cur != NULL) {
      Element *last = cur;
      cur = cur->next;
      free(last);
    }
  }
  free(table->elements);
  free(table);
}