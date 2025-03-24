#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "tests.h"

#pragma warning(disable : 4996)

#define MAX_NODES 100  // Максимальное количество вершин

int main() {
    setlocale(LC_ALL, "Rus");
    FILE* file = fopen("graph.txt", "r"); // Открываем файл с графом
    if (!file) {
        printf("Ошибка: не удалось открыть файл!\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n); // Читаем количество вершин

    int graph[MAX_NODES][MAX_NODES];

    // Читаем матрицу смежности из файла
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(file, "%d", &graph[i][j]);

    fclose(file);

    int start, end;
    printf("Введите начальную и конечную вершины (0-%d): ", n - 1);
    scanf("%d %d", &start, &end);

    if (start < 0 || start >= n || end < 0 || end >= n) {
        printf("Ошибка: некорректные вершины!\n");
        return 1;
    }

    if (is_path_exists(graph, n, start, end))
        printf("Путь между вершинами %d и %d существует.\n", start, end);
    else
        printf("Пути между вершинами %d и %d нет.\n", start, end);

    test_graph();

    return 0;
}