#include "Header.h"
#define MAXLENGTH 100

void Print_List(adjacency_list *l)
{
  for (int i = 0; i < l[0].number_of_vertex; i++) 
  {
    printf("%d: ", i + 1);
    Nodel *p = l->list[i];

    while (p) 
    {
      printf("(%d - %d)  ", p->vertex, p->length);
      p = p->next;
    }
    printf("\n");
  }
  printf("\n\n\n");
}

int Get_Int_From_Char(char *buffer) 
{
  int c = 0;
  int result = 0;

  while (buffer[c] != '\n' && buffer[c] != '\0') 
  {
    result *= 10;
    result += buffer[c] - '0';
    c++;
  }
  return result;
}

adjacency_list *Get_List(const char *filename) {

  FILE *f = fopen(filename, "r");

  if (!f) {
    return NULL;
  }

  char buffer[MAXLENGTH];
  int length = 0;

  fgets(buffer, MAXLENGTH, f);
  length = Get_Int_From_Char(buffer);

  adjacency_list *list = malloc(sizeof(adjacency_list));
  list->list = malloc(sizeof(Nodel *) * length);

  for (int i = 0; i < length; i++) 
  {
    list->list[i] = malloc(sizeof(Nodel));
  }

  char is_in_cycle;

  for (int i = 0; i < length; i++) 
  {
    fgets(buffer, MAXLENGTH, f);
    Nodel *head = list->list[i];

    int j = 0;
    is_in_cycle = 0;
    head->vertex = 0;

    while (buffer[j] != '\n' && buffer[j] != '\0') 
    {
      is_in_cycle = 1;
      if (buffer[j] == ' ') 
      {
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

    if (is_in_cycle) 
    {

      head->next = NULL;
    } else {
      list->list[i] = NULL;
    }

  }
  list->number_of_vertex = length;
  fclose(f);
  return list;
} 