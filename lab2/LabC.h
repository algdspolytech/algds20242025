#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "HashMap.h"

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

// Фунция получающая слова из файла
char **get_words_from_file(FILE *file);

// Функция создающая на основании надора слов, словарь в котором каждому слову
// ставиться число от 0 до n
HashMap *get_words_table(char **words);

// Функция считывающая из файла связи между узлами графа
int **get_segments(FILE *file, HashMap *dict);

// Рекурсивная функция топологической сортировки
void top_sort(int i, int *visited, int *st, int **graph, int length);