#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "HashMap.h"

#define INPUT_FILE "graph.txt"
#define OUTPUT_FILE "output.txt"


// Функция считывающая слова
char** get_words_from_file(FILE* file);

// Функция создающая словарь слов, где каждому слову сопоставляется число от 1 до n
HashMap* get_words_table(char** words);

// Функция считывающая из файла связи между словами
int** get_segments(FILE* file, HashMap* dict);

// Рекурсивная функция топологической сортировки
void top_sort(int i, int* visited, int* st, int** graph, int length);