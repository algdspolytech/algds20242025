#include "../include/hash_table.h"
#include <stdlib.h>
#include <string.h>

unsigned long hash_func(const char *str, int size) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash % size;
}

hash_table *create_table(int size) {
  hash_table *table = malloc(sizeof(hash_table));
  table->size = size;
  table->buckets = calloc(size, sizeof(node *));
  return table;
}

void insert(hash_table *table, const char *key) {
  unsigned long index = hash_func(key, table->size);
  node *current = table->buckets[index];

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return;
    }
    current = current->next;
  }

  node *new_node = malloc(sizeof(node));
  new_node->key = strdup(key);
  new_node->next = table->buckets[index];
  table->buckets[index] = new_node;
}

int search(hash_table *table, const char *key) {
  unsigned long index = hash_func(key, table->size);
  node *current = table->buckets[index];

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return 1;
    }
    current = current->next;
  }
  return 0;
}

void delete(hash_table *table, const char *key) {
  unsigned long index = hash_func(key, table->size);
  node *current = table->buckets[index];
  node *prev = NULL;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      if (prev == NULL) {
        table->buckets[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current->key);
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
}

void free_table(hash_table *table) {
  for (int i = 0; i < table->size; i++) {
    node *current = table->buckets[i];
    while (current != NULL) {
      node *tmp = current;
      current = current->next;
      free(tmp->key);
      free(tmp);
    }
  }
  free(table->buckets);
  free(table);
}
