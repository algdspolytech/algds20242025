#include "../headers/main.h"
#define MAXLENGTH 1000

void ArrayToZeroC(char *array, int length) {
  for (int i = 0; i < length; i++) {
    array[i] = 0;
  }
}

void ArrayToNumI(int *array, int length, int num) {
  for (int i = 0; i < length; i++) {
    array[i] = num;
  }
}

void BFSL(const adjacency_list *l, int start, char *visited, int *pred) {
  queue *q = CreateQueue();
  PushQueue(q, start);
  pred[start - 1] = 0;
  visited[start - 1] = 1;
  int temp;
  while (!IsEmpty(q)) {
    temp = PopQueue(q);
    Nodel *ptr = l[0].list[temp - 1];
    while (ptr != NULL) {
      if (visited[ptr->vertex - 1] == 0) {
        visited[ptr->vertex - 1] = 1;
        pred[ptr->vertex - 1] = pred[temp - 1] + ptr->length;
        PushQueue(q, ptr->vertex);
      }
      ptr = ptr->next;
    }
  }
  FreeQueue(q);
}

int *BFSLStart(const adjacency_list *l, int start) {
  char *visited = malloc(sizeof(char) * l[0].num_vertex);
  ArrayToZeroC(visited, l[0].num_vertex);
  int *pred = malloc(sizeof(int) * l[0].num_vertex);
  ArrayToNumI(pred, l[0].num_vertex, 0);
  BFSL(l, start, visited, pred);
  free(visited);
  return pred;
}

void BFSM(const adjacency_matrix *m, int start, char *visited, int *pred) {
  queue *q = CreateQueue();
  PushQueue(q, start);
  pred[start - 1] = 0;
  visited[start - 1] = 1;

  int temp;
  while (!IsEmpty(q)) {
    temp = q[0].head->data;
    PopQueue(q);

    for (int i = 1; i <= m[0].length; i++) {
      if (visited[i - 1] == 0 && m[0].matrix[temp - 1][i - 1] != 0) {
        visited[i - 1] = 1;
        pred[i - 1] = pred[temp - 1] + m[0].matrix[temp - 1][i - 1];
        PushQueue(q, i);
      }
    }
  }
  FreeQueue(q);
}

int *BFSMStart(const adjacency_matrix *m, int start) {
  char *visited = malloc(sizeof(char) * m[0].length);
  ArrayToZeroC(visited, m[0].length);
  int *pred = malloc(sizeof(int) * m[0].length);
  ArrayToNumI(pred, m[0].length, 0);
  BFSM(m, start, visited, pred);
  free(visited);
  return pred;
}
char CompareArrays(const int *a, const int *b, int length) {
  for (int i = 0; i < length; i++) {
    if (a[i] != b[i]) {
      return 0;
    }
  }
  return 1;
}

char CompareGraphs(const char *filepath_to_list,
                   const char *filepath_to_matrix) {
  adjacency_matrix *m = GetMatrix(filepath_to_matrix);
  adjacency_list *l = GetList(filepath_to_list);
  for (int i = 0; i < l->num_vertex; i++) {
    int *pred2 = BFSMStart(m, i + 1);
    int *pred1 = BFSLStart(l, i + 1);

    if (m[0].length != l[0].num_vertex) {
      return 0;
    }
    char res = CompareArrays(pred1, pred2, m[0].length);
    free(pred1);
    free(pred2);
    if (res == 0) {
      return 0;
    }
  }
  return 1;
}