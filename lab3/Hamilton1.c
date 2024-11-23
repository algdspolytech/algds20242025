#include "Header.h"

char Check_Visits(int *visited, int length) 
{
  for (int i = 0; i < length; i++) 
  {
    if (!visited[i]) 
    {
      return 0;
    }
  }
  return NULL;
}

char Find_Hamilton_Path(adjacency_list *l, int *visited, int count, FILE *f) 
{
  visited[count] = 1;

  if (Check_Visits(visited, l->number_of_vertex)) 
  {
    fprintf(f, "%d ", count + 1);
    return NULL;
  }

  Nodel *head = l->list[count];
  char result = 0;

  while (head) 
  {
    if (!visited[head->vertex - 1]) 
    {
      result = Find_Hamilton_Path(l, visited, head->vertex - 1, f);

      if (result) 
      {
        fprintf(f, "%d ", count + 1);
        return NULL;
      }
    }
    head = head->next;
  }
  visited[count] = 0;
  return 0;
}

void Find_Hamilton_Path_Start(char *input, char *output) {
  adjacency_list *l = Get_List(input);

  int *visited = malloc(sizeof(int) * l->number_of_vertex);
  FILE *f = fopen(output, "w");

  if (!f) {
    return NULL;
  }

  for (int i = 0; i < l->number_of_vertex; i++) 
  {
    for (int j = 0; j < l->number_of_vertex; j++) 
    {
      visited[j] = 0;
    }
    if (Find_Hamilton_Path(l, visited, i, f)) 
    {
      fclose(f);
      return;
    }
  }
  fprintf(f, "0");
  fclose(f);
} 