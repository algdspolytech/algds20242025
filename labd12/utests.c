#include "header.h"


void graph_coloring_cycle() {
    FILE* input_file = fopen("input_cycle.txt", "r");
    FILE* output_file = fopen("output_cycle.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}

void graph_coloring_star() {
    FILE* input_file = fopen("input_star.txt", "r");
    FILE* output_file = fopen("output_star.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}

void graph_coloring_complete() {
    FILE* input_file = fopen("input_complete.txt", "r");
    FILE* output_file = fopen("output_complete.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}

void graph_coloring_tree() {
    FILE* input_file = fopen("input_tree.txt", "r");
    FILE* output_file = fopen("output_tree.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}

void graph_coloring_path() {
    FILE* input_file = fopen("input_path.txt", "r");
    FILE* output_file = fopen("output_path.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}

void graph_coloring_triangle() {
    FILE* input_file = fopen("input_triangle.txt", "r");
    FILE* output_file = fopen("output_triangle.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}

void graph_coloring_bipartite() {
    FILE* input_file = fopen("input_bipartite.txt", "r");
    FILE* output_file = fopen("output_bipartite.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}

void graph_coloring_combined() {
    FILE* input_file = fopen("input_combined.txt", "r");
    FILE* output_file = fopen("output_combined.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}

void graph_coloring_disconnected() {
    FILE* input_file = fopen("input_disconnected.txt", "r");
    FILE* output_file = fopen("output_disconnected.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);
    for (int i = 0; i < V; i++) {
        color[i] = 0;
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file);
    }
    fclose(input_file);

    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]);
        }
    }
    else {
        fprintf(output_file, "0");
    }
    fclose(output_file);
}
void graph_coloring_complex() {
    FILE* input_file = fopen("input_complex.txt", "r");
    FILE* output_file = fopen("output_complex.txt", "w");
    if (!input_file || !output_file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    fscanf(input_file, "%d %d", &V, &K);

    // Инициализация массива цветов и графа
    for (int i = 0; i < V; i++) {
        color[i] = 0; // Инициализация цветов
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0; // Инициализация графа
        }
    }

    // Загрузка графа в массив смежности
    for (int i = 0; i < V; i++) {
        int adjacent_vertex;
        while (fscanf(input_file, "%d", &adjacent_vertex) == 1) {
            graph[i][adjacent_vertex - 1] = 1;
        }
        fgetc(input_file); // Переход на следующую строку
    }

    fclose(input_file); // Закрытие файла с входными данными

    // Выполнение раскраски графа
    if (graph_coloring(0)) {
        for (int i = 0; i < V; i++) {
            fprintf(output_file, "%d ", color[i]); // Запись цветов в выходной файл
        }
    }
    else {
        fprintf(output_file, "0"); // Если раскрасить не удалось
    }

    fclose(output_file); // Закрытие выходного файла
}