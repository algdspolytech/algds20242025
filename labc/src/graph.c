#include "../include/graph.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

graph_list parse_list(const char *file_name) {
  graph_list res;
  int **adj_list = NULL;
  res.adj_list = adj_list;
  res.size = 0;
  char *line = NULL;
  size_t len = 0;
  FILE *f = fopen(file_name, "r");
  if (f == NULL) {
    perror("Ошибка при открытии файла");
    res.size = -1;
    return res;
  }
  while (getline(&line, &len, f) >= 0) {
    adj_list = realloc(adj_list, (res.size + 1) * sizeof(int *));
    // в первом элементе хранится число связей
    int *el = calloc(1, sizeof(int));
    adj_list[res.size] = el;
    res.size++;
    char *p, *end;
    for (p = line; *p != '\0'; p = end) {
      int val = strtol(p, &end, 10);
      if (end == p) {
        break;
      }
      el = realloc(el, (el[0] + 2) * sizeof(int));
      el[0]++;
      el[el[0]] = val;
    }
  }
  fclose(f);
  res.adj_list = adj_list;
  return res;
}

graph_matrix parse_matrix(const char *file_name) {
  graph_matrix res;
  int *adj_matrix = NULL;
  res.adj_matrix = adj_matrix;
  res.size = 0;
  char *line = NULL;
  size_t len = 0;
  FILE *f = fopen(file_name, "r");
  if (f == NULL) {
    perror("Ошибка при открытии файла");
    res.size = -1;
    return res;
  }
  while (getline(&line, &len, f) >= 0) {
    char *p, *end;
    for (p = line; *p != '\0'; p = end) {
      int val = strtol(p, &end, 10);
      if (end == p) {
        break;
      }
      adj_matrix = realloc(adj_matrix, (res.size + 1) * sizeof(int));
      adj_matrix[res.size] = val;
      res.size++;
    }
  }
  fclose(f);
  res.adj_matrix = adj_matrix;
  res.size = sqrt(res.size);
  return res;
}

int compare_lm(const graph_list *l, const graph_matrix *m) {
  for (int i = 0; i < l->size; i++) {
    int *tmp = calloc(l->size, sizeof(int));
    for (int j = 1; j <= l->adj_list[i][0]; j++) {
      tmp[l->adj_list[i][j] - 1] = 1;
    }
    for (int j = 0; j < l->size; j++) {
      if (tmp[j] != m->adj_matrix[l->size * i + j]) {
        return 0;
      }
    }
    free(tmp);
  }
  return 1;
}

void del_l(graph_list *l) {
  for (int i = 0; i < l->size; i++) {
    free(l->adj_list[i]);
  }
  free(l->adj_list);
}

void del_m(graph_matrix *m) { free(m->adj_matrix); }
