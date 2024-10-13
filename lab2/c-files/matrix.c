#include "../headers/list.h"
#define MAXLENGTH 1000

adjacency_list *GetList(const char *filename) {
  FILE *f_r = fopen(filename, "r");
  if (!f_r) {
    exit(1);
  }
  char buffer[MAXLENGTH];
  adjacency_list *list = malloc(sizeof(adjacency_list));
  list->list = malloc(1);
  int length = 0;
  while (fgets(buffer, MAXLENGTH, f_r)) {
    length++;
    int i = 0;
    Nodel **temp = realloc(list->list, sizeof(Nodel *) * length);
    if (!temp) {
      free(list->list);
      exit(1);
    }
    list->list = temp;
    list->list[length - 1] = malloc(sizeof(Nodel));
    Nodel *head = list->list[length - 1];
    while (buffer[i] != '\n' && buffer[i] != '\0') {
      if (buffer[i] == ';') {
        head->next = malloc(sizeof(Nodel));
        head = head->next;
        i++;
      } else if (buffer[i] == ':') {
        i++;
        head->length = buffer[i] - '0';
        i++;
      } else {
        head->vertex = buffer[i] - '0';
        i++;
      }
    }

    head->next = NULL;
  }
  list->num_vertex = length;

  fclose(f_r);
  return list;
}