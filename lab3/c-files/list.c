#include "../headers/list.h"
#define MAXLENGTH 100

void PrintList(adjacency_list *l) {
  for (int i = 0; i < l[0].num_vertex; i++) {
    printf("%d: ", i + 1);
    Nodel *ptr = l->list[i];

    while (ptr) {
      printf("(%d - %d)  ", ptr->vertex, ptr->length);
      ptr = ptr->next;
    }
    printf("\n");
  }
  printf("\n\n\n");
}

int GetIntFromChar(char *buffer) {
  int t = 0;
  int result = 0;
  while (buffer[t] != '\n' && buffer[t] != '\0') {
    result *= 10;
    result += buffer[t] - '0';
    t++;
  }
  return result;
}

adjacency_list *GetList(const char *filename) {
  FILE *f_r = fopen(filename, "r");
  if (!f_r) {
    perror("WrongFile");
    exit(1);
  }
  char buffer[MAXLENGTH];
  int length = 0;
  fgets(buffer, MAXLENGTH, f_r);
  length = GetIntFromChar(buffer);

  adjacency_list *list = malloc(sizeof(adjacency_list));
  list->list = malloc(sizeof(Nodel *) * length);
  for (int i = 0; i < length; i++) {
    list->list[i] = malloc(sizeof(Nodel));
  }
  char is_in_cycle;
  for (int i = 0; i < length; i++) {
    fgets(buffer, MAXLENGTH, f_r);
    Nodel *head = list->list[i];
    int j = 0;
    is_in_cycle = 0;
    head->vertex = 0;
    while (buffer[j] != '\n' && buffer[j] != '\0') {
      is_in_cycle = 1;
      if (buffer[j] == ' ') {
        head->next = malloc(sizeof(Nodel));
        head = head->next;
        head->vertex = 0;
        j++;
      } else {
        head->vertex = head->vertex * 10 + buffer[j] - '0';
        head->length = 1;
        j++;
      }
    }
    if (is_in_cycle) {

      head->next = NULL;
    } else {
      list->list[i] = NULL;
    }
  }
  list->num_vertex = length;
  fclose(f_r);
  return list;
}