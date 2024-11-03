#include "LabC.h"

int main() {
  // Считываем данные из файла
  FILE *file = fopen(INPUT_FILE, "r");
  char **words = get_words_from_file(file);

  HashMap *dict = get_words_table(words);

  char **keys = GetKeys(dict);

  int **graph = get_segments(file, dict);
  int length = dict->keys_size;

  // Выполняем топологическую сортировку

  int *st = (int *)malloc((length + 1) * sizeof(int));
  st[0] = -1;
  int *visited = (int *)malloc(length * sizeof(int));
  for (int i = 0; i < length; i++)
    visited[i] = 0;

  // Вызываем рекурсивную вспомогательную функцию топологической сортировки для
  // каждой вершины
  for (int i = 0; i < length; i++)
    if (visited[i] == 0)
      top_sort(i, visited, st, graph, length);

  length = 0;
  while (st[length] != -1)
    length++;

  // Возможна ситуация что такой последовательности не существует поэтому
  // проверим что она была составлена правильно
  int flag = 1;
  for (int i = 0; i < length; i++) {
    for (int j = i; j < length; j++) {
      if (graph[st[i]][st[j]] == 1) {
        flag = 0;
      }
    }
  }

  // По результатам топологической сортировки и проверки записываем результат в
  // выходной файл
  file = fopen(OUTPUT_FILE, "w");
  if (flag) {
    for (int j = length - 1; j >= 0; j--)
      fprintf(file, "%s ", GetKeyByValue(dict, st[j]));
  } else {
    fprintf(file, "[Error]");
  }
}