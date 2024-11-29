#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

// Максимальные размеры графа
#define MAX_VERTICES 100

// Функция для проверки совпадения графов
bool compare_graphs(const char* adjacency_list_file, const char* adjacency_matrix_file);

#endif
