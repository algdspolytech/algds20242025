#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 101
#define MAX_LOAD 0.7

typedef enum { SLOT_FREE, SLOT_OCCUPIED, SLOT_DELETED } SlotStatus;

typedef struct {
  int *slots;
  SlotStatus *flags;
  int count;
  int cap;
} LinearSet;

unsigned long hash_int(unsigned long x) {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return x;
}

LinearSet *create_set(int cap) {
  LinearSet *set = malloc(sizeof(LinearSet));
  set->slots = malloc(sizeof(int) * cap);
  set->flags = malloc(sizeof(SlotStatus) * cap);
  for (int i = 0; i < cap; ++i)
    set->flags[i] = SLOT_FREE;
  set->cap = cap;
  set->count = 0;
  return set;
}

void free_set(LinearSet *set) {
  if (!set)
    return;
  free(set->slots);
  free(set->flags);
  free(set);
}

int find_position(LinearSet *set, int key, int *found) {
  unsigned long h = hash_int((unsigned long)key);
  int idx = h % set->cap;
  int first_deleted = -1;

  for (int i = 0; i < set->cap; ++i) {
    int pos = (idx + i) % set->cap;
    if (set->flags[pos] == SLOT_OCCUPIED && set->slots[pos] == key) {
      *found = 1;
      return pos;
    }
    if (set->flags[pos] == SLOT_FREE) {
      *found = 0;
      return (first_deleted != -1) ? first_deleted : pos;
    }
    if (set->flags[pos] == SLOT_DELETED && first_deleted == -1)
      first_deleted = pos;
  }
  *found = 0;
  return -1;
}

void reallocate(LinearSet *set) {
  int new_cap = set->cap * 2 + 1;
  LinearSet *new_set = create_set(new_cap);

  for (int i = 0; i < set->cap; ++i) {
    if (set->flags[i] == SLOT_OCCUPIED) {
      int dummy;
      int pos = find_position(new_set, set->slots[i], &dummy);
      new_set->slots[pos] = set->slots[i];
      new_set->flags[pos] = SLOT_OCCUPIED;
      new_set->count++;
    }
  }

  free(set->slots);
  free(set->flags);

  set->slots = new_set->slots;
  set->flags = new_set->flags;
  set->cap = new_set->cap;
  set->count = new_set->count;
  free(new_set);
}

void add(LinearSet *set, int key) {
  if ((double)(set->count + 1) / set->cap > MAX_LOAD)
    reallocate(set);

  int found;
  int pos = find_position(set, key, &found);
  if (!found) {
    set->slots[pos] = key;
    set->flags[pos] = SLOT_OCCUPIED;
    set->count++;
  }
}

void erase(LinearSet *set, int key) {
  int found;
  int pos = find_position(set, key, &found);
  if (found) {
    set->flags[pos] = SLOT_DELETED;
    set->count--;
  }
}

int has(LinearSet *set, int key) {
  int found;
  find_position(set, key, &found);
  return found;
}

int main(void) {
  LinearSet *set = create_set(INITIAL_CAPACITY);
  char op;
  int key;

  while (scanf(" %c %d", &op, &key) == 2) {
    switch (op) {
    case 'a':
      add(set, key);
      break;
    case 'r':
      erase(set, key);
      break;
    case 'f':
      printf("%s\n", has(set, key) ? "yes" : "no");
      break;
    }
  }

  free_set(set);
  return 0;
}