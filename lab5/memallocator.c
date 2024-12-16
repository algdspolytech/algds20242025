#include "memallocator.h"
#include <stdlib.h>

typedef struct block {
  int size;
  int isfree;
  struct block *next;
} block;

void *mem = NULL;
int msize = 0;
block *head = NULL;
block *last = NULL;

int meminit(void *pMemory, int size) {
  if (pMemory == NULL || size <= sizeof(block)) {
    return 0;
  }

  mem = pMemory;
  msize = size;

  head = (block *)pMemory;
  head->size = size - sizeof(block);
  head->isfree = 0;
  head->next = NULL;

  last = head;
  return 1;
}

void memdone() {
  head = NULL;
  last = NULL;
  msize = 0;
  mem = NULL;
}

void *memalloc(int size) {

  if (size <= 0 || !mem) {
    return NULL;
  }

  block *t = NULL;
  if (last) {
    t = last->next;
  } else {
    t = head;
  }

  block *st = t;

  do {
    if (!t) {
      t = head;
    }
    if (!t->isfree && t->size >= size) {
      break;
    }
    t = t->next;
  } while (t != st);

  if (!t || t->isfree || t->size < size) {
    return NULL;
  }

  if (t->size >= size + sizeof(block)) {
    block *nb = (block *)((char *)t + sizeof(block) + size);
    nb->size = t->size - size - sizeof(block);
    nb->isfree = 0;
    nb->next = t->next;

    t->next = nb;
    t->size = size;
  }

  t->isfree = 1;
  last = t;
  return (void *)((char *)t + sizeof(block));
}

void memfree(void *p) {

  if (!p) {
    return;
  }

  block *t = (block *)((char *)p - sizeof(block));
  if (!t->isfree) {
    return;
  }

  t->isfree = 0;

  if (t->next && !t->next->isfree) {
    t->size += t->next->size + sizeof(block);
    t->next = t->next->next;
  }

  block *prev = head;
  while (prev && prev->next != t) {
    prev = prev->next;
  }

  if (prev && !prev->isfree) {
    prev->size += t->size + sizeof(block);
    prev->next = t->next;
  }
}

int memgetminimumsize() { return sizeof(block); }

int memgetblocksize() { return sizeof(block); }