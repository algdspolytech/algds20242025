#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodel {
  int vertex;
  int length;
  struct Nodel *next;
} Nodel;

typedef struct {
  int num_vertex;
  Nodel **list;
} adjacency_list;

adjacency_list *GetList(const char *filename);