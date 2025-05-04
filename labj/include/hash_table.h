#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct node {
  char *key;
  struct node *next;
} node;

typedef struct hash_table {
  int size;
  node **buckets;
} hash_table;

unsigned long hash_func(const char *str, int size);
hash_table *create_table(int size);
void insert(hash_table *table, const char *key);
int search(hash_table *table, const char *key);
void delete(hash_table *table, const char *key);
void free_table(hash_table *table);

#endif
