#ifndef HASH
#define HASH

typedef struct Element {
  const char *key;
  const char *val;
  struct Element *next;
} Element;

typedef struct Table {
  int size;
  Element **elements;
} Table;

int hash_fun(const char *key, int size);
Table *CreateTable(int size);
const char *Search(Table *table, const char *key);
void Insert(Table *table, const char *key, const char *val);
void Delete(Table *table, const char *key);
void KillTable(Table *table);

#endif