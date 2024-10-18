#include "../headers/main.h"

char CheckVisits(int *visited, int length) {
  /*printf("\n\n\n");
   for(int i = 0; i < length; i++){
      printf("%d - %d\n",i,visited[i]);
  }
  printf("\n\n\n");*/
  for (int i = 0; i < length; i++) {
    if (!visited[i]) {

      return 0;
    }
  }
  return 1;
}

char FindHamiltonPath(adjacency_list *l, int *visited, int count, FILE *f_w) {
  visited[count] = 1;
  if (CheckVisits(visited, l->num_vertex)) {
    fprintf(f_w, "%d ", count + 1);
    return 1;
  }

  Nodel *head = l->list[count];
  char result = 0;
  while (head) {
    if (!visited[head->vertex - 1]) {
      result = FindHamiltonPath(l, visited, head->vertex - 1, f_w);
      if (result) {
        fprintf(f_w, "%d ", count + 1);
        return 1;
      }
    }
    head = head->next;
  }
  visited[count] = 0;
  return 0;
}

void FindHamiltonPathStart(char *input, char *output) {
  adjacency_list *l = GetList(input);
  int *visited = malloc(sizeof(int) * l->num_vertex);
  FILE *f_w = fopen(output, "w");
  if (!f_w) {
    perror("WrongFile");
    exit(1);
  }
  for (int i = 0; i < l->num_vertex; i++) {
    for (int j = 0; j < l->num_vertex; j++) {
      visited[j] = 0;
    }
    if (FindHamiltonPath(l, visited, i, f_w)) {
      fclose(f_w);
      return;
    }
  }
  fprintf(f_w, "0");
  fclose(f_w);
}